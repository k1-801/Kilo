#include <utility>

#include "ParticleFactory.hpp"
#include "Core.hpp"

namespace Kilo
{
    ParticleFactory::ParticleFactory(){}
    ParticleFactory::~ParticleFactory(){}

    ParticleFactory& ParticleFactory::getInstance()
    {
        static ParticleFactory _instance;
        return _instance;
    }

    void ParticleFactory::add(QString name, ParticleFunc gen)
    {
        if(name.isEmpty())
            throw std::invalid_argument( "Kilo::ParticleFactory::add(): no key given");
        if(!gen)
            throw std::invalid_argument( "Kilo::ParticleFactory::add(): no object given");
        if(_c.find(name) != _c.end())
            throw std::invalid_argument(("Kilo::ParticleFactory::add(): class \"" + name + "\" already registered!").toStdString());
        _c.insert(std::make_pair(name, gen));
    }

    AbstractParticle* ParticleFactory::get(QString name)
    {
        if(_c.find(name) == _c.end())
            throw std::invalid_argument(("Kilo::ParticleFactory::get(): class \"" + name + "\" is NOT registered!").toStdString());
        return _c[name]();
    }
}
