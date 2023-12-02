#include"vector_operations.h"
#include <cmath>

Vec3D cross(Vec3D vec1, Vec3D vec2){
    Vec3D result;
    result.i = vec1.j*vec2.k - vec1.k*vec2.j;
    result.j = vec1.k*vec2.i - vec1.i*vec2.k;
    result.k = vec1.i*vec2.j - vec1.j*vec2.i;
    return result;
}

float dot(Vec3D vec1, Vec3D vec2){
    return vec1.i*vec2.i + vec1.j*vec2.j + vec1.k*vec2.k;
}

float vecLen(Vec3D vec){
    return sqrt(pow(vec.i, 2) + pow(vec.j, 2) + pow(vec.k, 2));
}


