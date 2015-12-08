#pragma once

#ifndef KILO_UNIVERSE_HPP
#define KILO_UNIVERSE_HPP

// Qt
#include <QObject>
#include <QString>
#include <QtXml>

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
