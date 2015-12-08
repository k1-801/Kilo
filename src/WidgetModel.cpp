#include "../include/WidgetModel.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// HCL
#include <HCL/Vector3.hpp>
// Kilo
#include "../include/Core.hpp"
#include "../include/Runner.hpp"

// OpenGL
#include <GL/glu.h>

namespace Kilo
{
    WidgetModel::WidgetModel(QWidget* parent) : Widget3D(parent){}
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

        QMutex& m = Core::getInstance().mutexParticles;
        m.lock();
        Universe::getInstance().draw();
        m.unlock();
    }

    void WidgetModel::changeAngle(Hcl::Rotation r)
    {
        _rotation = r;
        paintGL();
    }
}
