#include "chipmunk/chipmunk.h"

#define SOKOL_IMPL
#include "sokol.h"
#include "free.h"
#include "draw.h"
#include "utils.h"
#include "shader.h"
#include "creature.h"
#include "environment.h"

#include <stdio.h>

#define AMOUNT 100

static Environment* world;

static void Init(void);
static void Update(void);
static void Event(const sapp_event*);
static cpVect MouseToSpace(const sapp_event* event);
static void Cleanup(void);

int main(void)
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

	TransformScreen(world->view.scale, world->view.offset); // todo: change this

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

	world->view.ready = cpTrue;
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

		default:
			break;
		}
	} break;

	case SAPP_EVENTTYPE_MOUSE_DOWN:
	{
		/* Store mouse coordinates */
		world->mouse.pos = MouseToSpace(event);

		if (event->mouse_button == SAPP_MOUSEBUTTON_LEFT)
		{
			// todo: select creature
			world->mouse.leftPressed = cpTrue;
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
		if (world->mouse.rightPressed)
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
		/* Some scroll limit */
		const float scrollMin = 0.001f;
		const float scrollMax = 20.0f;
		const float scrollIntensity = 20.0f;

		/* Modify zoom */
		world->view.scale = cpfclamp(world->view.scale * (1.0f + event->scroll_y / scrollIntensity), scrollMin, scrollMax);
	} break;

	default:
		break;
	}
}

static cpVect MouseToSpace(const sapp_event* event) // todo: put in environment? because if the VPMatrix is also there...
{
	/* Calculate clip coordinates for mouse */
	cpVect clipCoord = cpv(2.0 * event->mouse_x / sapp_width() - 1.0, 1.0 - 2.0 * event->mouse_y / sapp_height());

	/* Use the VP matrix to transform to world space */
	return cpTransformPoint(cpTransformInverse(ChipmunkDebugDrawVPMatrix), clipCoord);
}

static void Cleanup(void)
{
	FreeAllChildren(world->space);
	cpSpaceFree(world->space);
	sg_shutdown();
}
