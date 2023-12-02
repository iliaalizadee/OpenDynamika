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



const char *fragmentShaderSource = "#version 450 core\n"
                                   "out vec4 color;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   color = vec4(1.0, 1.0, 1.0, 1.0);\n"
                                   "}\0";


const char *vertexShaderSource = "#version 450 core\n"
                                 "in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";




int main(int argc, char *argv[])
{


    loadModel(&triangles, "/home/ilia/Documents/untitled.obj");


    camera.transformCamera(0, 0, 4);
    camera.rotateCamera(rad(15), rad(15), 0);

    camera.setAspectRatio(1);
    camera.setPlaneWidth(10);
    camera.setNearPlane(1);
    camera.setFarPlane(20);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    functions =  QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();



    transformAndNormalize(&triangles, camera);

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

    int posattr = functions->glGetAttribLocation(program, "aPos");
    functions->glVertexAttribPointer(posattr, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    functions->glEnableVertexAttribArray(posattr);

    functions->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    functions->glDrawArrays(GL_TRIANGLES, 0, (int)sizeof(array)/sizeof(GL_FLOAT));
    return a.exec();
}



