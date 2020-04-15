#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "chipmunk/chipmunk.h"

float randomRange(float min, float max);
cpVect randomVector(int maxLenth);
uint32_t rand32(uint32_t seed);

/* Dynamic array, not a linked list */
typedef struct {
	int count;
	void** list;
} List;

typedef void (*free_cb)(void*);

List* NewList(void);
void Add(List*, void*);
void Remove(List*, void*, free_cb);
void RemoveAt(List*, int, free_cb);
void RemoveAll(List*, free_cb);
void Delete(List*);

#endif /* UTILS_H */
