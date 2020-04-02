#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "utils.h"
#include "creature.h"

typedef struct {
	cpSpace* space;
	CreatureList* creatures;
	cpFloat timeStep;
	Creature* selectedCreature;

	struct {
		cpVect offset;
		cpFloat scale;
		cpFloat targetScale;
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
