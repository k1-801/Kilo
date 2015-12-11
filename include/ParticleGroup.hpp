#pragma once

#ifndef KILO_PARTICLE_GROUP_HPP_INCLUDED
#define KILO_PARTICLE_GROUP_HPP_INCLUDED

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
#include <QObject>

namespace Kilo
{
    class ParticleGroup;
}

// Kilo
#include "AbstractParticle.hpp"
#include "ParticleField.hpp"

namespace Kilo
{
    class ParticleGroup : public AbstractParticle
    {
        Q_OBJECT

        private:
            QColor  _color;
            long double _mass;
            long double _radius;
            long double _charge;

        public:
            Q_INVOKABLE ParticleGroup();
            virtual    ~ParticleGroup() override;

            void add(AbstractParticle*);

            long double getCharge() const override;
            QColor      getColor () const override;
            long double getMass  () const override;
            long double getRadius() const override;

            void updateCoord() override;
            void updateForce() override;
            bool updateGroup() override;
            void  smartClean() override;
    };
}

#endif // KILO_PARTICLE_GROUP_HPP_INCLUDED
