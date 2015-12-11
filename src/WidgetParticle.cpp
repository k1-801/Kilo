#include "../include/WidgetParticle.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// HCL
#include <HCL/Exception.hpp>

namespace Kilo
{
    WidgetParticle::WidgetParticle(QWidget* parent) : QTableWidget(parent)
    {

    }

    void WidgetParticle::_update()
    {
        clear();
        ;
    }

    void WidgetParticle::setParticle(ParticleWP p)
    {
        ParticleSP p2 = p.lock();
        if(p2)
        {
            _p = p2;
            this->setHorizontalHeaderLabels(QStringList(p2->getName()));
            _update();
        }
        else
        {
            throw Hcl::Exception("WidgetParticle::setParticle(): Null pointer");
        }
    }
}

