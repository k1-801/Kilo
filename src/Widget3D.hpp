#pragma once

#ifndef KILO_WIDGET3D_HPP
#define KILO_WIDGET3D_HPP

// Qt
#include <QOpenGLWidget>
#include <QTimer>

namespace Kilo
{
    class Widget3D;
}

// Kilo
#include "Vector3.hpp"

namespace Kilo
{
    class Widget3D : public QOpenGLWidget
    {
        private:
            int _w;
            int _h;
            QTimer redrawTimer;

        protected:
            void reperspective();
            void initializeGL();
            void resizeGL(int, int);\

        public:
            Widget3D(QWidget* = 0);
            virtual ~Widget3D();

        public slots:
            void redraw();
    };
}

#endif // KILO_WIDGET3D_HPP
