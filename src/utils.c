#include "chipmunk/chipmunk.h"

#include "utils.h"

Color randomColor(void)
{
	return (Color) { randomRange(0.0, 1.0), randomRange(0.0, 1.0), randomRange(0.0, 1.0), 1.0 };
}

cpFloat randomRange(cpFloat min, cpFloat max)
{
	return min + rand() / (RAND_MAX / (max - min) + 1);
}

cpVect randomVector(int maxLenth)
{
	cpFloat angle = CP_PI * 2.0 * randomRange(0.0, 1.0);
	return cpvmult(cpvforangle(angle), rand() % maxLenth);
}
