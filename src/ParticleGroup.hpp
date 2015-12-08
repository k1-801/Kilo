#pragma once

#ifndef KILO_PARTICLE_GROUP_HPP_INCLUDED
#define KILO_PARTICLE_GROUP_HPP_INCLUDED

// C++
#include <list>
// Qt
#include <QTextStream>
#include <QObject>
#include <QtXml>

namespace Kilo
{
    class ParticleGroup;
}

#include "AbstractParticle.hpp"
#include "ParticleField.hpp"
#include "Vector3.hpp"

namespace Kilo
{
    class ParticleGroup : public AbstractParticle
    {
        Q_OBJECT

        private:
            Color                _color;
            long double          _mass;
            long double          _radius;
            long double          _charge;

        public:
            Q_INVOKABLE ParticleGroup();
            virtual    ~ParticleGroup() override;

            void add(AbstractParticle*);

            std::vector<ParticleField*> getFields()       override;
            long double                 getCharge() const override;
            Color                       getColor () const override;
            long double                 getMass  () const override;
            long double                 getRadius() const override;

            void updateCoord() override;
            void updateForce() override;
            bool updateGroup() override;
            void  smartClean() override;
    };
}

#endif // KILO_PARTICLE_GROUP_HPP_INCLUDED
