#pragma once

#ifndef DOT_HPP_INCLUDED
#define DOT_HPP_INCLUDED

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QColor>
#include <QTextStream>
#include <QVector>

namespace Kilo
{
    class Dot;
}

#include "../ParticleField.hpp"
#include "../ParticleFinal.hpp"

namespace Kilo
{
    class Dot : public ParticleFinal
    {
        Q_OBJECT

        private:
            QColor _color;
            long double _charge;
            long double _mass;
            long double _radius;

        public:
            Q_INVOKABLE Dot();
            ~Dot();

            QColor      getColor () const override;
            long double getCharge() const override;
            long double getMass  () const override;
            long double getRadius() const override;
    };
}

#endif // DOT_HPP_INCLUDED
