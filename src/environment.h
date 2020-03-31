#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "chipmunk/chipmunk_private.h"

typedef struct {
	cpSpace* space;
	cpArray* creatures;
	cpFloat timeStep;
	cpFloat viewScale;
	cpVect viewTranslate;
	// todo: coordinates
} Environment;

Environment* NewEnvironment(void);

#endif /* ENVIRONMENT_H */
