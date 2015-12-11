#include "../include/WidgetParticleList.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Kilo
#include "../include/Universe.hpp"

namespace Kilo
{
    WidgetParticleList::WidgetParticleList(QWidget* parent) : QTreeWidget(parent)
    {
        reload();
    }

    void WidgetParticleList::_load(QTreeWidgetItem* parent, ParticleWP curr, int level)
    {
        ParticleSP c = curr.lock();
        QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(c->getName()));
        parent->addChild(item);
        _c[item] = std::make_pair(c, level);
        for(ParticleSP i : c->getChildren())
        {
            _load(item, i, level + 1);
        }
    }

    void WidgetParticleList::reload()
    {
        Universe& u = Universe::getInstance();
        _c.clear();
        QTreeWidgetItem* uitem = new QTreeWidgetItem(QStringList("Universe"));
        QList<ParticleSP>& list = u.getChildren();
        _c[uitem] = std::make_pair(u.self(), 0);
        for(ParticleSP i : list)
        {
            _load(uitem, i, 1);
        }
        clear();
        addTopLevelItem(uitem);
    }
}
