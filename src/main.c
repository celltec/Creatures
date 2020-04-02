#include "chipmunk/chipmunk.h"

#define SOKOL_IMPL
#include "sokol.h"
#include "test.h"
#include "free.h"
#include "draw.h"
#include "utils.h"
#include "shader.h"
#include "creature.h"
#include "environment.h"

#define AMOUNT 500

static Environment* world;

static void Init(void);
static void Update(void);
static void Event(const sapp_event*);
static void Cleanup(void);

int main(void)
{
	stm_setup();

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
	Add(world->creatures, creature);
	cpSpaceAddBody(world->space, cpShapeGetBody(creature->shape));
	cpSpaceAddShape(world->space, creature->shape);
#ifdef DEBUG
	cpVect pos = cpBodyGetPosition(cpShapeGetBody(creature->shape));
	printf("Spawned a creature:\n pos: (%.0f, %.0f)\n size: %.0f\n mobility: %.0f\n\n", pos.x, pos.y, creature->size, creature->mobility);
#endif
}

static void Init(void)
{
#ifdef DEBUG
	printf("Started\n\n");
#endif
	InitGfx();
	srand((int)stm_now());

	world = NewEnvironment();

#ifdef DEBUG
	Test();
#endif

	/* Spawn some creatures for testing */
	for (int i = 0; i < AMOUNT; ++i)
	{
		NewCreature();
	}
}

static void FollowCreature(void)  // todo: smooth transition
{
	if (world->selectedCreature)
	{
		world->view.offset = cpvneg(cpBodyGetPosition(cpShapeGetBody(world->selectedCreature->shape)));
	}
}

static void SmoothScaling(void)
{
	static const int scrollResistance = 10;  /* Slow down scrolling to look nicer  */

	cpFloat difference = world->view.scale - world->view.targetScale;
	world->view.scale -= difference / scrollResistance;

	if (cpfabs(difference) < world->view.scale / scrollResistance)  /* Some relative value that looks good */
	{
		world->view.targetScale = world->view.scale;  /* Stop early to prevent changing forever */
	}
}

static void Update(void)
{
	/* Calculate physics */
	cpSpaceStep(world->space, world->timeStep);

	FollowCreature();
	SmoothScaling();

	TransformScreen(world->view.scale, world->view.offset);
	world->view.ready = cpTrue;

	for (int i = 0; i < world->creatures->count; ++i)
	{
		Creature* creature = world->creatures->list[i];

		Survive(creature);
		Draw(creature);

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

	FlushScreen();
}

static cpVect MouseToSpace(const sapp_event* event)  // todo: put in environment? VPMatrix should also be there
{
	/* Calculate clip coordinates for mouse */
	cpVect unitVect = cpv(2.0 * event->mouse_x / sapp_width() - 1.0, 1.0 - 2.0 * event->mouse_y / sapp_height());

	/* Use the VP matrix to transform to world space */
	return cpTransformPoint(cpTransformInverse(ChipmunkDebugDrawVPMatrix), unitVect);
}

static void SelectCreature(const cpVect pos)
{
	cpShape *nearest = cpSpacePointQueryNearest(world->space, pos, 0.0, CP_SHAPE_FILTER_ALL, NULL);
	
	if (!nearest) return;

	for (int i = 0; i < world->creatures->count; ++i)
	{
		Creature* creature = world->creatures->list[i];

		if (creature->shape == nearest)
		{
			world->selectedCreature = creature;
#ifdef DEBUG
			cpVect pos = cpBodyGetPosition(cpShapeGetBody(creature->shape));
			printf("Select:\n pos: (%.0f, %.0f)\n size: %.0f\n energy: %.0f\n health: %.0f\n mobility: %.0f\n\n", pos.x, pos.y, creature->size, creature->energy, creature->health, creature->mobility);
#endif
			break; // todo: scaling
		}
	}
}

static void Event(const sapp_event* event)
{
	switch (event->type)
	{
	case SAPP_EVENTTYPE_KEY_DOWN:
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

		case SAPP_KEYCODE_T:
			Test();
			break;

		default:
			break;
		}
	} break;

	case SAPP_EVENTTYPE_MOUSE_DOWN:
	{
		/* Store mouse coordinates */
		world->mouse.pos = MouseToSpace(event);
#ifdef DEBUG
		printf("Click (%.0f, %.0f)\n\n", world->mouse.pos.x, world->mouse.pos.y);
#endif

		if (event->mouse_button == SAPP_MOUSEBUTTON_LEFT)
		{
			world->mouse.leftPressed = cpTrue;

			/* Release creature to start manually panning (again) */
			world->selectedCreature = NULL;

			SelectCreature(MouseToSpace(event));
		}
		else if (event->mouse_button == SAPP_MOUSEBUTTON_RIGHT)
		{
			world->mouse.rightPressed = cpTrue;
		}
	} break;

	case SAPP_EVENTTYPE_MOUSE_UP:
	{
		if (event->mouse_button == SAPP_MOUSEBUTTON_LEFT)
		{
			world->mouse.leftPressed = cpFalse;
		}
		else if (event->mouse_button == SAPP_MOUSEBUTTON_RIGHT)
		{
			world->mouse.rightPressed = cpFalse;
		}
	} break;

	case SAPP_EVENTTYPE_MOUSE_MOVE:
	{
		if (world->mouse.leftPressed)
		{
			cpVect direction = cpvsub(MouseToSpace(event), world->mouse.pos);

			if (world->view.ready)  /* Prevent multiple executions per frame */
			{
				/* Move view */
				world->view.offset = cpvadd(world->view.offset, direction);
				world->view.ready = cpFalse;
			}
		}
	} break;

	case SAPP_EVENTTYPE_MOUSE_SCROLL:
	{
		/* Some arbitrary scroll limits */
		static const float min = 0.005f;  /* Theoretically open to be smaller */
		static const float max = 20.0f;    /* The smallest creature is already big enough at this scale */

		if (world->view.ready)  /* Prevent multiple executions per frame */
		{
			cpFloat factor = 1.0f + event->scroll_y / 10.0f;  /* Make smaller scrolling steps */

			/* Modify zoom */
			world->view.targetScale = cpfclamp(world->view.targetScale * factor, min, max);
			
			// todo: ask floooh to change sokol_app.h on line 4303, because i need mouse pos with scroll event
			// todo: zoom to mouse position (do after shader refactoring)

			world->view.ready = cpFalse;
		}
	} break;

	default:
		break;
	}
}

static void Cleanup(void)
{
	FreeAllChildren(world->space);
	cpSpaceFree(world->space);
	FreeList(world->creatures);
	cpfree(world);
	sg_shutdown();
#ifdef DEBUG
	printf("Shutdown\n\n");
#endif
}
