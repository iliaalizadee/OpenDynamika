#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "position.h"
#include <vector>


struct Point{
    Position pos;

    Point(){

    }

    Point(Position pos){
        this->pos = pos;
    }
};

struct Line{
    Point start;
    Point end;
};

struct Triangle{
    std::vector<Point> vertices;

    Triangle(){
    }

    Triangle(std::vector<Point> vertices){
        this->vertices = vertices;
    }
};

#endif // PRIMITIVES_H
