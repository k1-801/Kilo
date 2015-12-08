#pragma once

#ifndef KILO_PARTICLE_FIELD_HPP
#define KILO_PARTICLE_FIELD_HPP

// C++
#include <memory>
// Qt
#include <QString>

namespace Kilo
{
    class ParticleField;
    class ParticleFieldLongDouble;
    class ParticleFieldVector3;
}

#include "Vector3.hpp"

namespace Kilo
{
    class ParticleField
    {
        protected:
            bool _m;

        public:
            ParticleField(QString, bool);
            QString name;
            virtual QString* getValue() = 0;
            virtual void     setValue(QString&) = 0;
    };

    class ParticleFieldLongDouble : public ParticleField
    {
        protected:
            long double* _src;

        public:
            ParticleFieldLongDouble(QString, bool, long double&);
            QString* getValue();
            void     setValue(QString&);
    };

    class ParticleFieldVector3 : public ParticleField
    {
        protected:
            Vector3* _src;

        public:
            ParticleFieldVector3(QString, bool, Vector3&);
            QString* getValue();
            void     setValue(QString&);
    };
}

#endif // KILO_PARTICLE_FIELD_HPP
