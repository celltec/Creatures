#include "chipmunk/chipmunk.h"

#define SOKOL_IMPL
#include "sokol.h"
#include "free.h"
#include "draw.h"
#include "utils.h"
#include "creature.h"

#define AMOUNT 15

// todo: dynamic heap allocation
static Creature creatures[AMOUNT];

static cpSpace* space; // todo: put in environment (eine globale struct in der space, timestep, und alle scale/translate Koordinaten drin sind)
static const cpFloat timeStep = 1.0 / 60.0;  /* For 60 Hz */

static void Init(void);
static void Frame(void);
static void Event(const sapp_event*);
static void Cleanup(void);

int main(void) // todo: config via arguments
{
	stm_setup();

	sapp_desc app = {
		.init_cb = Init,
		.frame_cb = Frame,
		.event_cb = Event,
		.cleanup_cb = Cleanup,
		.width = 1200,
		.height = 1000,
		.fullscreen = cpFalse,
		.high_dpi = cpTrue,
		.sample_count = 4,  /* MSAA */
		.window_title = "Creatures",
	};

	return sapp_run(&app);
}

static void Init(void)
{
	srand((int)stm_now());

	/* Initialize sokol */
	sg_desc desc = { 0 };
	sg_setup(&desc);
	cpAssertHard(sg_isvalid(), "failed to initialize sokol_gfx");

	InitDraw();

	/* Initialize the global space */
	space = cpSpaceNew();
	cpSpaceSetDamping(space, 0.000001);        /* Bodies shouldn't retain their velocity */
	cpSpaceSetCollisionBias(space, 0.000001);  /* Push apart overlapping bodies very fast */

	/* Spawn some creatures for testing */
	for (int i = 0; i < AMOUNT; ++i)
	{
		/* Create instance */
		Creature creature = Spawn();

		/* Register components */
		creatures[i] = creature;
		cpSpaceAddBody(space, cpShapeGetBody(creature.shape));
		cpSpaceAddShape(space, creature.shape);
	}
}

/* For testing */
static cpVect target;

static void Frame(void)
{
	/* Calculate physics */
	cpSpaceStep(space, timeStep);

	TransformScreen(); // todo: change this

	for (int i = 0; i < AMOUNT; ++i)
	{
		cpBody* body = cpShapeGetBody((creatures + i)->shape);

		(creatures + i)->energy -= 0.1 / cpBodyGetMass(body);  /* 0.1 gives enough time to live */

		/* Target stuff only for testing */
		if (cpvnear(cpBodyGetPosition(body), (creatures + i)->target, 1 + cpBodyGetMass(body)))
		{
			target = randomVector(250);

			(creatures + i)->energy = 100;
			(creatures + i)->mobility += 50;
			(creatures + i)->color = randomColor();
		}
	}

	for (int i = 0; i < AMOUNT; ++i)
	{
		(creatures + i)->target = target;

		if ((creatures + i)->energy < 0)
		{
			/* Creature is dead and becomes a ghost */
			(creatures + i)->color.a = 0.1;
			(creatures + i)->mobility = 100;
		}

		Update(creatures + i);
		Draw(creatures + i);
	}

	FlushScreen(); // todo: change this
}

static void Event(const sapp_event* event)
{
	if (event->type == SAPP_EVENTTYPE_KEY_DOWN)
	{
		switch (event->key_code)
		{
		case SAPP_KEYCODE_ESCAPE:
			exit(0);
			break;
		default:
			break;
		}
	}
}

static void Cleanup(void)
{
	FreeAllChildren(space);
	cpSpaceFree(space);
	sg_shutdown();
}
