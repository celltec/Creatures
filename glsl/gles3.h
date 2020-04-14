#pragma once
/*
    #version:1# (machine generated, don't edit!)

    Generated by sokol-shdc (https://github.com/floooh/sokol-tools)

    Overview:

        Shader program 'app':
            Get shader desc: app_shader_desc()
            Vertex shader: vs
                Attribute slots:
                    ATTR_vs_IN_pos = 0
                    ATTR_vs_IN_uv = 1
                    ATTR_vs_IN_radius = 2
                    ATTR_vs_IN_fill = 3
                    ATTR_vs_IN_outline = 4
                Uniform block 'vs_params':
                    C struct: vs_params_t
                    Bind slot: SLOT_vs_params = 0
            Fragment shader: fs


    Shader descriptor structs:

        sg_shader app = sg_make_shader(app_shader_desc());

    Vertex attribute locations for vertex shader 'vs':

        sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc){
            .layout = {
                .attrs = {
                    [ATTR_vs_IN_pos] = { ... },
                    [ATTR_vs_IN_uv] = { ... },
                    [ATTR_vs_IN_radius] = { ... },
                    [ATTR_vs_IN_fill] = { ... },
                    [ATTR_vs_IN_outline] = { ... },
                },
            },
            ...});

    Image bind slots, use as index in sg_bindings.vs_images[] or .fs_images[]


    Bind slot and C-struct for uniform block 'vs_params':

        vs_params_t vs_params = {
            .mvp = ...;
        };
        sg_apply_uniforms(SG_SHADERSTAGE_[VS|FS], SLOT_vs_params, &vs_params, sizeof(vs_params));

*/
#include <stdint.h>
#include <stdbool.h>
#if !defined(SOKOL_SHDC_ALIGN)
  #if defined(_MSC_VER)
    #define SOKOL_SHDC_ALIGN(a) __declspec(align(a))
  #else
    #define SOKOL_SHDC_ALIGN(a) __attribute__((aligned(a)))
  #endif
#endif
#define ATTR_vs_IN_pos (0)
#define ATTR_vs_IN_uv (1)
#define ATTR_vs_IN_radius (2)
#define ATTR_vs_IN_fill (3)
#define ATTR_vs_IN_outline (4)
#define SLOT_vs_params (0)
#pragma pack(push,1)
SOKOL_SHDC_ALIGN(16) typedef struct vs_params_t {
    hmm_mat4 mvp;
} vs_params_t;
#pragma pack(pop)
#if defined(SOKOL_GLES3)
/*
    #version 300 es
    
    struct s_frag
    {
        vec2 uv;
        vec4 fill;
        vec4 outline;
    };
    
    uniform vec4 vs_params[4];
    layout(location = 0) in vec2 IN_pos;
    layout(location = 2) in float IN_radius;
    layout(location = 1) in vec2 IN_uv;
    out vec2 FRAG_uv;
    out vec4 FRAG_fill;
    out vec4 FRAG_outline;
    layout(location = 3) in vec4 IN_fill;
    layout(location = 4) in vec4 IN_outline;
    
    void main()
    {
        gl_Position = mat4(vs_params[0], vs_params[1], vs_params[2], vs_params[3]) * vec4(IN_pos + (IN_uv * IN_radius), 0.0, 0.0);
        FRAG_uv = IN_uv;
        FRAG_fill = IN_fill;
        vec3 _60 = FRAG_fill.xyz * IN_fill.w;
        FRAG_fill = vec4(_60.x, _60.y, _60.z, FRAG_fill.w);
        FRAG_outline = IN_outline;
        FRAG_outline.w *= IN_outline.w;
    }
    
*/
static const char vs_source_glsl300es[721] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x30,0x30,0x20,0x65,0x73,0x0a,
    0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x73,0x5f,0x66,0x72,0x61,0x67,0x0a,0x7b,
    0x0a,0x20,0x20,0x20,0x20,0x76,0x65,0x63,0x32,0x20,0x75,0x76,0x3b,0x0a,0x20,0x20,
    0x20,0x20,0x76,0x65,0x63,0x34,0x20,0x66,0x69,0x6c,0x6c,0x3b,0x0a,0x20,0x20,0x20,
    0x20,0x76,0x65,0x63,0x34,0x20,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x3b,0x0a,0x7d,
    0x3b,0x0a,0x0a,0x75,0x6e,0x69,0x66,0x6f,0x72,0x6d,0x20,0x76,0x65,0x63,0x34,0x20,
    0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x34,0x5d,0x3b,0x0a,0x6c,0x61,
    0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,
    0x30,0x29,0x20,0x69,0x6e,0x20,0x76,0x65,0x63,0x32,0x20,0x49,0x4e,0x5f,0x70,0x6f,
    0x73,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,
    0x6f,0x6e,0x20,0x3d,0x20,0x32,0x29,0x20,0x69,0x6e,0x20,0x66,0x6c,0x6f,0x61,0x74,
    0x20,0x49,0x4e,0x5f,0x72,0x61,0x64,0x69,0x75,0x73,0x3b,0x0a,0x6c,0x61,0x79,0x6f,
    0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x31,0x29,
    0x20,0x69,0x6e,0x20,0x76,0x65,0x63,0x32,0x20,0x49,0x4e,0x5f,0x75,0x76,0x3b,0x0a,
    0x6f,0x75,0x74,0x20,0x76,0x65,0x63,0x32,0x20,0x46,0x52,0x41,0x47,0x5f,0x75,0x76,
    0x3b,0x0a,0x6f,0x75,0x74,0x20,0x76,0x65,0x63,0x34,0x20,0x46,0x52,0x41,0x47,0x5f,
    0x66,0x69,0x6c,0x6c,0x3b,0x0a,0x6f,0x75,0x74,0x20,0x76,0x65,0x63,0x34,0x20,0x46,
    0x52,0x41,0x47,0x5f,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x3b,0x0a,0x6c,0x61,0x79,
    0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x33,
    0x29,0x20,0x69,0x6e,0x20,0x76,0x65,0x63,0x34,0x20,0x49,0x4e,0x5f,0x66,0x69,0x6c,
    0x6c,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,
    0x6f,0x6e,0x20,0x3d,0x20,0x34,0x29,0x20,0x69,0x6e,0x20,0x76,0x65,0x63,0x34,0x20,
    0x49,0x4e,0x5f,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x3b,0x0a,0x0a,0x76,0x6f,0x69,
    0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x67,
    0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x6d,0x61,0x74,
    0x34,0x28,0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x30,0x5d,0x2c,0x20,
    0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x31,0x5d,0x2c,0x20,0x76,0x73,
    0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x32,0x5d,0x2c,0x20,0x76,0x73,0x5f,0x70,
    0x61,0x72,0x61,0x6d,0x73,0x5b,0x33,0x5d,0x29,0x20,0x2a,0x20,0x76,0x65,0x63,0x34,
    0x28,0x49,0x4e,0x5f,0x70,0x6f,0x73,0x20,0x2b,0x20,0x28,0x49,0x4e,0x5f,0x75,0x76,
    0x20,0x2a,0x20,0x49,0x4e,0x5f,0x72,0x61,0x64,0x69,0x75,0x73,0x29,0x2c,0x20,0x30,
    0x2e,0x30,0x2c,0x20,0x30,0x2e,0x30,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x46,0x52,
    0x41,0x47,0x5f,0x75,0x76,0x20,0x3d,0x20,0x49,0x4e,0x5f,0x75,0x76,0x3b,0x0a,0x20,
    0x20,0x20,0x20,0x46,0x52,0x41,0x47,0x5f,0x66,0x69,0x6c,0x6c,0x20,0x3d,0x20,0x49,
    0x4e,0x5f,0x66,0x69,0x6c,0x6c,0x3b,0x0a,0x20,0x20,0x20,0x20,0x76,0x65,0x63,0x33,
    0x20,0x5f,0x36,0x30,0x20,0x3d,0x20,0x46,0x52,0x41,0x47,0x5f,0x66,0x69,0x6c,0x6c,
    0x2e,0x78,0x79,0x7a,0x20,0x2a,0x20,0x49,0x4e,0x5f,0x66,0x69,0x6c,0x6c,0x2e,0x77,
    0x3b,0x0a,0x20,0x20,0x20,0x20,0x46,0x52,0x41,0x47,0x5f,0x66,0x69,0x6c,0x6c,0x20,
    0x3d,0x20,0x76,0x65,0x63,0x34,0x28,0x5f,0x36,0x30,0x2e,0x78,0x2c,0x20,0x5f,0x36,
    0x30,0x2e,0x79,0x2c,0x20,0x5f,0x36,0x30,0x2e,0x7a,0x2c,0x20,0x46,0x52,0x41,0x47,
    0x5f,0x66,0x69,0x6c,0x6c,0x2e,0x77,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x46,0x52,
    0x41,0x47,0x5f,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x20,0x3d,0x20,0x49,0x4e,0x5f,
    0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x3b,0x0a,0x20,0x20,0x20,0x20,0x46,0x52,0x41,
    0x47,0x5f,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x2e,0x77,0x20,0x2a,0x3d,0x20,0x49,
    0x4e,0x5f,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x2e,0x77,0x3b,0x0a,0x7d,0x0a,0x0a,
    0x00,
};
/*
    #version 300 es
    precision mediump float;
    precision highp int;
    
    struct s_frag
    {
        highp vec2 uv;
        highp vec4 fill;
        highp vec4 outline;
    };
    
    in highp vec2 FRAG_uv;
    in highp vec4 FRAG_fill;
    in highp vec4 FRAG_outline;
    layout(location = 0) out highp vec4 OUT_color;
    
    void main()
    {
        highp float _20 = length(FRAG_uv);
        highp float _25 = length(fwidth(FRAG_uv));
        highp float _36 = 1.0 - _25;
        OUT_color = (FRAG_fill + ((FRAG_outline - (FRAG_fill * FRAG_outline.w)) * smoothstep(_36 - _25, _36, _20))) * smoothstep(-1.0, _25 - 1.0, -_20);
    }
    
*/
static const char fs_source_glsl300es[557] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x30,0x30,0x20,0x65,0x73,0x0a,
    0x70,0x72,0x65,0x63,0x69,0x73,0x69,0x6f,0x6e,0x20,0x6d,0x65,0x64,0x69,0x75,0x6d,
    0x70,0x20,0x66,0x6c,0x6f,0x61,0x74,0x3b,0x0a,0x70,0x72,0x65,0x63,0x69,0x73,0x69,
    0x6f,0x6e,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x69,0x6e,0x74,0x3b,0x0a,0x0a,0x73,
    0x74,0x72,0x75,0x63,0x74,0x20,0x73,0x5f,0x66,0x72,0x61,0x67,0x0a,0x7b,0x0a,0x20,
    0x20,0x20,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x76,0x65,0x63,0x32,0x20,0x75,0x76,
    0x3b,0x0a,0x20,0x20,0x20,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x76,0x65,0x63,0x34,
    0x20,0x66,0x69,0x6c,0x6c,0x3b,0x0a,0x20,0x20,0x20,0x20,0x68,0x69,0x67,0x68,0x70,
    0x20,0x76,0x65,0x63,0x34,0x20,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x3b,0x0a,0x7d,
    0x3b,0x0a,0x0a,0x69,0x6e,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x76,0x65,0x63,0x32,
    0x20,0x46,0x52,0x41,0x47,0x5f,0x75,0x76,0x3b,0x0a,0x69,0x6e,0x20,0x68,0x69,0x67,
    0x68,0x70,0x20,0x76,0x65,0x63,0x34,0x20,0x46,0x52,0x41,0x47,0x5f,0x66,0x69,0x6c,
    0x6c,0x3b,0x0a,0x69,0x6e,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x76,0x65,0x63,0x34,
    0x20,0x46,0x52,0x41,0x47,0x5f,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x3b,0x0a,0x6c,
    0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,
    0x20,0x30,0x29,0x20,0x6f,0x75,0x74,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x76,0x65,
    0x63,0x34,0x20,0x4f,0x55,0x54,0x5f,0x63,0x6f,0x6c,0x6f,0x72,0x3b,0x0a,0x0a,0x76,
    0x6f,0x69,0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,
    0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x5f,0x32,0x30,
    0x20,0x3d,0x20,0x6c,0x65,0x6e,0x67,0x74,0x68,0x28,0x46,0x52,0x41,0x47,0x5f,0x75,
    0x76,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x66,0x6c,
    0x6f,0x61,0x74,0x20,0x5f,0x32,0x35,0x20,0x3d,0x20,0x6c,0x65,0x6e,0x67,0x74,0x68,
    0x28,0x66,0x77,0x69,0x64,0x74,0x68,0x28,0x46,0x52,0x41,0x47,0x5f,0x75,0x76,0x29,
    0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x66,0x6c,0x6f,
    0x61,0x74,0x20,0x5f,0x33,0x36,0x20,0x3d,0x20,0x31,0x2e,0x30,0x20,0x2d,0x20,0x5f,
    0x32,0x35,0x3b,0x0a,0x20,0x20,0x20,0x20,0x4f,0x55,0x54,0x5f,0x63,0x6f,0x6c,0x6f,
    0x72,0x20,0x3d,0x20,0x28,0x46,0x52,0x41,0x47,0x5f,0x66,0x69,0x6c,0x6c,0x20,0x2b,
    0x20,0x28,0x28,0x46,0x52,0x41,0x47,0x5f,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x20,
    0x2d,0x20,0x28,0x46,0x52,0x41,0x47,0x5f,0x66,0x69,0x6c,0x6c,0x20,0x2a,0x20,0x46,
    0x52,0x41,0x47,0x5f,0x6f,0x75,0x74,0x6c,0x69,0x6e,0x65,0x2e,0x77,0x29,0x29,0x20,
    0x2a,0x20,0x73,0x6d,0x6f,0x6f,0x74,0x68,0x73,0x74,0x65,0x70,0x28,0x5f,0x33,0x36,
    0x20,0x2d,0x20,0x5f,0x32,0x35,0x2c,0x20,0x5f,0x33,0x36,0x2c,0x20,0x5f,0x32,0x30,
    0x29,0x29,0x29,0x20,0x2a,0x20,0x73,0x6d,0x6f,0x6f,0x74,0x68,0x73,0x74,0x65,0x70,
    0x28,0x2d,0x31,0x2e,0x30,0x2c,0x20,0x5f,0x32,0x35,0x20,0x2d,0x20,0x31,0x2e,0x30,
    0x2c,0x20,0x2d,0x5f,0x32,0x30,0x29,0x3b,0x0a,0x7d,0x0a,0x0a,0x00,
};
static const sg_shader_desc app_shader_desc_glsl300es = {
  0, /* _start_canary */
  { /*attrs*/{"IN_pos","TEXCOORD",0},{"IN_uv","TEXCOORD",1},{"IN_radius","TEXCOORD",2},{"IN_fill","TEXCOORD",3},{"IN_outline","TEXCOORD",4},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}, },
  { /* vs */
    vs_source_glsl300es, /* source */
    0,  /* bytecode */
    0,  /* bytecode_size */
    "main", /* entry */
    { /* uniform blocks */
      {
        64, /* size */
        { /* uniforms */{"vs_params",SG_UNIFORMTYPE_FLOAT4,4},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0}, },
      },
      {
        0, /* size */
        { /* uniforms */{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0}, },
      },
      {
        0, /* size */
        { /* uniforms */{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0}, },
      },
      {
        0, /* size */
        { /* uniforms */{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0}, },
      },
    },
    { /* images */ {0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT}, },
  },
  { /* fs */
    fs_source_glsl300es, /* source */
    0,  /* bytecode */
    0,  /* bytecode_size */
    "main", /* entry */
    { /* uniform blocks */
      {
        0, /* size */
        { /* uniforms */{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0}, },
      },
      {
        0, /* size */
        { /* uniforms */{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0}, },
      },
      {
        0, /* size */
        { /* uniforms */{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0}, },
      },
      {
        0, /* size */
        { /* uniforms */{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0},{0,SG_UNIFORMTYPE_INVALID,0}, },
      },
    },
    { /* images */ {0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT},{0,_SG_IMAGETYPE_DEFAULT}, },
  },
  "app_shader", /* label */
  0, /* _end_canary */
};
#endif /* SOKOL_GLES3 */
#if !defined(SOKOL_GFX_INCLUDED)
  #error "Please include sokol_gfx.h before gles3.h"
#endif
static inline const sg_shader_desc* app_shader_desc(void) {
    #if defined(SOKOL_GLES3)
    if (sg_query_backend() == SG_BACKEND_GLES3) {
        return &app_shader_desc_glsl300es;
    }
    #endif /* SOKOL_GLES3 */
    return 0; /* can't happen */
}
