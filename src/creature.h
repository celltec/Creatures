#ifndef CREATURE_H
#define CREATURE_H

#include "color.h"

typedef struct {
	cpShape* shape;
	cpFloat size;
	cpFloat energy;
	cpFloat health;
	cpFloat mobility;
	cpVect target;
	Color color;
	int age;

	// todo: is making a function table here usefull?
	// todo: make state machine: idle, hunting, etc

} Creature;

Creature* Spawn(void);
void Survive(Creature* this);
void Kill(Creature*);
void Draw(Creature*);

#endif /* CREATURE_H */
