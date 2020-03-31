#ifndef UTILS_H
#define UTILS_H

#include "color.h"

uint32_t rand32(uint32_t seed);
Color randomColor(void);
cpFloat randomRange(cpFloat min, cpFloat max);
cpVect randomVector(int maxLenth);

#endif /* UTILS_H */
