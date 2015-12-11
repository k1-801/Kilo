#include "../include/ParticleGroup.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// HCL
#include <HCL/Factory.hpp>
// Kilo
#include "../include/Core.hpp"

REGISTER_IN_FACTORY(Kilo, AbstractParticle, Kilo, ParticleGroup)

namespace Kilo
{
    ParticleGroup::ParticleGroup() : AbstractParticle()
    {
        _fields.push_back(new ParticleFieldLongDouble(tr("Mass"),   false, _mass));
        _fields.push_back(new ParticleFieldLongDouble(tr("Radius"), false, _radius));
    }
    ParticleGroup::~ParticleGroup(){}

    long double ParticleGroup::getCharge() const {return _charge;}
    QColor      ParticleGroup::getColor () const {return _color;}
    long double ParticleGroup::getMass  () const {return _mass;}
    long double ParticleGroup::getRadius() const {return _radius;}

    void ParticleGroup::updateCoord()
    {
        for(std::shared_ptr<AbstractParticle> i : _children)
        {
            i->updateCoord();
        }
    }

    void ParticleGroup::updateForce()
    {
        for(ParticleS i : _children)
        {
            i->updateForce();
        }
    }

    bool ParticleGroup::updateGroup()
    {
        ParticleS p = _parent.lock();
        if(!p)
        {
            Core::getInstance().error("ParticleGroup without a parent!");
            exit(EXIT_FAILURE);
        }
        bool b = false;

        // Update children
        for(ParticleS c : _children)
        {
            c->updateGroup();
        }

        // Update current group
        long double r;

        // Check siblings for possible merging
        for(ParticleS c : p->getChildren())
        {
            if((c->getCoord() - getCoord()).length() < _radius)
            {
                // MERGE!!!1!
            }
        }

        // State variales setting
        _fitTraectory();
        _charge = 0;
        _color  = QColor();
        _traectory.push_back(0);
        _mass   = 0;
        _radius = 0;

        uint64_t sr = 0, sg = 0, sb = 0;
        for(ParticleS c : _children)
        {
            _charge       += c->getCharge();
            _traectory.back() += c->getCoord() * c->getMass();
            _mass         += c->getMass ();
            sr += c->getColor().red();
            sg += c->getColor().green();
            sb += c->getColor().blue();
        }
        _color.setRgb(sr / _children.size(), sg / _children.size(), sb / _children.size());
        _traectory.back() /= _children.size() * _mass;

        for(ParticleS c : _children)
        {
            r = (c->getCoord() - _traectory.back()).length() + c->getRadius();
            if( _radius < r)
                _radius = r;
        }
        return b;
    }

    void ParticleGroup::smartClean()
    {
        AbstractParticle::smartClean();
        for(ParticleS i : _children)
        {
            i->smartClean();
        }
    }
}
