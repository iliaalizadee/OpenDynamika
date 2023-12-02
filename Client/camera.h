#ifndef CAMERA_H
#define CAMERA_H
#define PI 3.1415926535

#include"position.h"

class Camera{
private:
    Position cameraPosition;
    Vec3D cameraUpVector;
    Vec3D cameraRightVector;
    float nearPlane;
    float farPlane;
    float planeWidth;
    float aspectRatio;
public:
    Camera();
    Camera(Position position);
    Camera(Vec3D upVector, Vec3D rightVector);
    Camera(Position position, Vec3D upVector, Vec3D rightVector);

    void transformCamera(float xTransform, float yTransform, float zTransform);
    void rotateCamera(float radX, float radY, float radZ);

    Position getCameraPosition();
    void setCameraPosition(Position cameraPosition);

    Vec3D getCameraUpVector();
    void setCameraUpVector(Vec3D cameraUpVector);

    Vec3D getCameraRightVector();
    void setCameraRightVector(Vec3D cameraRightVector);

    float getNearPlane();
    void setNearPlane(float nearPlane);

    float getFarPlane();
    void setFarPlane(float farPlane);

    float getPlaneWidth();
    void setPlaneWidth(float planeWidth);

    float getAspectRatio();
    void setAspectRatio(float aspectRatio);





};

#endif // CAMERA_H
