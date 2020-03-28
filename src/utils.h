#ifndef UTILS_H
#define UTILS_H

#include "color.h"

Color randomColor(void);
cpFloat randomRange(cpFloat min, cpFloat max);
cpVect randomVector(int maxLenth);

// todo: maybe add lehmer random generator and carmack sqrt

#endif /* UTILS_H */
