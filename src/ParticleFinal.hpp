#pragma once

#ifndef KILO_PARTICLE_FINAL_HPP_INCLUDED
#define KILO_PARTICLE_FINAL_HPP_INCLUDED

#include <QTextStream>

namespace Kilo
{
    class ParticleFinal;
}

#include "AbstractParticle.hpp"
#include "Vector3.hpp"

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
