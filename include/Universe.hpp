#pragma once

#ifndef KILO_UNIVERSE_HPP
#define KILO_UNIVERSE_HPP

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QObject>
#include <QString>

namespace Kilo
{
    class Universe;
}

#include "ParticleGroup.hpp"

namespace Kilo
{
    class Universe : public ParticleGroup
    {
        Q_OBJECT

        public:
            Universe();
            ~Universe();

            static Universe& getInstance();
            bool updateGroup();
    };
}

#endif // KILO_UNIVERSE_HPP
