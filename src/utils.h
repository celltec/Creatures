#ifndef UTILS_H
#define UTILS_H

#include "color.h"
#include "creature.h"

Color randomColor(void);
cpFloat randomRange(cpFloat min, cpFloat max);
cpVect randomVector(int maxLenth);
uint32_t rand32(uint32_t seed);

/* Dynamic array, not a linked list */
typedef struct {
	int count;
	Creature** list;
} CreatureList;

typedef void (*kill_cb)(Creature*);

CreatureList* NewList(void);
void Add(CreatureList*, Creature*);
void Remove(CreatureList*, Creature*, kill_cb);
void RemoveAll(CreatureList*, kill_cb);
void FreeList(CreatureList*);

#endif /* UTILS_H */
