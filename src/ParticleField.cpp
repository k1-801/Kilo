#include "../include/ParticleField.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QDebug>
// HCL
#include <HCL/Exception.hpp>
#include <HCL/Locker2.hpp>

namespace Kilo
{
    ParticleField::ParticleField(QString _name, bool m)
    {
        name = _name;
        _m = m;
    }

// long double
    ParticleFieldLongDouble::ParticleFieldLongDouble(QString _name, bool m, long double& src) : ParticleField(_name, m)
    {
        _src = &src;
    }

    QString* ParticleFieldLongDouble::getValue()
    {
        QString* result = new QString;
        QTextStream str(result);
        str.setRealNumberNotation(QTextStream::FixedNotation);
        str << *_src;
        return result;
    }

    void ParticleFieldLongDouble::setValue(QString value)
    {
        if(_m)
        {
            QTextStream str(&value);
            str >> *_src;
        }
    }

// Vector3
    ParticleFieldVector3::ParticleFieldVector3(QString _name, bool m, Hcl::Vector3& src) : ParticleField(_name, m)
    {
        _src = &src;
    }

    QString* ParticleFieldVector3::getValue()
    {
        QString* result = new QString;
        QTextStream str(result);
        str.setRealNumberNotation(QTextStream::FixedNotation);
        str << *_src;
        return result;
    }

    void ParticleFieldVector3::setValue(QString value)
    {
        _src->setValue(value);
    }

// QColor
    ParticleFieldQColor::ParticleFieldQColor(QString _name, bool m, QColor& src) : ParticleField(_name, m)
    {
        _src = &src;
    }

    QString* ParticleFieldQColor::getValue()
    {
        QString* result = new QString(_src->name());
        return result;
    }

    void ParticleFieldQColor::setValue(QString value)
    {
        _src->setNamedColor(value);
    }
}
