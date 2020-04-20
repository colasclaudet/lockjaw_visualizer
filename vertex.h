#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class Vertex
{
public:
    Vertex(GLfloat size, float x, float y, float z);
    void display(QOpenGLShaderProgram * buffer);
    void anime(float dt, float ymin, float ymax);
    void setColor(float r,float g, float b, float a);

    float x,y,z;

    float getX() const;

    float getY() const;

    float getZ() const;

private:

    QOpenGLBuffer vbo;
    QVector4D color = QVector4D(0.9f,1.0f,0.2f,0.5f);
    QVector3D position = QVector3D(0.0,0.0,0.0);
    QMatrix4x4 matrix;
    QVector<GLfloat> vertData;
    bool up = true;
};

#endif // VERTEX_H
