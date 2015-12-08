#pragma once

#ifndef KILO_WIDGET_PARTICLE_LIST_HPP
#define KILO_WIDGET_PARTICLE_LIST_HPP

#include <map>
#include <QTreeWidget>

namespace Kilo
{
    class WidgetParticleList;
}

#include "AbstractParticle.hpp"

namespace Kilo
{
    class WidgetParticleList : public QTreeWidget
    {
        private:
            std::map <QTreeWidgetItem*, std::pair<AbstractParticle*, int>> _c;

            void _load(QTreeWidgetItem*, AbstractParticle*, int = 0);

        public:
            WidgetParticleList(QWidget* = 0);
            void reload();

            friend class DialogParticleList;
    };
}

#endif // KILO_WIDGET_PARTICLE_LIST_HPP
