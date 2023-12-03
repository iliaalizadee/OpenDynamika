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

Vec3D operator+(Point const& p1, Point const& p2){
    return Vec3D(p1.pos.x + p2.pos.x, p1.pos.y + p2.pos.y, p1.pos.z + p2.pos.z);
}

Vec3D operator-(Point const& p1, Point const& p2){
    return Vec3D(p1.pos.x - p2.pos.x, p1.pos.y - p2.pos.y, p1.pos.z - p2.pos.z);
}



#endif