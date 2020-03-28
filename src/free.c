/* Copyright (c) 2013 Scott Lembcke and Howling Moon Software
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "chipmunk/chipmunk.h"

#include "free.h"

static void ShapeFreeWrap(cpSpace* space, cpShape* shape, void* unused)
{
	cpSpaceRemoveShape(space, shape);
	cpShapeFree(shape);
}

static void PostShapeFree(cpShape* shape, cpSpace* space)
{
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)ShapeFreeWrap, shape, NULL);
}

static void ConstraintFreeWrap(cpSpace* space, cpConstraint* constraint, void* unused)
{
	cpSpaceRemoveConstraint(space, constraint);
	cpConstraintFree(constraint);
}

static void PostConstraintFree(cpConstraint* constraint, cpSpace* space)
{
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)ConstraintFreeWrap, constraint, NULL);
}

static void BodyFreeWrap(cpSpace* space, cpBody* body, void* unused)
{
	cpSpaceRemoveBody(space, body);
	cpBodyFree(body);
}

static void PostBodyFree(cpBody* body, cpSpace* space)
{
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)BodyFreeWrap, body, NULL);
}

// Safe and future proof way to remove and free all objects that have been added to the space.
void FreeAllChildren(cpSpace* space)
{
	// Must remove these BEFORE freeing the body or you will access dangling pointers.
	cpSpaceEachShape(space, (cpSpaceShapeIteratorFunc)PostShapeFree, space);
	cpSpaceEachConstraint(space, (cpSpaceConstraintIteratorFunc)PostConstraintFree, space);
	cpSpaceEachBody(space, (cpSpaceBodyIteratorFunc)PostBodyFree, space);
}
