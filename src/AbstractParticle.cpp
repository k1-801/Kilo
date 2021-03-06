#include "../include/AbstractParticle.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// C
#include <math.h>
// C++
#include <memory>
// Qt
#include <QOpenGLWidget>
#include <QDebug>
// GL
#include <GL/glu.h>
// HCL
#include <HCL/Factory.hpp>
#include <HCL/Vector3.hpp>
#include <HCL/Operators.hpp>
// Kilo
#include "../include/Core.hpp"
#include "../include/Phy.hpp"

namespace Kilo
{
    AbstractParticle::AbstractParticle()
    {
        _sc_index = 0;
        _traectory.clear();
        _traectory.push_back(0);
        _parent.reset();
        _fields.push_back(new ParticleFieldVector3 (tr("Coord"),  true, _traectory.back()));
        _fields.push_back(new ParticleFieldVector3 (tr("Force"),  true, _force));
        _fields.push_back(new ParticleFieldVector3 (tr("Speed"),  true, _speed));
    }
    AbstractParticle::~AbstractParticle(){}

    void AbstractParticle::_addChild(ParticleWP p)
    {
        ParticleSP pw = p.lock();
        if(pw)
        {
            ParticleSP pp = pw->getParent().lock();
            if(pp != self())
            {
                pw->_parent = self();
                _children.push_back(pw);
                if(pp)
                {
                    pp->_delChild(p);
                }
            }
        }
        else
        {
            throw Hcl::Exception("Null pointer");
        }
    }

    void AbstractParticle::_delChild(ParticleWP p)
    {
        ParticleSP ps = p.lock();
        if(ps)
        {
            QList<ParticleSP>::iterator it;
            for(it = _children.begin(); it != _children.end(); ++it)
            {
                if(ps == *it)
                {
                    _children.erase(it);
                    break;
                }
            }
        }
        else
        {
            throw Hcl::Exception("Null pointer");
        }
    }

    // DEPRECATED
    void AbstractParticle::_drawDot()
    {
        QColor color = getColor();
        long double k3 = Core::getInstance().getZoom();
        glBegin(GL_POINTS);
        {
            Hcl::Coord coo = _traectory.back();
            glColor3f (color.red(), color.green(), color.blue());
            glVertex3d(coo.getX() * k3, coo.getY() * k3, coo.getZ() * k3);
        }
        glEnd();
    }

    // DEPRECATED
    void AbstractParticle::_drawTraectory()
    {
        QColor color = getColor();
        long double k3 = Core::getInstance().getZoom();
        long double k2 = 0, n = _traectory.size() * 4;
        //qDebug() << "Traectory size is" << n;

        glBegin(GL_LINE_STRIP);
        {
            for(Hcl::Coord coord : _traectory)
            {
                long double k1 = 0.25 + k2 / n;
                //qDebug() << k1;
                glColor3f (color.redF() * k1, color.greenF() * k1, color.blueF() * k1);
                glVertex3d(coord.getX() * k3, coord.getY() * k3, coord.getZ() * k3);
                k2 += 3;
            }
        }

        glEnd();
        glBegin(GL_POINT);
        glColor3f (1, 0, 0);
        glVertex3d(_traectory.first().getX() * k3, _traectory.first().getY() * k3, _traectory.first().getZ() * k3);
        glEnd();
    }

    void AbstractParticle::clearChildren()
    {
        for(ParticleSP i : _children)
        {
            i.reset();
        }
        _children.clear();
    }

    void AbstractParticle::clearTraectory()
    {
        for(ParticleSP i : _children)
        {
            i->clearTraectory();
        }
        Hcl::Coord t = _traectory.back();
        _traectory.clear();
        _traectory.push_back(t);
    }

    // DEPRECATED
    void AbstractParticle::draw()
    {
        //qDebug() << "Drawing " << getName() << " with " << _children.size() << " children";
        for(ParticleSP i : _children)
        {
            i->draw();
        }

        Core& core = Core::getInstance();

        _drawDot();
        if(core.isDrawingTraectories())
            _drawTraectory();
    }

    QVector<ParticleField*>& AbstractParticle::getFields()
    {
        return _fields;
    }

    void AbstractParticle::_fitTraectory()
    {
        Core& core = Core::getInstance();
        if(core.isAutoclean())
        {
            int k = core.getShadow();
            while((int)(_traectory.size()) > k)
            {
                _traectory.pop_front();
            }
        }
    }

    long double        AbstractParticle::getCharge   () const {return 0;}
    QList<ParticleSP>& AbstractParticle::getChildren () {return _children;}
    Hcl::Coord         AbstractParticle::getCoord    () const {return _traectory.back();}
    QString            AbstractParticle::getName     () const {return metaObject()->className();}
    ParticleWP               AbstractParticle::getParent   () const {return _parent;}
    Hcl::Speed               AbstractParticle::getSpeed    () const {return _speed;}
    const QList<Hcl::Coord>& AbstractParticle::getTraectory() const {return _traectory;}

    void AbstractParticle::writeData(QTextStream& str) const
    {
        for(ParticleField* i: _fields)
        {
            QString* tmp = i->getValue();
            str << *tmp;
            delete tmp;
        }
        str << _children.size() << '\n';
        for(ParticleSP i: _children)
        {
            str << i->getName() << ' ';
            i->writeData(str);
            str << '\n';
        }
    }

    void AbstractParticle::readData(QTextStream& str)
    {
        try
        {
            int i, n;
            QString tmpread;
            _traectory.clear();
            _traectory.push_back(0);
            clearChildren();
            str >> n;

            for(ParticleField* i: _fields)
            {
                str >> tmpread;
                i->setValue(tmpread);
            }
            for(i = 0; i < n; ++i)
            {
                str >> tmpread;
                ParticleSP c = Hcl::Factory<AbstractParticle>::getInstance().get(tmpread);
                c->setParent(self());
                c->readData(str);
            }
            updateGroup();
        }
        CATCH("AbstractParticle::readData");
    }

    void AbstractParticle::setParent(ParticleWP p)
    {
        try
        {
            ParticleSP parent_new = p.lock();
            ParticleSP parent_old = _parent.lock();

            if(parent_new != parent_old)
            {
                if(parent_new)
                {
                    parent_new->_addChild(self());
                }
                if(parent_old)
                {
                    parent_old->_delChild(self());
                }
            }
            _parent = parent_new;
        }
        CATCH("AbstractParticle::setParent");
    }

    void AbstractParticle::smartClean()
    {
        Core& core = Core::getInstance();
        if(core.isSmartClean())
        {
            ++_sc_index;
            if(_sc_index >= core.getSmartClean())
            {
                _sc_index = 0;
            }
            else
            {
                if(_traectory.size() > 3)
                {
                    auto it = _traectory.end(); --it; --it; // The only way to erase pre-last member
                    _traectory.erase(it);
                }
            }
        }
    }

    ParticleSP AbstractParticle::self()
    {
        return shared_from_this();
    }
}
