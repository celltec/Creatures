#ifndef DRAW_H
#define DRAW_H

#include "color.h"

void InitDraw(void);
void DrawDot(cpVect pos, cpFloat size, Color color);
void DrawCircle(cpVect pos, cpFloat radius, cpFloat angle, Color color);
void DrawLine(cpVect a, cpVect b, cpFloat width, Color color);
void DrawPolygon(cpShape* shape, Color color);

void TransformScreen(cpFloat scale, cpVect translate);
void FlushScreen(void);

#endif /* DRAW_H */
