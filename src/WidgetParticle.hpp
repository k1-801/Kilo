#pragma once

#ifndef KILO_WIDGET_PARTICLE_HPP
#define KILO_WIDGET_PARTICLE_HPP

#include <QTableWidget>

namespace Kilo
{
    class WidgetParticle;
}

#include "AbstractParticle.hpp"

namespace Kilo
{
    class WidgetParticle : public QTableWidget
    {
        Q_OBJECT

        protected:
            AbstractParticle* _p;

            void _update();

        public:
            WidgetParticle(QWidget* = 0);
            void setParticle(AbstractParticle*);
    };
}

#endif // KILO_WIDGET_PARTICLE_HPP
