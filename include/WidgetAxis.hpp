#pragma once

#ifndef WIDGET_AXIS_HPP_INCLUDED
#define WIDGET_AXIS_HPP_INCLUDED

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// HCL
#include <HCL/Vector3.hpp>

namespace Kilo
{
    class WidgetAxis;
}

// Kilo
#include "Widget3D.hpp"

namespace Kilo
{
    class WidgetAxis : public Widget3D
    {
        protected:
            Hcl::Rotation rotation;
            void paintGL();

        public:
            WidgetAxis(QWidget* = 0);
            ~WidgetAxis();

        public slots:
            void changeAngle(Hcl::Rotation);
    };
}

#endif // WIDGET_AXIS_HPP_INCLUDED
