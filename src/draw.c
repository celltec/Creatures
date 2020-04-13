#include "chipmunk/chipmunk.h"
#include "chipmunk/chipmunk_structs.h"
#include "shader.h"
#include "draw.h"

void DrawShape(cpShape* shape, Color color)
{
	/* Cast to poly shape */
	cpPolyShape* poly = (cpPolyShape*)shape;

	/* Get planes */
	int corners = poly->count;
	struct cpSplittingPlane* planes = poly->planes;

#if (__STDC_VERSION__ == 199901L)
	hmm_vec2 vertices[corners];  /* Only C99 */
#else
	hmm_vec2* vertices = (hmm_vec2*)alloca(corners * sizeof(hmm_vec2));
#endif

	/* Store vertices in HMM format */
	for (int i = 0; i < corners; ++i)
	{
		vertices[i].X = (float)planes[i].v0.x;
		vertices[i].Y = (float)planes[i].v0.y;
	}

	DrawPolygon(corners, vertices, color);
}
