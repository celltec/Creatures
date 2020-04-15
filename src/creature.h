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
	cpBool selected;

	// todo: is making a function table here usefull?
	// todo: state machine: idle, hunting, etc

} Creature;

Creature* Spawn(const cpVect pos, const cpFloat size);
void Survive(Creature*);
void Draw(Creature*);
void Kill(Creature*);

#endif /* CREATURE_H */
