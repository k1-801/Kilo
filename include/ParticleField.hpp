#pragma once

#ifndef KILO_PARTICLE_FIELD_HPP
#define KILO_PARTICLE_FIELD_HPP

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// C++
#include <memory>
// Qt
#include <QColor>
#include <QString>
// HCL
#include <HCL/Vector3.hpp>

namespace Kilo
{
    class ParticleField;
    class ParticleFieldLongDouble;
    class ParticleFieldVector3;
    class ParticleFieldQColor;
}

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
            virtual void     setValue(QString) = 0;
    };

    class ParticleFieldLongDouble : public ParticleField
    {
        protected:
            long double* _src;

        public:
            ParticleFieldLongDouble(QString, bool, long double&);
            QString* getValue()        override;
            void     setValue(QString) override;
    };

    class ParticleFieldVector3 : public ParticleField
    {
        protected:
            Hcl::Vector3* _src;

        public:
            ParticleFieldVector3(QString, bool, Hcl::Vector3&);
            QString* getValue()        override;
            void     setValue(QString) override;
    };

    class ParticleFieldQColor : public ParticleField
    {
        protected:
            QColor* _src;

        public:
            ParticleFieldQColor(QString, bool, QColor&);
            QString* getValue()        override;
            void     setValue(QString) override;
    };
}

#endif // KILO_PARTICLE_FIELD_HPP
