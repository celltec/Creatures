#include "chipmunk/chipmunk.h"

#include <stdio.h>

#include "../src/free.h"
#include "../src/utils.h"
#include "../src/creature.h"
#include "../src/environment.h"
#include "test.h"

void TestList(int cases);
void TestRandom(int cases);

void Test(void)
{
	printf("Testing...\n");

	TestRandom(10000);

	TestList(1);
	TestList(100);

	printf("Successful!\n\n");
}

void TestList(int cases)
{
	Environment* environment = NewEnvironment();
	InitEnvironment(environment);
	List* testList = NewList();
	Creature* creature;

	for (int i = 0; i < cases; ++i)
	{
		Creature* creature = Spawn(randomVector(1000), randomRange(10.0, 100.0));
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


	Creature* newCreature1 = Spawn(randomVector(1000), randomRange(10.0, 100.0));
	Creature* newCreature2 = Spawn(randomVector(1000), randomRange(10.0, 100.0));
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

	DestroyEnvironment(environment);

	for (int i = 0; i < cases; ++i)
	{
		Environment* stress = NewEnvironment();
		InitEnvironment(stress);
		DestroyEnvironment(stress);
	}
}

void TestRandom(int cases)
{
	const float min = -1;
	const float max = 1;

	for (int i = 0; i < cases; ++i)
	{
		float res = randomRange(min, max);
		cpAssertHard(res >= min && res <= max, "failed test");
	}
}