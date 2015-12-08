#include "../include/WidgetParticle.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

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

    void WidgetParticle::setParticle(AbstractParticle* p)
    {
        _p = p;
        this->setHorizontalHeaderLabels(QStringList(p->getName()));
        _update();
    }
}

