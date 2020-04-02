#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "utils.h"
#include "creature.h"

typedef struct {
	cpSpace* space;
	List* creatures;
	cpFloat timeStep;
	Creature* selectedCreature;

	struct {
		cpVect offset;
		cpVect targetOffset;
		cpFloat scale;
		cpFloat targetScale;
		cpBool moved;
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
