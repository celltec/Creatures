#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_NO_SSE
#define SOKOL_IMPL

#ifdef DEBUG
#include <stdio.h>
#include "../tests/test.h"
#endif

#include "chipmunk/chipmunk.h"
#include "sokol.h"
#include "free.h"
#include "draw.h"
#include "utils.h"
#include "input.h"
#include "shader.h"
#include "creature.h"
#include "environment.h"

#define AMOUNT 10

static void Init(Environment*);
static void Update(Environment*);
static void Cleanup(Environment*);

int main(int argc, char* argv[])
{
	stm_setup();
	sargs_setup(&(sargs_desc) { argc, argv });

	sapp_desc app = {
		.user_data = NewEnvironment(),
		.init_userdata_cb = Init,
		.frame_userdata_cb = Update,
		.event_userdata_cb = Event,
		.cleanup_userdata_cb = Cleanup,
		.width = 800,
		.height = 800,
		.fullscreen = cpFalse,
		.high_dpi = cpTrue,
		.sample_count = 4,  /* MSAA */
		.window_title = "Creatures"
	};

	return sapp_run(&app);
}

static void CreateCreature(Environment* world)
{
	/* Some random values for testing */
	const cpVect pos = randomVector(300);
	const cpFloat size = randomRange(5.0, 20.0);

	/* Create instance */
	Creature* creature = Spawn(pos, size);

	/* Register components */
	Add(world->creatures, creature);
	cpSpaceAddBody(world->space, cpShapeGetBody(creature->shape));
	cpSpaceAddShape(world->space, creature->shape);
#ifdef DEBUG
	cpVect debugPos = cpBodyGetPosition(cpShapeGetBody(creature->shape));
	printf("Spawned a creature:\n pos: (%.0f, %.0f)\n size: %.0f\n mobility: %.0f\n\n", debugPos.x, debugPos.y, creature->size, creature->mobility);
#endif
}

static void Init(Environment* world)
{
#ifdef DEBUG
	printf("Started\n\n");
	Test();
#endif

	InitGfx();
	InitEnvironment(world);

	/* Spawn some creatures for testing */
	for (int i = 0; i < AMOUNT; ++i)
	{
		CreateCreature(world);
	}
}

static void FollowCreature(Environment* world) // todo: reorganize
{
	if (world->selectedCreature)
	{
		world->view->targetOffset = cpvneg(cpBodyGetPosition(cpShapeGetBody(world->selectedCreature->shape)));
	}
	else
	{
		world->view->targetOffset = world->view->offset;
	}
}

static void SmoothTranslate(Environment* world)
{
	static const int resistance = 10;

	cpVect difference = cpvsub(world->view->offset, world->view->targetOffset);

	if (cpvlength(difference) < world->view->scale / resistance)
	{
		world->view->targetOffset = world->view->offset;
		return;  /* Stop early to prevent changing forever */
	}

	/* Approach desired value by subtracting some relative value so it looks good */
	world->view->offset = cpvsub(world->view->offset, cpvmult(difference, 1.0 / resistance));
}

static void SmoothScaling(Environment* world)
{
	static const int resistance = 10;

	cpFloat difference = world->view->scale - world->view->targetScale;

	if (cpfabs(difference) < world->view->scale / resistance)
	{
		world->view->targetScale = world->view->scale;
		return;  /* Stop early to prevent changing forever */
	}

	/* Approach desired value by subtracting some relative value so it looks good */
	world->view->scale -= difference / resistance;
}

static void Update(Environment* world)
{
	/* Calculate physics */
	cpSpaceStep(world->space, world->timeStep);

	FollowCreature(world);
	SmoothScaling(world);
	SmoothTranslate(world);

	for (int i = 0; i < world->creatures->count; ++i)
	{
		Creature* creature = world->creatures->list[i];

		Survive(creature);
		Display(creature);

		/* For testing */
		//DrawDot(creature->target, 10.0, black);
	}

	/* Check the creatures health separately to avoid changing the list mid-loop */
	for (int i = 0; i < world->creatures->count; ++i)
	{
		Creature* creature = world->creatures->list[i];

		if (creature->energy < 0.0)
		{
			if (creature == world->selectedCreature)
			{
				world->selectedCreature = NULL;
			}

#ifdef DEBUG
			cpVect pos = cpBodyGetPosition(cpShapeGetBody(creature->shape));
			printf("Creature dies:\n pos: (%.0f, %.0f)\n size: %.0f\n mobility: %.0f\n\n", pos.x, pos.y, creature->size, creature->mobility);
#endif

			Remove(world->creatures, creature, Kill);
		}
	}

	ConstructFrame(&world->view->matrix, world->view->scale, world->view->offset);
	world->view->ready = cpTrue;
}

static void Cleanup(Environment* world)
{
	FreeAllChildren(world->space);
	cpSpaceFree(world->space);
	Delete(world->creatures);
	cpfree(world->view);
	cpfree(world->mouse);
	cpfree(world);
	sargs_shutdown();
	sg_shutdown();

#ifdef DEBUG
	printf("Shutdown\n\n");
#endif
}
