#include "../include/WidgetAxis.hpp"

namespace Kilo
{
    WidgetAxis::WidgetAxis(QWidget* parent) : Widget3D(parent){}
    WidgetAxis::~WidgetAxis(){}

    void WidgetAxis::paintGL()
    {
        reperspective();
        glTranslated(0, 0, -3);
        glRotated(rotation.getX(), 1, 0, 0);
        glRotated(rotation.getY(), 0, 1, 0);
        glRotated(rotation.getZ(), 0, 0, 1);

        glBegin(GL_LINES);
            glColor3f (1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(1, 0, 0);

            glColor3f (0, 1, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 1, 0);

            glColor3f (0, 0, 1);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, 1);
        glEnd();
    }

    void WidgetAxis::changeAngle(Hcl::Rotation r)
    {
        rotation = r;
        paintGL();
    }
}
