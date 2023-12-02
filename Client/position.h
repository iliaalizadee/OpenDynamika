#ifndef POSITION_H
#define POSITION_H

struct Position{
    float x;
    float y;
    float z;

    Position(){

    }

    Position(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Vec2D{
    float i;
    float j;
};

struct Vec3D{
    float i;
    float j;
    float k;
};

#endif // POSITION_H
