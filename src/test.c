#include "chipmunk/chipmunk.h"

#include "free.h"
#include "utils.h"
#include "creature.h"
#include "environment.h"
#include "test.h"

void TestList(int cases);
void TestRandom(int cases);

void Test(void)
{
#ifdef DEBUG
	printf("Testing...\n");
#endif

	TestRandom(100000);

	TestList(1);
	TestList(10000);

#ifdef DEBUG
	printf("Successful!\n\n");
#endif
}

void TestList(int cases)
{
	Environment* environment = NewEnvironment();
	CreatureList* testList = NewList();

	for (int i = 0; i < cases; ++i)
	{
		Creature* creature = Spawn();
		cpSpaceAddBody(environment->space, cpShapeGetBody(creature->shape));
		cpSpaceAddShape(environment->space, creature->shape);
		Add(testList, creature);
	}

	cpAssertHard(testList->count == cases, "failed test");

	for (int i = 0; i < testList->count; ++i)
	{
		cpAssertHard(testList->list[i]->health == 100.0, "failed test");
	}

	int someIndex = (int)((float)cases / 2.0);
	Creature* testCreature = testList->list[someIndex];

	Remove(testList, testList->list[someIndex], NULL);
	cpAssertHard(testList->count == cases - 1, "failed test");
	if (testList->list)
		cpAssertHard(testList->list[someIndex] != testCreature, "failed test");
	cpAssertHard(testCreature->health == 100.0, "failed test");

	Add(testList, testCreature);
	cpAssertHard(testList->list[testList->count - 1]->health == 100.0, "failed test");

	Remove(testList, testList->list[testList->count - 1], Kill);
	cpAssertHard(testCreature->health != 100.0, "failed test");

	RemoveAll(testList, NULL);
	cpAssertHard(testList->count == 0, "failed test");

	FreeList(testList);
	FreeAllChildren(environment->space);
	cpSpaceFree(environment->space);
	cpfree(environment);
}

void TestRandom(int cases)
{
	const cpFloat min = -1;
	const cpFloat max = 1;

	for (int i = 0; i < cases; ++i)
	{
		cpFloat res = randomRange(min, max);
		cpAssertHard(res >= min && res <= max, "failed test");
	}
}