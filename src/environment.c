#include "chipmunk/chipmunk.h"
#include "sokol.h"
#include "free.h"
#include "environment.h"

Environment* NewEnvironment(void)
{
	return (Environment*)cpcalloc(1, sizeof(Environment));
}

void InitEnvironment(Environment* environment)
{
	/* Create new space and set properties */
	cpSpace* space = cpSpaceNew();
	cpSpaceSetDamping(space, 0.0);        /* Bodies shouldn't retain their velocity */
	cpSpaceSetCollisionBias(space, 0.0);  /* Push apart overlapping bodies very fast */
	
	/* Parse URL or command line arguments */
	if (sargs_exists("seed"))
	{
		environment->seed = atoi(sargs_value("seed"));
	}
	else
	{
		environment->seed = (int)stm_now();
	}

	srand(environment->seed);

	environment->space = space;
	environment->creatures = NewList();

	environment->view = (View*)cpcalloc(1, sizeof(View));
	environment->mouse = (Mouse*)cpcalloc(1, sizeof(Mouse));

	environment->timeStep = 1.0 / 60.0;  /* For 60 Hz */

	/* Zoom in the beginning */
	environment->view->scale = 0.01;
	environment->view->targetScale = 0.3;
}

void DestroyEnvironment(Environment* environment)
{
	FreeAllChildren(environment->space);
	cpSpaceFree(environment->space);
	Delete(environment->creatures);
	cpfree(environment->view);
	cpfree(environment->mouse);
	cpfree(environment);
}

