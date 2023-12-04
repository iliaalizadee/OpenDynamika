#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "primitives.h"
#include "surface.h"

class Object{
    private:
    std::vector<Surface> surfaces;
    Point CoM;
    Vec3D force;
    Vec3D speed;
    Vec3D angularSpeed;
    float mass;
    float momentOfInertia;

    public:
    std::vector<Surface> getSurfaces();


};

#endif