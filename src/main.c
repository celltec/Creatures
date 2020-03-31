#include "chipmunk/chipmunk.h"

#define SOKOL_IMPL
#include "sokol.h"
#include "free.h"
#include "draw.h"
#include "utils.h"
#include "shader.h"
#include "creature.h"
#include "environment.h"

#define AMOUNT 100

static Environment* world;

static void Init(void);
static void Update(void);
static void Event(const sapp_event*);
static void Cleanup(void);

int main(void) // todo: config via arguments
{
	stm_setup();
	srand((int)stm_now());

	sapp_desc app = {
		.init_cb = Init,
		.frame_cb = Update,
		.event_cb = Event,
		.cleanup_cb = Cleanup,
		.width = 800,
		.height = 800,
		.fullscreen = cpFalse,
		.high_dpi = cpTrue,
		.sample_count = 4,  /* MSAA */
		.window_title = "Creatures",
	};

	return sapp_run(&app);
}

static void NewCreature(void)
{
	/* Create instance */
	Creature* creature = Spawn();

	/* Register components */
	cpArrayPush(world->creatures, creature);
	cpSpaceAddBody(world->space, cpShapeGetBody(creature->shape));
	cpSpaceAddShape(world->space, creature->shape);
}

static void Init(void)
{
	InitGfx();

	world = NewEnvironment();

	/* Spawn some creatures for testing */
	for (int i = 0; i < AMOUNT; ++i)
	{
		NewCreature();
	}
}

static void Update(void)
{
	/* Calculate physics */
	cpSpaceStep(world->space, world->timeStep);

	TransformScreen(world->viewScale, world->viewTranslate); // todo: change this

	for (int i = 0; i < world->creatures->num; ++i)
	{
		Creature* creature = (Creature*)world->creatures->arr[i];

		Survive(creature);
		Draw(creature);

		/* For testing */
		//DrawDot(creature->target, 10.0, black);
	}

	/* Check the creatures health separately to avoid changing the list mid-loop */
	for (int i = 0; i < world->creatures->num; ++i)
	{
		Creature* creature = (Creature*)world->creatures->arr[i];

		if (creature->energy < 0.0)
		{
			/* Creature dies :( */
			Kill(creature);
			cpArrayDeleteObj(world->creatures, creature);
		}
	}

	FlushScreen(); // todo: change this
}

static void Event(const sapp_event* event)
{
	if (event->type == SAPP_EVENTTYPE_KEY_DOWN)
	{
		switch (event->key_code)
		{
		/* Exit the programm with escape */
		case SAPP_KEYCODE_ESCAPE:
			exit(0);
			break;

		/* Add a creature with spacebar */
		case SAPP_KEYCODE_SPACE:
			NewCreature();
			break;

		default:
			break;
		}
	}
	else if (event->type == SAPP_EVENTTYPE_MOUSE_SCROLL)
	{
		/* Some scroll limit */
		const float scrollMin = 0.1;
		const float scrollMax = 20.0;
		const float scrollIntensity = 20.0;

		world->viewScale = cpfclamp(world->viewScale * (1.0 + event->scroll_y / scrollIntensity), scrollMin, scrollMax);
	}
}

static void Cleanup(void)
{
	FreeAllChildren(world->space);
	cpSpaceFree(world->space);
	sg_shutdown();
}
