#include <vector>
#include <primitives.h>

class Object{
    private:
    std::vector<Triangle> surfaces;
    Point CoM;

    public:
    std::vector<Triangle> getSurfaces();


};