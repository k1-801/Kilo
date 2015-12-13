#include "../include/WidgetModel.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// HCL
#include <HCL/Locker2.hpp>
#include <HCL/Vector3.hpp>
// Kilo
#include "../include/Core.hpp"
#include "../include/Runner.hpp"

// OpenGL
#include <GL/glu.h>

namespace Kilo
{
    WidgetModel::WidgetModel(QWidget* parent) : Widget3D(parent)
    {
        _zoom = 1;
    }
    WidgetModel::~WidgetModel(){}

    void WidgetModel::paintGL()
    {
        // Perspective and so on
        reperspective();
        glTranslated(0, 0, -3);
        glRotated(_rotation.getX(), 1, 0, 0);
        glRotated(_rotation.getY(), 0, 1, 0);
        glRotated(_rotation.getZ(), 0, 0, 1);

        // Axis
        glBegin(GL_LINES);
        {
            glColor3f (1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(1, 0, 0);

            glColor3f (0, 1, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 1, 0);

            glColor3f (0, 0, 1);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, 1);

            if(Runner::getInstance().isSimRunning())
            {
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0, -1);
            }
        }
        glEnd();

        //Hcl::Locker1 _(Core::getInstance().mutexParticles);
        Universe::getInstance().draw();
    }

    void WidgetModel::changeAngle(Hcl::Rotation r)
    {
        _rotation = r;
        paintGL();
    }

    void WidgetModel::drawSphere(QColor color, Hcl::Coord coord, long double radius)
    {
        long double alpha = 1.5 - radius * _zoom;
        if(alpha < 0)
            alpha = 0;
        if(alpha > 1)
            alpha = 1;

        glPushMatrix();
        glTranslated(coord.getX() * _zoom, coord.getY() * _zoom, coord.getZ() * _zoom);
        glColor4f(color.red(), color.green(), color.blue(), alpha);
        GLUquadric* quad = gluNewQuadric();
        gluQuadricDrawStyle(quad, GLU_FILL);
        gluSphere(quad, radius * _zoom, 32, 32);
        gluDeleteQuadric(quad);
        glPopMatrix();
    }

    void WidgetModel::changeZoom(long double z)
    {
        _zoom = z;
    }
}
