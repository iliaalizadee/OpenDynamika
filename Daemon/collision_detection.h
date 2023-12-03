#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "primitives.h"
#include "surface.h"
#include "object.h"

bool lineIntersectsWithSurface(Line line, Surface surface);
bool surfacesIntersect(Surface s1, Surface s2);
bool surfaceIntersectsWithObject(Surface surface, Object object);
bool objectsIntersect(Object obj1, Object ob2);

#endif