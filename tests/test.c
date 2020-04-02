#include "chipmunk/chipmunk.h"

#ifdef DEBUG
#include <stdio.h>
#endif

#include "../src/free.h"
#include "../src/utils.h"
#include "../src/creature.h"
#include "../src/environment.h"
#include "test.h"

void TestList(int cases);
void TestRandom(int cases);

void Test(void)
{
#ifdef DEBUG
	printf("Testing...\n");
#endif

	TestRandom(10000);

	TestList(1);
	TestList(100);

#ifdef DEBUG
	printf("Successful!\n\n");
#endif
}

void TestList(int cases)
{
	Environment* environment = NewEnvironment();
	List* testList = New();
	Creature* creature;

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
		Creature* creature = testList->list[i];
		cpAssertHard(creature->health == 100.0, "failed test");
	}

	int someIndex = (int)((float)cases / 2.0);
	Creature* testCreature = testList->list[someIndex];

	Remove(testList, testList->list[someIndex], NULL);
	cpAssertHard(testList->count == cases - 1, "failed test");
	if (testList->list)
		cpAssertHard(testList->list[someIndex] != testCreature, "failed test");
	cpAssertHard(testCreature->health == 100.0, "failed test");

	Add(testList, testCreature);
	creature = testList->list[testList->count - 1];
	cpAssertHard(creature->health == 100.0, "failed test");

	Remove(testList, testList->list[testList->count - 1], Kill);
	cpAssertHard(testCreature->health != 100.0, "failed test");

	RemoveAll(testList, NULL);
	cpAssertHard(testList->count == 0, "failed test");


	Creature* newCreature1 = Spawn();
	Creature* newCreature2 = Spawn();
	cpSpaceAddBody(environment->space, cpShapeGetBody(newCreature2->shape));
	cpSpaceAddShape(environment->space, newCreature2->shape);

	Add(testList, newCreature1);
	creature = testList->list[0];
	cpAssertHard(creature->health == 100.0, "failed test");
	Add(testList, newCreature2);
	creature = testList->list[1];
	cpAssertHard(creature->health == 100.0, "failed test");

	RemoveAt(testList, 1, Kill);
	cpAssertHard(testList->count == 1, "failed test");
	cpAssertHard(testList->list != NULL, "failed test");
	cpAssertHard(newCreature2->health != 100.0, "failed test");
	RemoveAt(testList, 0, NULL);
	cpAssertHard(testList->count == 0, "failed test");
	cpAssertHard(testList->list == NULL, "failed test");
	cpAssertHard(newCreature1->health == 100.0, "failed test");


	Delete(testList);
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