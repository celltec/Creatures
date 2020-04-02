#include "chipmunk/chipmunk.h"

#include "utils.h"

/* Lehmer random number generator */
uint32_t rand32(uint32_t seed)
{
	seed += 0xe120fc15;
	uint64_t tmp;
	tmp = (uint64_t)seed * 0x4a39b70d;
	uint32_t m1 = (uint32_t)((tmp >> 32) ^ tmp);
	tmp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (uint32_t)((tmp >> 32) ^ tmp);
	return m2;
}

Color randomColor(void)
{
	return (Color) { randomRange(0.0, 1.0), randomRange(0.0, 1.0), randomRange(0.0, 1.0), 1.0 };
}

cpFloat randomRange(cpFloat min, cpFloat max)
{
	return min + rand32(rand()) / ((cpFloat)UINT32_MAX / (max - min) + 1);
}

cpVect randomVector(int maxLenth)
{
	return cpvmult(cpvforangle(randomRange(0.0, 2.0 * CP_PI)), rand32(rand()) % maxLenth);
}

CreatureList* NewList(void)
{
	return (CreatureList*)cpcalloc(1, sizeof(CreatureList));
}

void Add(CreatureList* list, Creature* creature)
{
	// todo: max counter to prevent unnecessary allocations when there are open slots at the end
	list->count++;
	list->list = (Creature**)cprealloc(list->list, list->count * sizeof(Creature*));
	list->list[list->count - 1] = creature;
}

void Remove(CreatureList* list, Creature* creature, kill_cb kill)
{
	for (int i = 0; i < list->count; ++i)
	{
		/* Search for creature */
		if (list->list[i] == creature)
		{
			list->count--;

			/* Move last item to current position */
			list->list[i] = list->list[list->count];

			/* Remove reference */
			list->list[list->count] = NULL;

			/* Optional callback to free memory */
			if (kill)
			{
				kill(creature);
			}

			return;
		}
	}
}

void RemoveAll(CreatureList* list, kill_cb kill)
{
	int count = list->count;

	for (int i = 0; i < count; ++i)
	{
		/* Always remove the first element */
		Remove(list, list->list[0], kill);
	}
}

void FreeList(CreatureList* list)
{
	if (list)
	{
		cpfree(list->list);
		list->list = NULL;
		cpfree(list);
	}
}
