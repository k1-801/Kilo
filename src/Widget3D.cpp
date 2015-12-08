#include "../include/Widget3D.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// OpenGL
#include <GL/glu.h>

namespace Kilo
{
    Widget3D::Widget3D(QWidget* parent) : QOpenGLWidget(parent)
    {
        connect(&redrawTimer, &QTimer::timeout, this, &Widget3D::redraw);
        redrawTimer.setInterval(25);
        redrawTimer.start();
    }
    Widget3D::~Widget3D()
    {
        redrawTimer.stop();
    }

    void Widget3D::reperspective()
    {
        glViewport(0, 0, _w, _h);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluPerspective(45, (long double)(_w) / _h, 0.01, 10000000);

        // Transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_TRUE);
    }

    void Widget3D::initializeGL()
    {
        _w = width();
        _h = height();
    }

    void Widget3D::resizeGL(int w, int h)
    {
        _w = w;
        _h = h;
    }

    void Widget3D::redraw()
    {
        update();
    }
}
