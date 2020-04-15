#ifdef DEBUG
#include <stdio.h>
#endif

#include "chipmunk/chipmunk.h"
#include "sokol.h" // todo: include only sokol_app.h
#include "creature.h"
#include "input.h"

static cpVect MouseToSpace(Environment* world, const sapp_event* event);
static void SelectCreature(Environment*, const cpVect);

void Event(const sapp_event* event, Environment* world)
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

		default:
			break;
		}
	} break;

	case SAPP_EVENTTYPE_MOUSE_DOWN:
	{
		/* Store mouse coordinates */
		world->mouse->pos = MouseToSpace(world, event);

#ifdef DEBUG
		printf("Click (%.0f, %.0f)\n\n", world->mouse->pos.x, world->mouse->pos.y);
#endif

		if (event->mouse_button == SAPP_MOUSEBUTTON_LEFT)
		{
			world->mouse->leftPressed = cpTrue;

			/* Release creature to start manually panning again */
			if (world->selectedCreature)
			{
				world->selectedCreature->selected = cpFalse;
				world->selectedCreature = NULL;
			}
		}
		else if (event->mouse_button == SAPP_MOUSEBUTTON_RIGHT)
		{
			world->mouse->rightPressed = cpTrue;

			/* For testing */
			if (world->selectedCreature)
				world->selectedCreature->mobility = 0;
		}
	} break;

	case SAPP_EVENTTYPE_MOUSE_UP:
	{
		if (event->mouse_button == SAPP_MOUSEBUTTON_LEFT)
		{
			if (world->mouse->leftPressed && !world->view->moved)
			{
				SelectCreature(world, MouseToSpace(world, event));
			}

			world->view->moved = cpFalse;
			world->mouse->leftPressed = cpFalse;
		}
		else if (event->mouse_button == SAPP_MOUSEBUTTON_RIGHT)
		{
			world->mouse->rightPressed = cpFalse;
		}
	} break;

	case SAPP_EVENTTYPE_MOUSE_MOVE:
	{
		if (world->mouse->leftPressed)
		{
			cpVect direction = cpvsub(MouseToSpace(world, event), world->mouse->pos);

			if (world->view->ready)  /* Prevent multiple executions per frame */
			{
				/* Move view */
				world->view->offset = cpvadd(world->view->offset, direction);
				world->view->moved = cpTrue;
				world->view->ready = cpFalse;
			}
		}
	} break;

	case SAPP_EVENTTYPE_MOUSE_SCROLL:
	{
		/* Some arbitrary scroll limits */
		static const float min = 0.005f;  /* Theoretically open to be smaller */
		static const float max = 20.0f;    /* The smallest creature is already big enough at this scale */

		if (world->view->ready)  /* Prevent multiple executions per frame */
		{
			cpFloat factor = 1.0f + event->scroll_y / 10.0f;  /* Make smaller scrolling steps */

			/* Modify zoom */
			world->view->targetScale = cpfclamp(world->view->targetScale * factor, min, max);

			// todo: ask floooh to change sokol_app.h on line 4303, because i need mouse pos with scroll event
			// todo: zoom to mouse position (do after shader refactoring)

			world->view->ready = cpFalse;
		}
	} break;

	default:
		break;
	}
}

// todo: put in environment? VP matrix is also there
static cpVect MouseToSpace(Environment* world, const sapp_event* event)
{
	/* Calculate clip coordinates for mouse */
	cpVect unitVect = cpv(2.0 * event->mouse_x / sapp_width() - 1.0, 1.0 - 2.0 * event->mouse_y / sapp_height());

	/* Use the VP matrix to transform to world space */
	return cpTransformPoint(cpTransformInverse(world->view->transform), unitVect);
}

static void SelectCreature(Environment* world, const cpVect pos)
{
	cpShape* nearest = cpSpacePointQueryNearest(world->space, pos, 200.0, CP_SHAPE_FILTER_ALL, NULL);  /* You don't have to click so exactly with a 200 radius */

	if (!nearest) return;

	for (int i = 0; i < world->creatures->count; ++i)
	{
		Creature* creature = world->creatures->list[i];

		if (creature->shape == nearest)
		{
			creature->selected = cpTrue;
			world->selectedCreature = creature;

#ifdef DEBUG
			cpVect pos = cpBodyGetPosition(cpShapeGetBody(creature->shape));
			printf("Select:\n pos: (%.0f, %.0f)\n size: %.0f\n energy: %.0f\n health: %.0f\n mobility: %.0f\n\n", pos.x, pos.y, creature->size, creature->energy, creature->health, creature->mobility);
#endif

			break; // todo: scaling
		}
	}
}

