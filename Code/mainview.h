#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "mainwindow.h"
#include "shapes/shape.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <QSlider>
#include <memory>

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    QOpenGLDebugLogger *debugLogger;
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram shaderProgram;

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    void referenceUI(Ui::MainWindow* ref);

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int newScale);
    void setShadingMode(ShadingMode shading);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    QVector<Shape> shapes;

    QMatrix4x4 rotation;
    QMatrix4x4 scaling;
    QMatrix4x4 projection;

    GLuint transformMatrix;
    GLuint projectionMatrix;
    GLuint rotateMatrix;
    GLuint scalingMatrix;

    int nearPlane = 0;
    int farPlane = 10;
    int scale = 100;
    QSlider* scaleSlider;

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged( QOpenGLDebugMessage Message );

private:
    void createShaderProgram();

};

#endif // MAINVIEW_H
