#pragma once

#ifndef KILO_PARTICLE_FINAL_HPP_INCLUDED
#define KILO_PARTICLE_FINAL_HPP_INCLUDED

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QTextStream>

namespace Kilo
{
    class ParticleFinal;
}

// Kilo
#include "AbstractParticle.hpp"

namespace Kilo
{
    class ParticleFinal : public AbstractParticle
    {
        Q_OBJECT

        public:
            ParticleFinal();
            virtual ~ParticleFinal() override;

            void getData(QTextStream&) const override;
            void setData(QTextStream&) override;

            void updateCoord() override;
            void updateForce() override;
            bool updateGroup() override;
    };
}

#endif // KILO_PARTICLE_FINAL_HPP_INCLUDED
