#ifndef COLOR_H
#define COLOR_H

#include "utils.h"

typedef struct {
	float r, g, b, a;
} Color;

static const Color black = { 0.0, 0.0, 0.0, 1.0 };
static const Color white = { 1.0, 1.0, 1.0, 1.0 };
static const Color red = { 1.0, 0.0, 0.0, 1.0 };
static const Color green = { 0.0, 1.0, 0.0, 1.0 };
static const Color blue = { 0.0, 0.0, 1.0, 1.0 };

static Color randomColor(void)
{
	/* Exclude boundary values to prevent pure blacks and whites */
	return (Color) {
		randomRange(0.2, 0.8),
		randomRange(0.2, 0.8),
		randomRange(0.2, 0.8),
		1.0
	};
}

#endif /* COLOR_H */
