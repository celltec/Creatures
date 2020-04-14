#ifndef COLOR_H
#define COLOR_H

#include "utils.h"

typedef struct {
	float r, g, b, a;
} Color;

static const Color black = { 0.0f, 0.0f, 0.0f, 1.0f };
static const Color white = { 1.0f, 1.0f, 1.0f, 1.0f };
static const Color red = { 1.0f, 0.0f, 0.0f, 1.0f };
static const Color green = { 0.0f, 1.0f, 0.0f, 1.0f };
static const Color blue = { 0.0f, 0.0f, 1.0f, 1.0f };

static Color randomColor(void)
{
	/* Exclude boundary values to prevent pure blacks and whites */
	return (Color) {
		randomRange(0.2f, 0.8f),
		randomRange(0.2f, 0.8f),
		randomRange(0.2f, 0.8f),
		1.0f
	};
}

#endif /* COLOR_H */
