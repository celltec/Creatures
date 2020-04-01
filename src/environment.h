#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "chipmunk/chipmunk_private.h"

typedef struct {
	cpSpace* space;
	cpArray* creatures;
	cpFloat timeStep;

	struct {
		cpVect offset;
		cpFloat scale;
		cpBool ready;
	} view;

	struct {
		cpVect pos;
		cpBool leftPressed;
		cpBool rightPressed;
	} mouse;
} Environment;

Environment* NewEnvironment(void);

#endif /* ENVIRONMENT_H */
