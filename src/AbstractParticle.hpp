#pragma once

#ifndef KILO_PARTICLE_HPP_INCLUDED
#define KILO_PARTICLE_HPP_INCLUDED

// C
#include <stdint.h>
// C++
#include <list>
#include <memory>
#include <vector>
// Qt
#include <QTextStream>
#include <QObject>
#include <QString>

namespace Kilo
{
    class AbstractParticle;
}

#include "ParticleField.hpp"
#include "Vector3.hpp"

namespace Kilo
{
    class AbstractParticle : public QObject
    {
        Q_OBJECT

        private:
            int _sc_index;

        protected:
            QList<AbstractParticle*> _children;
            QList<Coord>             _coord;
            Force                    _force;
            AbstractParticle*        _parent;
            Speed                    _speed;

            void _fitTraectory();
            void _addChild(AbstractParticle*);
            void _delChild(AbstractParticle*);

            volatile void _drawDot();
            volatile void _drawTraectory();
            volatile void _drawSphere();

        public:
            AbstractParticle();
            virtual ~AbstractParticle();

            void clearChildren();
            void clearTraectory();

            virtual void draw();

            virtual Color                       getColor    () const = 0;
            virtual long double                 getCharge   () const;
            QList<AbstractParticle*>&           getChildren ();
            Coord                               getCoord    () const;
            virtual std::vector<ParticleField*> getFields   () = 0;
            virtual long double                 getMass     () const = 0;
            QString                             getName     () const;
            AbstractParticle*                   getParent   () const;
            virtual long double                 getRadius   () const = 0;
            virtual Speed                       getSpeed    () const;
            const QList<Coord>&                 getTraectory() const;

            virtual void getData(QTextStream&) const;
            virtual void setData(QTextStream&);
            void setParent(AbstractParticle*);

            virtual void updateCoord() = 0;
            virtual void updateForce() = 0;
            virtual bool updateGroup() = 0;
            virtual void  smartClean();
    };
}

#endif // KILO_PARTICLE_HPP_INCLUDED
