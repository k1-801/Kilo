#pragma once

#ifndef KILO_PARTICLE_FACTORY_HPP
#define KILO_PARTICLE_FACTORY_HPP

// C++
#include <memory>
#include <map>
// Qt
#include <QString>

namespace Kilo
{
    class ParticleFactory;
}

#include "AbstractParticle.hpp"

namespace Kilo
{
    using ParticleFunc = AbstractParticle*(*)();

    class ParticleFactory
    {
        private:
            std::map<QString, ParticleFunc> _c;

            ParticleFactory();
            ~ParticleFactory();

        public:
            static ParticleFactory& getInstance();
            void      add(QString, ParticleFunc);
            AbstractParticle* get(QString);
    };
}

#define REGISTER_PARTICLE(type) \
namespace \
{ \
    Kilo::AbstractParticle* ParticleFactoryGenerator_##type(){return new type();} \
    class ParticleFactoryRegistrator_##type \
    { \
        private: \
            static ParticleFactoryRegistrator_##type _instance; \
            ParticleFactoryRegistrator_##type() \
            { \
                Kilo::ParticleFactory::getInstance().add(#type, &ParticleFactoryGenerator_##type); \
            } \
    }; \
    ParticleFactoryRegistrator_##type ParticleFactoryRegistrator_##type::_instance; \
}

#endif // KILO_PARTICLE_FACTORY_HPP
