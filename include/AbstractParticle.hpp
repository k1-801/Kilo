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
#include <QVector>

namespace Kilo
{
    class AbstractParticle;
    typedef std::shared_ptr<AbstractParticle> ParticleS;
    typedef std::  weak_ptr<AbstractParticle> ParticleW;
}

// Kilo
#include "ParticleField.hpp"

namespace Kilo
{
    class AbstractParticle : public QObject, public std::enable_shared_from_this<AbstractParticle>
    {
        Q_OBJECT

        private:
            int _sc_index;

        protected:
            QList<ParticleS>        _children;
            QVector<ParticleField*> _fields;
            Hcl::Traectory          _traectory;
            Hcl::Force              _force;
            ParticleW               _parent;
            Hcl::Speed              _speed;

            void _fitTraectory();
            void _addChild(ParticleW);
            void _delChild(ParticleW);

            void _drawDot      (); // Deprecated
            void _drawTraectory(); // Deprecated
            void _drawSphere   (); // Deprecated

        public:
            AbstractParticle();
            virtual ~AbstractParticle();

            void clearChildren();
            void clearTraectory();

            void draw();

            virtual QColor           getColor    () const = 0;
            virtual long double      getCharge   () const;
            QList<ParticleS>&        getChildren ();
            Hcl::Coord               getCoord    () const;
            QVector<ParticleField*>& getFields   ();
            virtual long double      getMass     () const = 0;
            QString                  getName     () const;
            ParticleW                getParent   () const;
            virtual long double      getRadius   () const = 0;
            virtual Hcl::Speed       getSpeed    () const;
            const QList<Hcl::Coord>& getTraectory() const;

            void  readData(QTextStream&);
            void writeData(QTextStream&) const;

            void setParent(ParticleW);

            virtual void updateCoord() = 0;
            virtual void updateForce() = 0;
            virtual bool updateGroup() = 0;
            virtual void  smartClean();
    };
}

#endif // KILO_PARTICLE_HPP_INCLUDED
