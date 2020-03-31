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
