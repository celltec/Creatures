#include "chipmunk/chipmunk.h"
#include "shader.h"

/* Limit vertices to 16 bit */
#define VERTEX_MAX (1 << 14)  /* 16384 possible vertices */
#define INDEX_MAX (VERTEX_MAX << 2)  /* 4 indices for every vertex */

// todo: check these numbers, they are probably not the most efficient
// todo: dynamic allocation possible?

typedef struct { float x, y; } Point;
typedef struct { Point pos, uv; float radius; Color color, highlight; } Vertex;

static sg_buffer vBufId, iBufId;
static uint16_t vertexCount, indexCount;

static Vertex vertexBuffer[VERTEX_MAX];
static uint16_t indexBuffer[INDEX_MAX];

static struct {
	sg_pipeline pipe;
	sg_bindings bind;
	sg_pass_action action;
} state;

void InitGfx(void)
{
	sg_setup(&(sg_desc) {
		.gl_force_gles2 = sapp_gles2(),
		.mtl_device = sapp_metal_get_device(),
		.mtl_renderpass_descriptor_cb = sapp_metal_get_renderpass_descriptor,
		.mtl_drawable_cb = sapp_metal_get_drawable,
		.d3d11_device = sapp_d3d11_get_device(),
		.d3d11_device_context = sapp_d3d11_get_device_context(),
		.d3d11_render_target_view_cb = sapp_d3d11_get_render_target_view,
		.d3d11_depth_stencil_view_cb = sapp_d3d11_get_depth_stencil_view
	});

	/* Vertex buffer */
	vBufId = sg_make_buffer(&(sg_buffer_desc) {
		.label = "vertex buffer",
		.size = VERTEX_MAX * sizeof(Vertex),
		.type = SG_BUFFERTYPE_VERTEXBUFFER,
		.usage = SG_USAGE_STREAM
	});

	/* Index buffer */
	iBufId = sg_make_buffer(&(sg_buffer_desc) {
		.label = "index buffer",
		.size = INDEX_MAX * sizeof(uint16_t),
		.type = SG_BUFFERTYPE_INDEXBUFFER,
		.usage = SG_USAGE_STREAM
	});

	/* Shader generated from app.glsl */
	sg_shader shader = sg_make_shader(app_shader_desc());

	/* Create pipeline */
	state.pipe = sg_make_pipeline(&(sg_pipeline_desc) {
		.label = "pipeline",
		.shader = shader,
		.index_type = SG_INDEXTYPE_UINT16,
		.rasterizer.sample_count = MSAA,
		.blend = {
			.enabled = true,
			.src_factor_rgb = SG_BLENDFACTOR_ONE,
			.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA
		},
		.layout = {
			.attrs = {
				[ATTR_vs_IN_pos].format = SG_VERTEXFORMAT_FLOAT2,
				[ATTR_vs_IN_uv].format = SG_VERTEXFORMAT_FLOAT2,
				[ATTR_vs_IN_radius].format = SG_VERTEXFORMAT_FLOAT,
				[ATTR_vs_IN_color].format = SG_VERTEXFORMAT_FLOAT4,
				[ATTR_vs_IN_highlight].format = SG_VERTEXFORMAT_FLOAT4
			}
		}
	});

	/* White background */
	state.action = (sg_pass_action) {
		.colors[0] = {
			.action = SG_ACTION_CLEAR,
			.val = { 1.0f, 1.0f, 1.0f, 1.0f }
		}
	};

	/* Bind buffer */
	state.bind = (sg_bindings) {
		.vertex_buffers[0] = vBufId,
		.index_buffer = iBufId
	};
}

void ConstructFrame(cpTransform* transform, cpFloat scale, cpVect offset)
{
	int width = sapp_width();
	int height = sapp_height();
	
	/* Zoom in view */
	float fw = (float)(width >> 4);
	float fh = (float)(height >> 4);
	cpBB viewBox = cpBBNew(-fw, -fh, fw, fh);

	cpTransform viewMatrix = cpTransformMult(cpTransformScale(scale, scale), cpTransformTranslate(offset));
	cpTransform projectionMatrix = cpTransformOrtho(viewBox);
	cpTransform vp = cpTransformMult(projectionMatrix, viewMatrix); // todo: use projectionMatrix for OSD

	*transform = vp;

	vs_params_t vs_params = {
		.vpMatrix = (Uniform){
			(float)vp.a, (float)vp.b, 0.0f, 0.0f,
			(float)vp.c, (float)vp.d, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			(float)vp.tx, (float)vp.ty, 0.0f, 1.0f } 
	};

	sg_update_buffer(vBufId, vertexBuffer, vertexCount * sizeof(Vertex));
	sg_update_buffer(iBufId, indexBuffer, indexCount * sizeof(uint16_t));

	sg_begin_default_pass(&state.action, width, height);
	sg_apply_pipeline(state.pipe);
	sg_apply_bindings(&state.bind);
	sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &vs_params, sizeof(vs_params));

	sg_draw(0, indexCount, 1);
	sg_end_pass();
	sg_commit();

	/* Reset buffer after drawing */
	vertexCount = 0;
	indexCount = 0;
}

static Vertex* push_vertices(size_t vcount, const uint16_t* index_src, size_t icount) {
	cpAssertHard(vertexCount + vcount <= VERTEX_MAX && indexCount + icount <= INDEX_MAX, "geometry buffer full");

	Vertex* vertex_dst = vertexBuffer + vertexCount;
	size_t base = vertexCount;
	vertexCount += vcount;

	uint16_t* index_dst = indexBuffer + indexCount;
	for (size_t i = 0; i < icount; i++) index_dst[i] = index_src[i] + (uint16_t)base;
	indexCount += icount;

	return vertex_dst;
}

void DrawDot(cpVect position, cpFloat size, Color color)
{
	Vertex* vertices = push_vertices(4, (uint16_t[]) { 0, 1, 2, 0, 2, 3 }, 6);

	Point pos = { (float)position.x, (float)position.y };
	float radius = (float)size;

	vertices[0] = (Vertex){ pos, {-1, -1}, radius, color };
	vertices[1] = (Vertex){ pos, {-1,  1}, radius, color };
	vertices[2] = (Vertex){ pos, { 1,  1}, radius, color };
	vertices[3] = (Vertex){ pos, { 1, -1}, radius, color };
}

void DrawLine(cpVect a, cpVect b, cpFloat radius, Color color)
{
	const uint16_t indices[] = { 0, 1, 2, 1, 2, 3, 2, 3, 4, 3, 4, 5, 4, 5, 6, 5, 6, 7 };
	Vertex* vertices = push_vertices(8, indices, 18);

	Point aPos = { (float)a.x, (float)a.y };
	Point bPos = { (float)b.x, (float)b.y };

	cpVect t = cpvnormalize(cpvsub(b, a));
	float r = (float)radius;

	vertices[0] = (Vertex){ aPos, {(float)(-t.x + t.y), (float)(-t.x - t.y)}, r, color };
	vertices[1] = (Vertex){ aPos, {(float)(-t.x - t.y), (float)(+t.x - t.y)}, r, color };
	vertices[2] = (Vertex){ aPos, {(float)(-0.0 + t.y), (float)(-t.x + 0.0)}, r, color };
	vertices[3] = (Vertex){ aPos, {(float)(-0.0 - t.y), (float)(+t.x + 0.0)}, r, color };

	vertices[4] = (Vertex){ bPos, {(float)(+0.0 + t.y), (float)(-t.x - 0.0)}, r, color };
	vertices[5] = (Vertex){ bPos, {(float)(+0.0 - t.y), (float)(+t.x - 0.0)}, r, color };
	vertices[6] = (Vertex){ bPos, {(float)(+t.x + t.y), (float)(-t.x + t.y)}, r, color };
	vertices[7] = (Vertex){ bPos, {(float)(+t.x - t.y), (float)(+t.x + t.y)}, r, color };
}

void DrawPolygon(int corners, const cpVect* vertices, cpFloat size, Color color, Color highlight)
{
	uint16_t indices[666]; // todo: make dynamic

	/* Fill triangles */
	for (int i = 0; i < corners - 2; i++)
	{
		indices[3 * i + 0] = 0;
		indices[3 * i + 1] = 4 * (i + 1);
		indices[3 * i + 2] = 4 * (i + 2);
	}

	/* Outline triangles */
	uint16_t* cursor = indices + 3 * (corners - 2);
	for (int i0 = 0; i0 < corners; i0++)
	{
		int i1 = (i0 + 1) % corners;
		cursor[12 * i0 + 0] = 4 * i0 + 0;
		cursor[12 * i0 + 1] = 4 * i0 + 1;
		cursor[12 * i0 + 2] = 4 * i0 + 2;
		cursor[12 * i0 + 3] = 4 * i0 + 0;
		cursor[12 * i0 + 4] = 4 * i0 + 2;
		cursor[12 * i0 + 5] = 4 * i0 + 3;
		cursor[12 * i0 + 6] = 4 * i0 + 0;
		cursor[12 * i0 + 7] = 4 * i0 + 3;
		cursor[12 * i0 + 8] = 4 * i1 + 0;
		cursor[12 * i0 + 9] = 4 * i0 + 3;
		cursor[12 * i0 + 10] = 4 * i1 + 0;
		cursor[12 * i0 + 11] = 4 * i1 + 1;
	}

	float inset = (float)-cpfmax(0, 2 * 1.0 - size);
	float outset = (float)size + 1.0;
	float radius = outset - inset;



	Vertex* vBuf = push_vertices(4 * corners, indices, 3 * (5 * corners - 2));
	
	for (int i = 0; i < corners; i++)
	{
		cpVect vCurr = vertices[i];
		cpVect vPrev = vertices[(i + (corners - 1)) % corners];
		cpVect vNext = vertices[(i + (corners + 1)) % corners];
		
		cpVect n1 = cpvnormalize(cpvrperp(cpvsub(vCurr, vPrev)));
		cpVect n2 = cpvnormalize(cpvrperp(cpvsub(vNext, vCurr)));
		cpVect of = cpvmult(cpvadd(n1, n2), 1.0f / (cpvdot(n1, n2) + 1.0f));
		cpVect v = cpvadd(vCurr, cpvmult(of, inset));

		Point pos = { v.x, v.y };

		vBuf[4 * i + 0] = (Vertex){ pos, {0.0f, 0.0f}, radius, color, highlight };
		vBuf[4 * i + 1] = (Vertex){ pos, {n1.x, n1.y}, radius, color, highlight };
		vBuf[4 * i + 2] = (Vertex){ pos, {of.x, of.y}, radius, color, highlight };
		vBuf[4 * i + 3] = (Vertex){ pos, {n2.x, n2.y}, radius, color, highlight };
	}
}
