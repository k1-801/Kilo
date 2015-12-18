#pragma once

#ifndef KILO_WIDGET_PARTICLE_HPP
#define KILO_WIDGET_PARTICLE_HPP

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QTableWidget>

namespace Kilo
{
    class WidgetParticle;
}

// Kilo
#include "AbstractParticle.hpp"

namespace Kilo
{
    class WidgetParticle : public QTableWidget
    {
        Q_OBJECT

        protected:
            ParticleWP _p;

        public:
            WidgetParticle(QWidget* = 0);
            void setParticle(ParticleWP);
            void update();
            void change(int);
    };
}

#endif // KILO_WIDGET_PARTICLE_HPP
