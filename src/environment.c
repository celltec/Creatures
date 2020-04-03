#include "chipmunk/chipmunk.h"

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
	
	environment->space = space;
	environment->creatures = NewList();
	environment->timeStep = 1.0 / 60.0;    /* For 60 Hz */
	environment->view.scale = 0.5;
	environment->view.targetScale = 0.05;  /* Zoom out in the beginning */
}
