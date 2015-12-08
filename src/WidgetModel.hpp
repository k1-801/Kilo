#pragma once

#ifndef WIDGET_MODEL_HPP_INCLUDED
#define WIDGET_MODEL_HPP_INCLUDED

namespace Kilo
{
    class WidgetModel;
}

#include "AbstractParticle.hpp"
#include "Vector3.hpp"
#include "Widget3D.hpp"

namespace Kilo
{
    class WidgetModel : public Widget3D
    {
        protected:
            Angle angle;
            void paintGL();

        public:
            WidgetModel(QWidget* = 0);
            ~WidgetModel();

        public slots:
            void changeAngle(Angle);
    };
}

#endif // WIDGET_MODEL_HPP_INCLUDED
