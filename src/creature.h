#ifndef CREATURE_H
#define CREATURE_H

#include "color.h"

typedef struct {
	cpShape* shape;
	cpFloat energy;
	cpFloat mobility;
	cpVect target;
	Color color;
} Creature;

Creature Spawn(void);
void Update(Creature*);
void Draw(Creature*);
void Destroy(Creature*);

#endif /* CREATURE_H */
