#ifndef SHADER_H
#define SHADER_H

#include "sokol.h"
#include "color.h"
#include "HandmadeMath.h"

#if defined(SOKOL_GLCORE33)
#include "../glsl/glcore330.h"
#elif defined(SOKOL_GLES2)
#include "../glsl/gles2.h"
#elif defined(SOKOL_GLES3)
#include "../glsl/gles3.h"
#elif defined(SOKOL_D3D11)
#include "../glsl/d3d11.h"
#elif defined(SOKOL_METAL)
#include "../glsl/ios.h"
#endif

void InitGfx(void);
void ConstructFrame(float scale, float x, float y);
void DrawPolygon(int corners, const hmm_vec2* vertices, float size, Color color);

#endif /* SHADER_H */
