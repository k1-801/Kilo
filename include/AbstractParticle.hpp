#pragma once

#ifndef KILO_PARTICLE_HPP_INCLUDED
#define KILO_PARTICLE_HPP_INCLUDED

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// C
#include <stdint.h>
// C++
#include <list>
#include <memory>
#include <vector>
// Qt
#include <QColor>
#include <QTextStream>
#include <QObject>
#include <QString>

namespace Kilo
{
    class AbstractParticle;
}

// Kilo
#include "ParticleField.hpp"

namespace Kilo
{
    class AbstractParticle : public QObject
    {
        Q_OBJECT

        private:
            int _sc_index;

        protected:
            QList<AbstractParticle*> _children;
            Hcl::Traectory           _traectory;
            Hcl::Force               _force;
            AbstractParticle*        _parent;
            Hcl::Speed               _speed;

            void _fitTraectory();
            void _addChild(AbstractParticle*);
            void _delChild(AbstractParticle*);

            void _drawDot      (); // Deprecated
            void _drawTraectory(); // Deprecated
            void _drawSphere   (); // Deprecated

        public:
            AbstractParticle();
            virtual ~AbstractParticle();

            void clearChildren();
            void clearTraectory();

            virtual void draw();

            virtual QColor                         getColor    () const = 0;
            virtual long double                    getCharge   () const;
            QList<AbstractParticle*>&              getChildren ();
            Hcl::Coord                             getCoord    () const;
            virtual const QVector<ParticleField*>& getFields   () = 0;
            virtual long double                    getMass     () const = 0;
            QString                                getName     () const;
            AbstractParticle*                      getParent   () const;
            virtual long double                    getRadius   () const = 0;
            virtual Hcl::Speed                     getSpeed    () const;
            const QList<Hcl::Coord>&               getTraectory() const;

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
