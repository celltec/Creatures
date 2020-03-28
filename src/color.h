#ifndef COLOR_H
#define COLOR_H

typedef struct {
	float r, g, b, a;
} Color;

static const Color black = { 0.0, 0.0, 0.0, 1.0 };
static const Color white = { 1.0, 1.0, 1.0, 1.0 };
static const Color red = { 1.0, 0.0, 0.0, 1.0 };
static const Color green = { 0.0, 1.0, 0.0, 1.0 };
static const Color blue = { 0.0, 0.0, 1.0, 1.0 };

#endif /* COLOR_H */
