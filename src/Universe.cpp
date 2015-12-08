#include "../include/Universe.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

//  Qt
#include <QFile>
#include <QDebug>
// Kilo
#include "../include/Core.hpp"

namespace Kilo
{
    Universe:: Universe() : ParticleGroup(){}
    Universe::~Universe(){}

    Universe& Universe::getInstance()
    {
        static Universe _instance;
        return _instance;
    }

    bool Universe::updateGroup()
    {
        for(AbstractParticle* i : _children)
        {
            i->updateGroup();
        }
        return false;
    }
}
