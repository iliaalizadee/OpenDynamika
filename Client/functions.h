#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<vector>
#include"primitives.h"
#include"camera.h"
#include<QString>


void transformAndNormalize(std::vector<Triangle> *triangles, Camera camera);
void copyToArray(std::vector<Triangle> triangles, float array[][3][3]);
void loadModel(std::vector<Triangle> *triangles, QString modelLocation);

#endif // FUNCTIONS_H
