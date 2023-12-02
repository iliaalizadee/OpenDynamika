#include "camera.h"
#include <cmath>


Camera::Camera(){
    this->cameraPosition.x = 0;
    this->cameraPosition.y = 0;
    this->cameraPosition.z = 0;
    this->cameraRightVector.i = 1;
    this->cameraRightVector.j = 0;
    this->cameraRightVector.k = 0;
    this->cameraUpVector.i = 0;
    this->cameraUpVector.j = 1;
    this->cameraUpVector.k = 0;
}

Camera::Camera(Position position, Vec3D upVector, Vec3D rightVector){
    this->cameraPosition = position;
    this->cameraUpVector = upVector;
    this->cameraRightVector = rightVector;
}






void Camera::transformCamera(float xTransform, float yTransform, float zTransform){

        Camera::cameraPosition.x += xTransform;
        Camera::cameraPosition.y += yTransform;
        Camera::cameraPosition.z += zTransform;
}


void Camera::rotateCamera(float radX, float radY, float radZ){
        Vec3D tempCameraRightVector = cameraRightVector;
        Vec3D tempCameraUpVector = cameraUpVector;


        this->cameraRightVector.i = cos(radZ)*tempCameraRightVector.i - sin(radZ)*tempCameraRightVector.j;
        this->cameraRightVector.i = cos(radY)*cameraRightVector.i + sin(radY)*tempCameraRightVector.k;
        this->cameraRightVector.j = cos(radZ)*tempCameraRightVector.j + sin(radZ)*tempCameraRightVector.i;
        this->cameraRightVector.j = cos(radX)*cameraRightVector.j - sin(radX)*tempCameraRightVector.k;
        this->cameraRightVector.k = cos(radX)*tempCameraRightVector.k + sin(radX)*tempCameraRightVector.j;
        this->cameraRightVector.k = cos(radY)*cameraRightVector.k - sin(radY)*tempCameraRightVector.i;

        this->cameraUpVector.i = cos(radZ)*tempCameraUpVector.i - sin(radZ)*tempCameraUpVector.j;
        this->cameraUpVector.i = cos(radY)*cameraUpVector.i + sin(radY)*tempCameraUpVector.k;
        this->cameraUpVector.j = cos(radZ)*tempCameraUpVector.j + sin(radZ)*tempCameraUpVector.i;
        this->cameraUpVector.j = cos(radX)*cameraUpVector.j - sin(radX)*tempCameraUpVector.k;
        this->cameraUpVector.k = cos(radX)*tempCameraUpVector.k + sin(radX)*tempCameraUpVector.j;
        this->cameraUpVector.k = cos(radY)*cameraUpVector.k - sin(radY)*tempCameraUpVector.i;


}




Position Camera::getCameraPosition(){
        return this->cameraPosition;
}
void Camera::setCameraPosition(Position cameraPosition){
        this->cameraPosition = cameraPosition;
}

Vec3D Camera::getCameraUpVector(){
        return this->cameraUpVector;
}
void Camera::setCameraUpVector(Vec3D cameraUpVector){
        this->cameraUpVector = cameraUpVector;
}

Vec3D Camera::getCameraRightVector(){
        return this->cameraRightVector;
}
void Camera::setCameraRightVector(Vec3D cameraRightVector){
        this->cameraRightVector = cameraRightVector;
}

float Camera::getNearPlane(){
        return this->nearPlane;
}
void Camera::setNearPlane(float nearPlane){
        this->nearPlane = nearPlane;
}

float Camera::getFarPlane(){
        return this->farPlane;
}
void Camera::setFarPlane(float farPlane){
        this->farPlane = farPlane;
}

float Camera::getPlaneWidth(){
        return this->planeWidth;
}
void Camera::setPlaneWidth(float planeWidth){
        this->planeWidth = planeWidth;
}

float Camera::getAspectRatio(){
        return this->aspectRatio;
}
void Camera::setAspectRatio(float aspectRatio){
        this->aspectRatio = aspectRatio;
}
