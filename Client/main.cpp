#include "mainwindow.h"

#include <QApplication>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_5_Core>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <cmath>
#include <vector>
#include <QFileDialog>
#include "camera.h"
#include "primitives.h"
#include "functions.h"


#define PI 3.1415926535
#define rad(x) x*PI/180

Camera camera;

std::vector<Triangle> triangles;
std::vector<Triangle> viewMapping;

unsigned int vaobuf[1];
unsigned int vbobuf[1];

QOpenGLFunctions_4_5_Core *functions;



const char *fragmentShaderSource;
const char *vertexShaderSource;
std::string vertexShaderSourceBuffer;
std::string fragmentShaderSourceBuffer;




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QFile fragmentShaderSourceFile("/home/ilia/Documents/Simul/Simul/fsh.glsl");
    QFile vertexShaderSourceFile("/home/ilia/Documents/Simul/Simul/vsh.glsl");


    if(fragmentShaderSourceFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&fragmentShaderSourceFile);
        fragmentShaderSourceBuffer = stream.readAll().toStdString();
    }
    fragmentShaderSourceFile.close();
    fragmentShaderSource = fragmentShaderSourceBuffer.c_str();



    if(vertexShaderSourceFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&vertexShaderSourceFile);
        vertexShaderSourceBuffer = stream.readAll().toStdString();
    }
    vertexShaderSourceFile.close();
    vertexShaderSource = vertexShaderSourceBuffer.c_str();



    loadModel(&triangles, "/home/ilia/Documents/untitled.obj");



    camera.transformCamera(1, -1, 4);
    camera.rotateCamera(rad(15), rad(15), 0);

    camera.setAspectRatio(1);
    camera.setPlaneWidth(10);
    camera.setNearPlane(1);
    camera.setFarPlane(20);



    functions =  QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();


    unsigned int program = functions->glCreateProgram();


    unsigned int vsh = functions->glCreateShader(GL_VERTEX_SHADER);
    functions->glShaderSource(vsh, 1, &vertexShaderSource, NULL);
    functions->glCompileShader(vsh);

    unsigned int fsh = functions->glCreateShader(GL_FRAGMENT_SHADER);
    functions->glShaderSource(fsh, 1, &fragmentShaderSource, NULL);
    functions->glCompileShader(fsh);

    functions->glAttachShader(program, vsh);
    functions->glAttachShader(program, fsh);

    functions->glLinkProgram(program);
    functions->glUseProgram(program);

    functions->glDeleteShader(vsh);
    functions->glDeleteShader(fsh);


    functions->glGenVertexArrays(1, vaobuf);
    functions->glBindVertexArray(vaobuf[0]);

    functions->glGenBuffers(1, vbobuf);
    functions->glBindBuffer(GL_ARRAY_BUFFER, vbobuf[0]);


    float array[triangles.size()][3][3];
    copyToArray(triangles, array);


    functions->glBufferData(GL_ARRAY_BUFFER, sizeof(array), array, GL_STATIC_DRAW);

    int wxyUniformLocation = functions->glGetUniformLocation(program, "wxy");
    int wzUniformLocation = functions->glGetUniformLocation(program, "wz");
    int cameraPositionUniformLocation = functions->glGetUniformLocation(program, "cameraPosition");
    int cameraUpVectorUniformLocation = functions->glGetUniformLocation(program, "cameraUpVector");
    int cameraRightVectorUniformLocation = functions->glGetUniformLocation(program, "cameraRightVector");
    int positionAttributeLocation = functions->glGetAttribLocation(program, "position");

    functions->glUniform1f(wxyUniformLocation, camera.getPlaneWidth()/2);
    functions->glUniform1f(wzUniformLocation, (camera.getFarPlane() - camera.getNearPlane())/2);
    functions->glUniform3f(cameraPositionUniformLocation, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
    functions->glUniform3f(cameraUpVectorUniformLocation, camera.getCameraUpVector().i, camera.getCameraUpVector().j, camera.getCameraUpVector().k);
    functions->glUniform3f(cameraRightVectorUniformLocation, camera.getCameraRightVector().i, camera.getCameraRightVector().j, camera.getCameraRightVector().k);

    functions->glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    functions->glEnableVertexAttribArray(positionAttributeLocation);

    functions->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    functions->glDrawArrays(GL_TRIANGLES, 0, (int)sizeof(array)/sizeof(GL_FLOAT));

    return a.exec();
}



