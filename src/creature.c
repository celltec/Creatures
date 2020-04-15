#include "chipmunk/chipmunk.h"
#include "draw.h"
#include "utils.h"
#include "color.h"
#include "creature.h"

// todo: change name
static void ChangeMobility(Creature* this, cpFloat value)
{
	/* Limit to reasonable amount */
	this->mobility = cpfclamp(this->mobility + value, 0, cpfpow(this->size, 1.0 / 3.0) * 1000);  /* Handcrafted magic factor */ // todo: change limit?
}

static void UseEnergy(Creature* this)
{
	/* Live longer with more health, bigger size and lower mobility	*/
	this->energy -= this->mobility / this->size / (this->health * 100);  /* without the *100 there's very little time */
}

static void ReplenishEnergy(Creature* this, cpFloat amount)
{
	if (amount > 0)
	{
		this->energy = cpfmin(this->energy + amount, 100.0);
	}
}

static void Damage(Creature* this, cpFloat amount)
{
	if (amount > 0)
	{
		this->health = cpfmax(this->health - amount, 0.0);
	}
}

static cpVect SeekTarget(void)
{
	/* Test target */
	return randomVector(300);
}

// todo: IMPORTANT goes in opposite direction if angle is exactly 180° (bug or feature?) [maybe make turn speed constant?]
static void Move(Creature* this)
{
	cpBody* body = cpShapeGetBody(this->shape);
	const cpVect target = cpBodyWorldToLocal(body, this->target);

	const cpFloat precision = cpfmin(cpfsqrt(cpvlength(target)) * 0.5 / cpfabs(cpvtoangle(target)), 10);  /* Handcrafted magic factor */
	cpBodyApplyForceAtLocalPoint(body, cpv(precision * this->mobility  * this->size, 0.0), cpBodyGetCenterOfGravity(body));
	cpBodySetTorque(body, cpvtoangle(target) * this->mobility * cpfpow(this->size, 2.1));  /* Handcrafted magic factor */
}

Creature* Spawn(const cpVect pos, const cpFloat size)
{
	Creature* creature = (Creature*)cpcalloc(1, sizeof(Creature));

	/* For testing */
	int corners = (int)randomRange(4, 6);
	if (corners == 5) corners = 6;

#if (__STDC_VERSION__ == 199901L)
	cpVect vertices[corners]; /* Only C99 */
#else
	cpVect* vertices = (cpVect*)alloca(corners * sizeof(cpVect));
#endif

	/* Some random values for testing */
	const cpFloat angle = randomRange(0, 2 * CP_PI);
	const cpFloat mobility = randomRange(50, 500);
	const Color color = randomColor();

	// todo: put in own function
	for (int i = 0; i < corners; ++i)
	{
		/* For testing (to look better) */
		cpFloat length = size;
		if (i == corners / 2.0)
			length *= 2.5;

		/* Calculate vertecies for polygon */
		cpFloat angle = CP_PI * 2.0f * i / corners;
		vertices[i] = cpvmult(cpvforangle(angle), length);
	}

	/* Create object */
	cpBody* body = cpBodyNew(size, cpMomentForPoly(size, corners, vertices, cpvzero, 1.0));
	cpShape* shape = cpPolyShapeNew(body, corners, vertices, cpTransformIdentity, 1.0);
	cpShapeSetFilter(shape, cpShapeFilterNew(CP_NO_GROUP, CP_ALL_CATEGORIES, CP_ALL_CATEGORIES));

	/* Set initial state */
	cpBodySetPosition(body, pos);
	cpBodySetAngle(body, angle);

	creature->shape = shape;
	creature->size = size;
	creature->energy = 100.0;
	creature->health = 100.0;
	creature->mobility = mobility;
	creature->color = color;

	return creature;
}

void Survive(Creature* this)
{
	cpBody* body = cpShapeGetBody(this->shape);

	// todo: seek target if food was seen and is big enough or something
	Move(this);
	UseEnergy(this);

	// todo: change this to state idle
	if (cpveql(this->target, cpvzero))
	{
		this->target = SeekTarget();
	}

	/* Target stuff only for testing */
	if (cpvnear(cpBodyGetPosition(body), this->target, 6.0 + this->size)) // 5 -> size of dot
	{
		/* Consume test target */
		ReplenishEnergy(this, 100.0);
		this->target = SeekTarget();
	}
}

void Display(Creature* this)
{
	DrawShape(this->shape, this->color, this->selected);
}

void Kill(Creature* this)
{
	cpSpace* space = cpShapeGetSpace(this->shape);
	cpBody* body = cpShapeGetBody(this->shape);

	/* Remove shape before freeing the body or you will access dangling pointers */
	cpSpaceRemoveShape(space, this->shape);
	cpShapeFree(this->shape);
	cpSpaceRemoveBody(space, body);
	cpBodyFree(body);

	cpfree(this);
}
