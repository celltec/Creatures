#include "chipmunk/chipmunk.h"

#include "utils.h"

cpFloat randomRange(cpFloat min, cpFloat max)
{
	return min + rand32(rand()) / ((cpFloat)UINT32_MAX / (max - min) + 1);
}

cpVect randomVector(int maxLenth)
{
	return cpvmult(cpvforangle(randomRange(0.0, 2.0 * CP_PI)), rand32(rand()) % maxLenth);
}

Color randomColor(void)
{
	return (Color) { randomRange(0.0, 1.0), randomRange(0.0, 1.0), randomRange(0.0, 1.0), 1.0 };
}

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

List* New(void)
{
	return (List*)cpcalloc(1, sizeof(List));
}

void Add(List* list, void* data)
{
	/* Allocate one new slot at the end of the list */
	list->count++;
	list->list = (void**)cprealloc(list->list, list->count * sizeof(void*));

	/* Put the data in that slot */
	list->list[list->count - 1] = data;
}

void Remove(List* list, void* data, free_cb func)
{
	for (int i = 0; i < list->count; ++i)
	{
		/* Search for data */
		if (list->list[i] == data)
		{
			RemoveAt(list, i, func);
			return;  /* Leave loop early */
		}
	}
}

void RemoveAt(List* list, int index, free_cb func)
{
	/* Optional callback to free memory */
	if (func)
	{
		func(list->list[index]);
	}

	list->count--;

	if (list->count == 0)
	{
		/* List is empty */
		cpfree(list->list);
		list->list = NULL;
		return;
	}

	/* Override the data with data at the end of the list */
	list->list[index] = list->list[list->count];

	/* Remove reference to that data at the end */
	list->list[list->count] = NULL;

	/* Reduce allocation */
	list->list = (void**)cprealloc(list->list, list->count * sizeof(void*));
}

void RemoveAll(List* list, free_cb free)
{
	const int count = list->count;

	for (int i = 0; i < count; ++i)
	{
		/* Always remove the first element */
		RemoveAt(list, 0, free);
	}
}

void Delete(List* list)
{
	if (!list) return;
	if (list->count > 0) RemoveAll(list, NULL);
	cpfree(list);
}
