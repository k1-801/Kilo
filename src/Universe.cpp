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
    Universe:: Universe() : ParticleGroup()
    {
        _fields.clear(); // Universe is a static entity and should have no data to read.
    }
    Universe::~Universe(){}

    Universe& Universe::getInstance()
    {
//        static Universe _instance;
        static std::shared_ptr<Universe> _instance = std::make_shared<Universe>();
        return *_instance;
    }

    bool Universe::updateGroup()
    {
        for(ParticleSP i : _children)
        {
            i->updateGroup();
        }
        return false;
    }
}
