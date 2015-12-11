#include "../include/ParticleFinal.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Kilo
#include "../include/Phy.hpp"
#include "../include/Core.hpp"

namespace Kilo
{
    ParticleFinal::ParticleFinal() : AbstractParticle(){}
    ParticleFinal::~ParticleFinal(){}

    void ParticleFinal::updateCoord()
    {
        _fitTraectory();
        long double precision = Core::getInstance().getPrecision();
        Hcl::Coord coord = _traectory.back();
        _speed += _force / getMass() / precision;
        coord  += _speed / precision;
        _traectory.push_back(coord);
    }

    void ParticleFinal::updateForce()
    {
        ParticleS p;
        ParticleS prev = shared_from_this();
        long double m0 = getMass(), m1;
        long double q0 = getCharge(), q1;

        _force = 0;
        for(p = _parent.lock(); p; p = p->getParent().lock())
        {
            for(std::shared_ptr<AbstractParticle> c : p->getChildren())
            {
                if(c != prev)
                {
                    Hcl::Vector3 diff = getCoord() - c->getCoord();
                    long double dl = diff.length();
                    q1 = c->getCharge();
                    m1 = c->getMass();

                    Hcl::Force qforce =  (diff * PHY_K * q0 * q1) / (dl * dl * dl); // Qulon
                    Hcl::Force mforce = -(diff * PHY_G * m0 * m1) / (dl * dl * dl); // Gravity

                    _force += qforce + mforce;
                }
            }
            prev = p;
        }
    }

    bool ParticleFinal::updateGroup(){return false;}
}
