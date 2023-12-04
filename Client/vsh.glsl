#version 450 core
uniform float wz;
uniform float wxy;
uniform vec3 cameraPosition;
uniform vec3 cameraUpVector;
uniform vec3 cameraRightVector;
in vec3 position;

void main(){
    vec3 vertexPositionRelativeToCamera = position - cameraPosition;
    gl_Position = vec4(
                       dot(vertexPositionRelativeToCamera, cameraRightVector)/wxy,
                       dot(vertexPositionRelativeToCamera, cameraUpVector)/wxy,
                       dot(vertexPositionRelativeToCamera, cross(cameraUpVector, cameraRightVector))/wz,
                       1.0);
}
