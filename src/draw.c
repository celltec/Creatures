#include "chipmunk/chipmunk.h"
#include "chipmunk/chipmunk_structs.h"

#include "shader.h"
#include "draw.h"

static cpSpaceDebugColor ColorToSpaceDebugColor(Color c)
{
	return (cpSpaceDebugColor) { c.r, c.g, c.b, c.a };
}

void InitDraw(void)
{
	ChipmunkDebugDrawInit();
}

void DrawDot(cpVect pos, cpFloat size, Color color)
{
	ChipmunkDebugDrawDot(size, pos, ColorToSpaceDebugColor(color));
}

void DrawCircle(cpVect pos, cpFloat radius, cpFloat angle, Color color)
{
	ChipmunkDebugDrawCircle(pos, angle, radius, ColorToSpaceDebugColor(color), ColorToSpaceDebugColor(color));
}

void DrawLine(cpVect a, cpVect b, cpFloat width, Color color)
{
	ChipmunkDebugDrawFatSegment(a, b, width, ColorToSpaceDebugColor(color), ColorToSpaceDebugColor(color));
}

void DrawPolygon(cpShape* shape, Color color)
{
	/* Cast to poly shape */
	cpPolyShape* poly = (cpPolyShape*)shape;

	/* Get planes */
	int corners = poly->count;
	struct cpSplittingPlane* planes = poly->planes;

#if (__STDC_VERSION__ == 199901L)
	cpVect vertices[corners]; /* Only C99 */
#else
	cpVect* vertices = (cpVect*)alloca(corners * sizeof(cpVect));
#endif

	/* Store vertices */
	for (int i = 0; i < corners; ++i)
	{
		vertices[i] = planes[i].v0;
	}

	ChipmunkDebugDrawPolygon(corners, vertices, poly->r, ColorToSpaceDebugColor(color), ColorToSpaceDebugColor(color));
}

static sg_pass_action action = {
	.colors[0] = {.action = SG_ACTION_CLEAR, .val = { 1.0f, 1.0f, 1.0f, 1.0f } }, /* White background */
};

void TransformScreen(void) // todo: change this
{
	ChipmunkDebugDrawClearRenderer();

	cpFloat scale = 1.0;
	cpVect translate = cpvzero;

	cpVect screen_size = { sapp_width(), sapp_height() };
	cpTransform view_matrix = cpTransformMult(cpTransformScale(scale, scale), cpTransformTranslate(translate));

	float screen_scale = (float)cpfmin(screen_size.x / 640.0, screen_size.y / 480.0);
	float hw = (float)screen_size.x * (0.5f / screen_scale);
	float hh = (float)screen_size.y * (0.5f / screen_scale);
	cpTransform projection_matrix = cpTransformOrtho(cpBBNew(-hw, -hh, hw, hh));

	ChipmunkDebugDrawVPMatrix = cpTransformMult(projection_matrix, view_matrix);

	sg_begin_default_pass(&action, sapp_width(), sapp_height());
}

void FlushScreen(void) // todo: change this
{
	ChipmunkDebugDrawFlushRenderer();
	ChipmunkDebugDrawPopRenderer();

	sg_end_pass();
	sg_commit();
}
