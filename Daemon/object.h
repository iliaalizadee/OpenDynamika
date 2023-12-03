#include <vector>
#include <primitives.h>

class Object{
    private:
    std::vector<Surface> surfaces;
    Point CoM;
    Vec3D speed;
    Vec3D angularSpeed;
    float mass;
    float momentOfInertia;

    public:
    std::vector<Surface> getSurfaces();


};