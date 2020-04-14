#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "utils.h"
#include "creature.h"

typedef struct {
	cpTransform transform;
	cpVect offset;
	cpVect targetOffset;
	cpFloat scale;
	cpFloat targetScale;
	cpBool moved;
	cpBool ready;
} View;

typedef struct {
	cpVect pos;
	cpBool leftPressed;
	cpBool rightPressed;
} Mouse;

typedef struct {
	int seed; // todo: rename to 'user' and use chars as value?
	int age;  /* Set only when world is saved */ // todo: use as evolution factor
	cpSpace* space;
	List* creatures;
	cpFloat timeStep;
	Creature* selectedCreature;
	View* view;
	Mouse* mouse;
} Environment;

Environment* NewEnvironment(void);
void InitEnvironment(Environment*);

#endif /* ENVIRONMENT_H */
