#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "utils.h"
#include "creature.h"

typedef struct {
	int seed; // todo: rename to 'user' and use chars as value?
	int age;  /* Set only when world is saved */ // todo: use as evolution factor
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
void InitEnvironment(Environment*);

#endif /* ENVIRONMENT_H */
