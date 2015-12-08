#include "../../include/Particles/Dot.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// HCL
#include <HCL/Factory.hpp>

REGISTER_IN_FACTORY(Kilo, AbstractParticle, Kilo, Dot)

namespace Kilo
{
    Dot::Dot():ParticleFinal(){}
    Dot::~Dot(){}

    QColor      Dot::getColor () const {return _color;}
    long double Dot::getCharge() const {return _charge;}

    const QVector<ParticleField*>& Dot::getFields()
    {
        static QVector<ParticleField*> _fields;
        if(_fields.isEmpty())
        {
            _fields.push_back(new ParticleFieldLongDouble(tr("Charge"), true, _charge));
            //_fields.push_back(new ParticleFieldVector3   (tr("Color"),  true, _color));
            _fields.push_back(new ParticleFieldVector3   (tr("Coord"),  true, _traectory.back()));
            _fields.push_back(new ParticleFieldLongDouble(tr("Mass"),   true, _mass));
            _fields.push_back(new ParticleFieldLongDouble(tr("Radius"), true, _radius));
        }
        return _fields;
    }

    long double Dot::getMass  () const {return _mass;}
    long double Dot::getRadius() const {return _radius;}

    void Dot::getData(QTextStream& str) const
    {
        ParticleFinal::getData(str);
        str << ' ' << _color << ' ' << _charge << ' ' << _mass << ' ' << _radius;
    }

    void Dot::setData(QTextStream& str)
    {
        ParticleFinal::setData(str);
        str >> _color >> _charge >> _mass >> _radius;
    }
}
