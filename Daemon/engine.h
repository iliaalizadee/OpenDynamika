#ifndef ENGINE_H
#define ENGINE_H

#include "vector"
#include "object.h"

class Engine{
    private:
    float timeIncrement;

    public:
    void progressSimulation(std::vector<Object> objects);
    
};

#endif