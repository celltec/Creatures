#include "chipmunk/chipmunk.h"

#include "draw.h"
#include "utils.h"
#include "creature.h"

Creature Spawn(void)
{
	// todo: make circle if more than 10 corners or something

	/* For testing */
	int corners = (int)randomRange(4, 6);
	if (corners == 5) corners = 6;

#if (__STDC_VERSION__ == 199901L)
	cpVect vertices[corners]; /* Only C99 */
#else
	cpVect* vertices = (cpVect*)alloca(corners * sizeof(cpVect));
#endif

	/* Some random values for testing */
	cpFloat size = randomRange(2.0, 20.0);
	cpVect pos = randomVector(300);
	cpFloat mobility = randomRange(500, 1000);
	Color color = randomColor();

	// todo: put in own function
	for (int i = 0; i < corners; ++i)
	{
		/* For testing (to look better) */
		if (i == corners / 2)
			size *= 2.5;
		if (i == corners / 2 + 1)
			size /= 2.5;

		/* Calculate vertecies for polygon */
		cpFloat angle = CP_PI * 2.0f * i / corners;
		vertices[i] = cpvmult(cpvforangle(angle), size);
	}

	/* Create object */
	cpBody* body = cpBodyNew(size, cpMomentForPoly(size, corners, vertices, cpvzero, 1.0));
	cpShape* shape = cpPolyShapeNew(body, corners, vertices, cpTransformIdentity, 1.0);
	
	/* Set initial state */
	cpBodySetPosition(body, pos);
	cpBodySetAngle(body, randomRange(0.0, 2.0 * CP_PI));

	return (Creature) {
		.shape = shape,
		.energy = 100.0,
		.mobility = mobility,
		.color = color
	};
}

void Update(Creature* this)
{
	cpBody* body = cpShapeGetBody(this->shape);

	/* Apply Forces */
	cpBodyApplyForceAtLocalPoint(body, cpv(this->mobility * cpfsqrt(cpBodyGetMass(body)), 0.0), cpBodyGetCenterOfGravity(body));
	cpBodySetTorque(body, this->mobility * cpvtoangle(cpBodyWorldToLocal(body, this->target)) * cpfpow(cpBodyGetMass(body) / 3.0, 2.0));  /* [magic number] pow(mass/3,2) looks better */
}

void Draw(Creature* this)
{
	DrawPolygon(this->shape, this->color);

	/* For testing */
	DrawDot(this->target, 5.0, black);
}

void Destroy(Creature* this)
{
	// todo: implement
}
