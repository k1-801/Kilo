#include "../../include/Particles/Dot.hpp"

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
#include <HCL/Factory.hpp>

REGISTER_IN_FACTORY(Kilo, AbstractParticle, Kilo, Dot)

namespace Kilo
{
    Dot::Dot() : ParticleFinal()
    {
        _fields.push_back(new ParticleFieldLongDouble(tr("Charge"), true, _charge));
        _fields.push_back(new ParticleFieldQColor    (tr("Color"),  true, _color));
        _fields.push_back(new ParticleFieldLongDouble(tr("Mass"),   true, _mass));
        _fields.push_back(new ParticleFieldLongDouble(tr("Radius"), true, _radius));
    }
    Dot::~Dot(){}

    QColor      Dot::getColor () const {return _color;}
    long double Dot::getCharge() const {return _charge;}
    long double Dot::getMass  () const {return _mass;}
    long double Dot::getRadius() const {return _radius;}
}
