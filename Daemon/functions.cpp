#include "functions.h"
#include "vector_operations.h"

Point calculateCoM(Object object){
    std::vector<Point> normals;
    std::vector<float> weights;

    for (int n = 0; n < object.getSurfaces().size(); n++){

        normals.push_back(Position(
            (object.getSurfaces()[n].surfaceBoundary.vertices[0].pos.x + object.getSurfaces()[n].surfaceBoundary.vertices[1].pos.x + object.getSurfaces()[n].surfaceBoundary.vertices[2].pos.x)/3,
            (object.getSurfaces()[n].surfaceBoundary.vertices[0].pos.y + object.getSurfaces()[n].surfaceBoundary.vertices[1].pos.y + object.getSurfaces()[n].surfaceBoundary.vertices[2].pos.y)/3,
            (object.getSurfaces()[n].surfaceBoundary.vertices[0].pos.z + object.getSurfaces()[n].surfaceBoundary.vertices[1].pos.z + object.getSurfaces()[n].surfaceBoundary.vertices[2].pos.z)/3
        ));

        weights.push_back(
            vecLen(
                cross(
                    Vec3D(
                        object.getSurfaces()[n].surfaceBoundary.vertices[1].pos.x - object.getSurfaces()[n].surfaceBoundary.vertices[0].pos.x,
                        object.getSurfaces()[n].surfaceBoundary.vertices[1].pos.y - object.getSurfaces()[n].surfaceBoundary.vertices[0].pos.y,
                        object.getSurfaces()[n].surfaceBoundary.vertices[1].pos.z - object.getSurfaces()[n].surfaceBoundary.vertices[0].pos.z

                    ),
                    Vec3D(
                        object.getSurfaces()[n].surfaceBoundary.vertices[2].pos.x - object.getSurfaces()[n].surfaceBoundary.vertices[0].pos.x,
                        object.getSurfaces()[n].surfaceBoundary.vertices[2].pos.y - object.getSurfaces()[n].surfaceBoundary.vertices[0].pos.y,
                        object.getSurfaces()[n].surfaceBoundary.vertices[2].pos.z - object.getSurfaces()[n].surfaceBoundary.vertices[0].pos.z
                    ))));

        float xWeightedSum(0);
        float yWeightedSum(0);
        float zWeightedSum(0);
        float weigthSum(0);

        for (int n = 0; n < object.getSurfaces().size(); n++){
            xWeightedSum += normals[n].pos.x * weights[n];
            yWeightedSum += normals[n].pos.y * weights[n];
            zWeightedSum += normals[n].pos.z * weights[n];
            weigthSum += weights[n];
        }

        return Point(Position(xWeightedSum/weigthSum, yWeightedSum/weigthSum, zWeightedSum/weigthSum));
    }
}
