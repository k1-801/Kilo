#pragma once

#ifndef KILO_WIDGET_PARTICLE_LIST_HPP
#define KILO_WIDGET_PARTICLE_LIST_HPP

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// C++
#include <map>
// Qt
#include <QTreeWidget>

namespace Kilo
{
    class WidgetParticleList;
}

// Kilo
#include "AbstractParticle.hpp"

namespace Kilo
{
    class WidgetParticleList : public QTreeWidget
    {
        private:
            std::map <QTreeWidgetItem*, std::pair<ParticleSP, int> > _c;

            void _load(QTreeWidgetItem*, ParticleWP, int = 0);

        public:
            WidgetParticleList(QWidget* = 0);
            void reload();

            friend class DialogParticleList;
    };
}

#endif // KILO_WIDGET_PARTICLE_LIST_HPP
