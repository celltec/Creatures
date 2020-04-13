#pragma once
/*
    #version:1# (machine generated, don't edit!)

    Generated by sokol-shdc (https://github.com/floooh/sokol-tools)

    Overview:

        Shader program 'app':
            Get shader desc: app_shader_desc()
            Vertex shader: vs
                Attribute slots:
                    ATTR_vs_position = 0
                    ATTR_vs_color = 1
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
                    [ATTR_vs_position] = { ... },
                    [ATTR_vs_color] = { ... },
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
#define ATTR_vs_position (0)
#define ATTR_vs_color (1)
#define SLOT_vs_params (0)
#pragma pack(push,1)
SOKOL_SHDC_ALIGN(16) typedef struct vs_params_t {
    hmm_mat4 mvp;
} vs_params_t;
#pragma pack(pop)
#if defined(SOKOL_METAL)
/*
    #include <metal_stdlib>
    #include <simd/simd.h>
    
    using namespace metal;
    
    struct vs_params
    {
        float4x4 mvp;
    };
    
    struct main0_out
    {
        float4 vert_color [[user(locn0)]];
        float4 gl_Position [[position]];
    };
    
    struct main0_in
    {
        float4 position [[attribute(0)]];
        float4 color [[attribute(1)]];
    };
    
    #line 15 ""
    vertex main0_out main0(main0_in in [[stage_in]], constant vs_params& _20 [[buffer(0)]])
    {
        main0_out out = {};
    #line 15 ""
        out.gl_Position = _20.mvp * in.position;
    #line 16 ""
        out.vert_color = in.color;
        return out;
    }
    
*/
static const char vs_source_metal_ios[553] = {
    0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,0x20,0x3c,0x6d,0x65,0x74,0x61,0x6c,0x5f,
    0x73,0x74,0x64,0x6c,0x69,0x62,0x3e,0x0a,0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,
    0x20,0x3c,0x73,0x69,0x6d,0x64,0x2f,0x73,0x69,0x6d,0x64,0x2e,0x68,0x3e,0x0a,0x0a,
    0x75,0x73,0x69,0x6e,0x67,0x20,0x6e,0x61,0x6d,0x65,0x73,0x70,0x61,0x63,0x65,0x20,
    0x6d,0x65,0x74,0x61,0x6c,0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x76,
    0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,
    0x6c,0x6f,0x61,0x74,0x34,0x78,0x34,0x20,0x6d,0x76,0x70,0x3b,0x0a,0x7d,0x3b,0x0a,
    0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x6f,0x75,
    0x74,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x76,
    0x65,0x72,0x74,0x5f,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x5b,0x5b,0x75,0x73,0x65,0x72,
    0x28,0x6c,0x6f,0x63,0x6e,0x30,0x29,0x5d,0x5d,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,
    0x6c,0x6f,0x61,0x74,0x34,0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,
    0x6e,0x20,0x5b,0x5b,0x70,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x5d,0x5d,0x3b,0x0a,
    0x7d,0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x6d,0x61,0x69,0x6e,0x30,
    0x5f,0x69,0x6e,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,
    0x20,0x70,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x20,0x5b,0x5b,0x61,0x74,0x74,0x72,
    0x69,0x62,0x75,0x74,0x65,0x28,0x30,0x29,0x5d,0x5d,0x3b,0x0a,0x20,0x20,0x20,0x20,
    0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x5b,0x5b,0x61,
    0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x28,0x31,0x29,0x5d,0x5d,0x3b,0x0a,0x7d,
    0x3b,0x0a,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,0x35,0x20,0x22,0x22,0x0a,0x76,
    0x65,0x72,0x74,0x65,0x78,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x6f,0x75,0x74,0x20,
    0x6d,0x61,0x69,0x6e,0x30,0x28,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x69,0x6e,0x20,0x69,
    0x6e,0x20,0x5b,0x5b,0x73,0x74,0x61,0x67,0x65,0x5f,0x69,0x6e,0x5d,0x5d,0x2c,0x20,
    0x63,0x6f,0x6e,0x73,0x74,0x61,0x6e,0x74,0x20,0x76,0x73,0x5f,0x70,0x61,0x72,0x61,
    0x6d,0x73,0x26,0x20,0x5f,0x32,0x30,0x20,0x5b,0x5b,0x62,0x75,0x66,0x66,0x65,0x72,
    0x28,0x30,0x29,0x5d,0x5d,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x6d,0x61,0x69,
    0x6e,0x30,0x5f,0x6f,0x75,0x74,0x20,0x6f,0x75,0x74,0x20,0x3d,0x20,0x7b,0x7d,0x3b,
    0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,0x35,0x20,0x22,0x22,0x0a,0x20,0x20,0x20,
    0x20,0x6f,0x75,0x74,0x2e,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,
    0x20,0x3d,0x20,0x5f,0x32,0x30,0x2e,0x6d,0x76,0x70,0x20,0x2a,0x20,0x69,0x6e,0x2e,
    0x70,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x3b,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,
    0x31,0x36,0x20,0x22,0x22,0x0a,0x20,0x20,0x20,0x20,0x6f,0x75,0x74,0x2e,0x76,0x65,
    0x72,0x74,0x5f,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x69,0x6e,0x2e,0x63,0x6f,
    0x6c,0x6f,0x72,0x3b,0x0a,0x20,0x20,0x20,0x20,0x72,0x65,0x74,0x75,0x72,0x6e,0x20,
    0x6f,0x75,0x74,0x3b,0x0a,0x7d,0x0a,0x0a,0x00,
};
/*
    #include <metal_stdlib>
    #include <simd/simd.h>
    
    using namespace metal;
    
    struct main0_out
    {
        float4 frag_color [[color(0)]];
    };
    
    struct main0_in
    {
        float4 vert_color [[user(locn0)]];
    };
    
    #line 10 ""
    fragment main0_out main0(main0_in in [[stage_in]])
    {
        main0_out out = {};
    #line 10 ""
        out.frag_color = in.vert_color;
        return out;
    }
    
*/
static const char fs_source_metal_ios[349] = {
    0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,0x20,0x3c,0x6d,0x65,0x74,0x61,0x6c,0x5f,
    0x73,0x74,0x64,0x6c,0x69,0x62,0x3e,0x0a,0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,
    0x20,0x3c,0x73,0x69,0x6d,0x64,0x2f,0x73,0x69,0x6d,0x64,0x2e,0x68,0x3e,0x0a,0x0a,
    0x75,0x73,0x69,0x6e,0x67,0x20,0x6e,0x61,0x6d,0x65,0x73,0x70,0x61,0x63,0x65,0x20,
    0x6d,0x65,0x74,0x61,0x6c,0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x6d,
    0x61,0x69,0x6e,0x30,0x5f,0x6f,0x75,0x74,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,
    0x6c,0x6f,0x61,0x74,0x34,0x20,0x66,0x72,0x61,0x67,0x5f,0x63,0x6f,0x6c,0x6f,0x72,
    0x20,0x5b,0x5b,0x63,0x6f,0x6c,0x6f,0x72,0x28,0x30,0x29,0x5d,0x5d,0x3b,0x0a,0x7d,
    0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,
    0x69,0x6e,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,
    0x76,0x65,0x72,0x74,0x5f,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x5b,0x5b,0x75,0x73,0x65,
    0x72,0x28,0x6c,0x6f,0x63,0x6e,0x30,0x29,0x5d,0x5d,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,
    0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,0x30,0x20,0x22,0x22,0x0a,0x66,0x72,0x61,0x67,
    0x6d,0x65,0x6e,0x74,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x6f,0x75,0x74,0x20,0x6d,
    0x61,0x69,0x6e,0x30,0x28,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x69,0x6e,0x20,0x69,0x6e,
    0x20,0x5b,0x5b,0x73,0x74,0x61,0x67,0x65,0x5f,0x69,0x6e,0x5d,0x5d,0x29,0x0a,0x7b,
    0x0a,0x20,0x20,0x20,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x6f,0x75,0x74,0x20,0x6f,
    0x75,0x74,0x20,0x3d,0x20,0x7b,0x7d,0x3b,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,
    0x30,0x20,0x22,0x22,0x0a,0x20,0x20,0x20,0x20,0x6f,0x75,0x74,0x2e,0x66,0x72,0x61,
    0x67,0x5f,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x69,0x6e,0x2e,0x76,0x65,0x72,
    0x74,0x5f,0x63,0x6f,0x6c,0x6f,0x72,0x3b,0x0a,0x20,0x20,0x20,0x20,0x72,0x65,0x74,
    0x75,0x72,0x6e,0x20,0x6f,0x75,0x74,0x3b,0x0a,0x7d,0x0a,0x0a,0x00,
};
static const sg_shader_desc app_shader_desc_metal_ios = {
  0, /* _start_canary */
  { /*attrs*/{"position","TEXCOORD",0},{"color","TEXCOORD",1},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}, },
  { /* vs */
    vs_source_metal_ios, /* source */
    0,  /* bytecode */
    0,  /* bytecode_size */
    "main0", /* entry */
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
    fs_source_metal_ios, /* source */
    0,  /* bytecode */
    0,  /* bytecode_size */
    "main0", /* entry */
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
#endif /* SOKOL_METAL */
#if !defined(SOKOL_GFX_INCLUDED)
  #error "Please include sokol_gfx.h before ios.h"
#endif
static inline const sg_shader_desc* app_shader_desc(void) {
    #if defined(SOKOL_METAL)
    if (sg_query_backend() == SG_BACKEND_METAL_IOS) {
        return &app_shader_desc_metal_ios;
    }
    #endif /* SOKOL_METAL */
    return 0; /* can't happen */
}
