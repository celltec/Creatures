#include "sokol.h"
#include "color.h"
#include "shader.h"

// todo: dynamic allocation possible?
#define VERTEX_MAX (1 << 14)        /* Some vertex limit: 16384 possible vertices */
#define INDEX_MAX (4 * VERTEX_MAX)  /* 4 indices fro every vertex */

typedef struct { hmm_vec2 pos; Color color; } Vertex;

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

	/* Shader generated by sokol-shdc from app.glsl */
	sg_shader shd = sg_make_shader(app_shader_desc());

	/* Create pipeline */
	state.pipe = sg_make_pipeline(&(sg_pipeline_desc) {
		.layout = {
			.attrs = {
				[ATTR_vs_position] .format = SG_VERTEXFORMAT_FLOAT2,
				[ATTR_vs_color].format = SG_VERTEXFORMAT_FLOAT4
			}
		},
			.shader = shd,
			.index_type = SG_INDEXTYPE_UINT16,
			.label = "pipeline"
	});

	/* White background */
	state.action = (sg_pass_action){
		.colors[0] = {.action = SG_ACTION_CLEAR, .val = {1.0f, 1.0f, 1.0f, 1.0f } }
	};

	/* setup resource bindings */
	state.bind = (sg_bindings){
		.vertex_buffers[0] = vBufId,
		.index_buffer = iBufId
	};
}

void ConstructFrame(void)
{
	hmm_vec3 scale = { 0.1f, 0.1f, 1.0f };
	hmm_vec3 offset = { 5.0f, 5.0f, 0.0f };

	vertexBuffer[0] = (Vertex){ {-1, -1 }, red };
	vertexBuffer[1] = (Vertex){ {-1, 1 }, green };
	vertexBuffer[2] = (Vertex){ {1, 1 }, blue };
	vertexBuffer[3] = (Vertex){ {1, -1 }, black };

	vertexCount = 4;

	indexBuffer[0] = 0;
	indexBuffer[1] = 1;
	indexBuffer[2] = 2;
	indexBuffer[3] = 3;
	indexBuffer[4] = 0;
	indexBuffer[5] = 2;

	indexCount = 6;

	vs_params_t vs_params;
	vs_params.mvp = HMM_MultiplyMat4(HMM_Scale(scale), HMM_Translate(offset));

	sg_update_buffer(vBufId, vertexBuffer, vertexCount * sizeof(Vertex));
	sg_update_buffer(iBufId, indexBuffer, indexCount * sizeof(uint16_t));

	sg_begin_default_pass(&state.action, sapp_width(), sapp_height());
	sg_apply_pipeline(state.pipe);
	sg_apply_bindings(&state.bind);
	sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &vs_params, sizeof(vs_params));

	sg_draw(0, indexCount, 1);
	sg_end_pass();
	sg_commit();
}