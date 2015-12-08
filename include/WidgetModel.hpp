#pragma once

#ifndef WIDGET_MODEL_HPP_INCLUDED
#define WIDGET_MODEL_HPP_INCLUDED

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

namespace Kilo
{
    class WidgetModel;
}

// Kilo
#include "AbstractParticle.hpp"
#include "Widget3D.hpp"

namespace Kilo
{
    class WidgetModel : public Widget3D
    {
        protected:
            Hcl::Rotation _rotation; // Rotation angle
            Hcl::Coord _offset;
            void paintGL();

        public:
            WidgetModel(QWidget* = 0);
            ~WidgetModel();
            void drawSphere   (QColor, Hcl::Coord    );
            void drawPoint    (QColor, Hcl::Coord    );
            void drawTraectory(QColor, Hcl::Traectory);

        public slots:
            void changeAngle(Hcl::Rotation);
    };
}

#endif // WIDGET_MODEL_HPP_INCLUDED
