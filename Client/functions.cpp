#include"functions.h"
#include "vector_operations.h"
#include <QFile>
#include <QTextStream>


void transformAndNormalize(std::vector<Triangle> *triangles, Camera camera){

    Vec3D vertexPositionRelativeToCamera;

    float wz = (camera.getFarPlane() - camera.getNearPlane())/2;
    float wxy = camera.getPlaneWidth()/2;

    for (int n = 0; n < (*triangles).size(); n++){
        for(int j = 0; j < 3; j++){

            vertexPositionRelativeToCamera.i = (*triangles)[n].vertices[j].pos.x - camera.getCameraPosition().x;
            vertexPositionRelativeToCamera.j = (*triangles)[n].vertices[j].pos.y - camera.getCameraPosition().y;
            vertexPositionRelativeToCamera.k = (*triangles)[n].vertices[j].pos.z - camera.getCameraPosition().z;

            (*triangles)[n].vertices[j].pos.x = dot(vertexPositionRelativeToCamera, camera.getCameraRightVector())/wxy;
            (*triangles)[n].vertices[j].pos.y = dot(vertexPositionRelativeToCamera, camera.getCameraUpVector())/wxy;

            (*triangles)[n].vertices[j].pos.z = 1 - (dot(vertexPositionRelativeToCamera, cross(camera.getCameraUpVector(), camera.getCameraRightVector())) - camera.getNearPlane())/wz;

        }
    }
}


void copyToArray(std::vector<Triangle> triangles, float array[][3][3]){
    for (int n = 0; n < triangles.size(); n++){
        for (int j = 0; j < 3; j++){
            array[n][j][0] = triangles[n].vertices[j].pos.x;
            array[n][j][1] = triangles[n].vertices[j].pos.y;
            array[n][j][2] = triangles[n].vertices[j].pos.z;
        }
    }
}


void loadModel(std::vector<Triangle> *triangles, QString modelLocation){
    QFile objFile(modelLocation);
    std::vector<Point> verticeData;

    if(objFile.open(QIODevice::ReadOnly | QIODevice::Text)){

        QTextStream stream(&objFile);
        QString text;
        QStringList list;

        while(!stream.atEnd()){
            text = stream.readLine();
            list = text.split(" ");

            if (list[0] == "v"){
                verticeData.push_back(
                    Point(
                        Position(
                            list[1].toFloat(),
                            list[2].toFloat(),
                            list[3].toFloat())));

            }else if (list.at(0) == "f"){

                float v1Index = list[1].split("/")[0].toFloat();
                float v2Index = list[2].split("/")[0].toFloat();
                float v3Index = list[3].split("/")[0].toFloat();

                (*triangles).push_back(
                    Triangle({
                        verticeData[v1Index - 1],
                        verticeData[v2Index - 1],
                        verticeData[v3Index - 1]
                    }));
            }
        }
    }
}
