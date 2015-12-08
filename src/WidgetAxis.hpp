#pragma once

#ifndef WIDGET_AXIS_HPP_INCLUDED
#define WIDGET_AXIS_HPP_INCLUDED

namespace Kilo
{
    class WidgetAxis;
}

#include "Vector3.hpp"
#include "Widget3D.hpp"

namespace Kilo
{
    class WidgetAxis : public Widget3D
    {
        protected:
            Angle angle;
            void paintGL();

        public:
            WidgetAxis(QWidget* = 0);
            ~WidgetAxis();

        public slots:
            void changeAngle(Angle);
    };
}

#endif // WIDGET_AXIS_HPP_INCLUDED
