#include "chipmunk/chipmunk.h"
#include "chipmunk/chipmunk_structs.h"
#include "shader.h"
#include "draw.h"

void DrawShape(cpShape* shape, Color color, cpBool highlight)
{
	/* Cast to poly shape */
	cpPolyShape* poly = (cpPolyShape*)shape;

	float size = poly->r;
	int corners = poly->count;

	/* Get planes */
	struct cpSplittingPlane* planes = poly->planes;

#if (__STDC_VERSION__ == 199901L)
	cpVect vertices[corners];  /* Only C99 */
#else
	cpVect* vertices = (cpVect*)alloca(corners * sizeof(cpVect));
#endif

	for (int i = 0; i < corners; ++i)
	{
		vertices[i] = planes[i].v0;
	}

	Color highlightColor = { 0 };

	if (highlight)
	{
		highlightColor = black;
	}

	DrawPolygon(corners, vertices, size, color, highlightColor);
}
