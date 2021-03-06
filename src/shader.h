#ifndef SHADER_H
#define SHADER_H

#include "sokol.h"
#include "color.h"

#define MSAA 4

typedef struct {
	float vpMatrix[16];
} Uniform;

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
void ConstructFrame(cpTransform* matrix, cpFloat scale, cpVect offset);

void DrawDot(cpVect position, cpFloat size, Color color);
void DrawLine(cpVect a, cpVect b, cpFloat radius, Color color);
void DrawPolygon(int corners, const cpVect* vertices, cpFloat size, Color color, Color highlight);

#endif /* SHADER_H */
