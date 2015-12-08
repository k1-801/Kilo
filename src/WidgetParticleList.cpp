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

    void WidgetParticleList::_load(QTreeWidgetItem* parent, AbstractParticle* curr, int level)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(curr->getName()));
        parent->addChild(item);
        _c[item] = std::make_pair(curr, level);
        QList<AbstractParticle*>& l = curr->getChildren();
        for(AbstractParticle* i : l)
        {
            _load(item, i, level + 1);
        }
    }

    void WidgetParticleList::reload()
    {
        Universe& u = Universe::getInstance();
        _c.clear();
        QTreeWidgetItem* uitem = new QTreeWidgetItem(QStringList("Universe"));
        QList<AbstractParticle*>& list = u.getChildren();
        _c[uitem] = std::make_pair(&u, 0);
        for(AbstractParticle* i : list)
        {
            _load(uitem, i, 1);
        }
        clear();
        addTopLevelItem(uitem);
    }
}
