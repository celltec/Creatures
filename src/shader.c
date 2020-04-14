#include "shader.h"

/* Limit vertices to 16 bit */
#define VERTEX_MAX (1 << 14)  /* 16384 possible vertices */
#define INDEX_MAX (VERTEX_MAX << 2)  /* 4 indices for every vertex */

// todo: check these numbers, they are probably not the most efficient
// todo: dynamic allocation possible?

typedef struct { float x, y; } Point;
typedef struct { Point pos, uv; float radius; Color fill, outline; } Vertex;

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

	vBufId = sg_make_buffer(&(sg_buffer_desc) {
		.label = "vertex buffer",
		.size = VERTEX_MAX * sizeof(Vertex),
		.type = SG_BUFFERTYPE_VERTEXBUFFER,
		.usage = SG_USAGE_STREAM
	});

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
		.layout = {
			.attrs = {
				[ATTR_vs_IN_pos].format = SG_VERTEXFORMAT_FLOAT2,
				[ATTR_vs_IN_uv].format = SG_VERTEXFORMAT_FLOAT2,
				[ATTR_vs_IN_radius].format = SG_VERTEXFORMAT_FLOAT,
				[ATTR_vs_IN_fill].format = SG_VERTEXFORMAT_FLOAT4,
				[ATTR_vs_IN_outline].format = SG_VERTEXFORMAT_FLOAT4
			}
		}
	});

	/* White background */
	state.action = (sg_pass_action) {
		.colors[0] = {.action = SG_ACTION_CLEAR, .val = {1.0f, 1.0f, 1.0f, 1.0f } }
	};

	/* setup resource bindings */
	state.bind = (sg_bindings) {
		.vertex_buffers[0] = vBufId,
		.index_buffer = iBufId
	};
}

void ConstructFrame(cpTransform* matrix, cpFloat scale, cpVect offset)
{
	int width = sapp_width();
	int height = sapp_height();
	
	/* Half width and height to get center */
	float hw = (float)(width >> 1);
	float hh = (float)(height >> 1);

	cpTransform viewMatrix = cpTransformMult(cpTransformScale(scale, scale), cpTransformTranslate(offset));
	cpTransform projectionMatrix = cpTransformOrtho(cpBBNew(-hw, -hh, hw, hh));
	cpTransform mvp = cpTransformMult(projectionMatrix, viewMatrix);
	*matrix = mvp;

	vs_params_t vs_params;
	vs_params.mvp = (hmm_mat4){ (float)mvp.a, (float)mvp.b, 0.0f, 0.0f,
								(float)mvp.c, (float)mvp.d, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								(float)mvp.tx, (float)mvp.ty, 0.0f, 1.0f },

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

static Vertex* push_vertexes(size_t vcount, const uint16_t* index_src, size_t icount) {
	//cpAssertHard(vertexCount + vcount <= VERTEX_MAX && indexCount + icount <= INDEX_MAX, "Geometry buffer full.");

	Vertex* vertex_dst = vertexBuffer + vertexCount;
	size_t base = vertexCount;
	vertexCount += vcount;

	uint16_t* index_dst = indexBuffer + indexCount;
	for (size_t i = 0; i < icount; i++) index_dst[i] = index_src[i] + (uint16_t)base;
	indexCount += icount;

	return vertex_dst;
}

void DrawPolygon(int corners, const cpVect* vertices, float size, Color color)
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

	Vertex* vBuf = push_vertexes(4 * corners, indices, 3 * (5 * corners - 2));
	for (int i = 0; i < corners; i++) {
		cpVect v0 = vertices[i];
		cpVect vPrev = vertices[(i + (corners - 1)) % corners];
		cpVect vNext = vertices[(i + (corners + 1)) % corners];
		
		cpVect n1 = cpvnormalize(cpvrperp(cpvsub(v0, vPrev)));
		cpVect n2 = cpvnormalize(cpvrperp(cpvsub(vNext, v0)));
		cpVect of = cpvmult(cpvadd(n1, n2), 1.0 / (cpvdot(n1, n2) + 1.0f));
		cpVect v = cpvadd(v0, cpvmult(of, inset));

		vBuf[4 * i + 0] = (Vertex){ {(float)v.x, (float)v.y}, {0.0f, 0.0f}, 0.0f, color, color };
		vBuf[4 * i + 1] = (Vertex){ {(float)v.x, (float)v.y}, {(float)n1.x, (float)n1.y}, radius, color, color };
		vBuf[4 * i + 2] = (Vertex){ {(float)v.x, (float)v.y}, {(float)of.x, (float)of.y}, radius, color, color };
		vBuf[4 * i + 3] = (Vertex){ {(float)v.x, (float)v.y}, {(float)n2.x, (float)n2.y}, radius, color, color };
	}
}
