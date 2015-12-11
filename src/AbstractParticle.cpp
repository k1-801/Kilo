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
#include <QDebug>
#include <QOpenGLWidget>
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

    void AbstractParticle::_addChild(ParticleW p)
    {
        ParticleS pw = p.lock();
        if(pw)
        {
            ParticleS pp = pw->getParent().lock();
            if(pp != shared_from_this())
            {
                pw->_parent = shared_from_this();
                _children.push_back(std::move(pw));
            }
            if(pp)
            {
                pp->_delChild(p);
            }
        }
        else
        {
            throw Hcl::Exception("Null pointer");
        }
    }

    void AbstractParticle::_delChild(ParticleW p)
    {
        ParticleS ps = p.lock();
        QList<ParticleS>::iterator it;
        for(it = _children.begin(); it != _children.end(); ++it)
        {
            if(ps == *it)
            {
                _children.erase(it);
                break;
            }
        }
        throw Hcl::Exception(tr("Particle to delete not found!"));
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
        uint64_t i = 0;
        glBegin(GL_LINE_STRIP);
        {
            for(Hcl::Coord coord : _traectory)
            {
                long double k1 = (long double)(i) / _traectory.size();
                glColor3f (color.red() * k1, color.green() * k1, color.blue() * k1);
                glVertex3d(coord.getX() * k3, coord.getY() * k3, coord.getZ() * k3);
                ++i;
            }
        }
        glEnd();
    }

    // DAPRECATED
    void AbstractParticle::_drawSphere()
    {
        QColor color = getColor();
        long double k3 = Core::getInstance().getZoom();
        long double alpha = 1.5 - getRadius() * k3;
        if(alpha < 0)
            alpha = 0;
        if(alpha > 1)
            alpha = 1;

        glPushMatrix();
        glTranslated(_traectory.back().getX() * k3, _traectory.back().getY() * k3, _traectory.back().getZ() * k3);
        glColor4f(color.red(), color.green(), color.blue(), alpha);
        GLUquadric* quad = gluNewQuadric();
        gluQuadricDrawStyle(quad, GLU_FILL);
        gluSphere(quad, getRadius() * k3, 32, 32);
        gluDeleteQuadric(quad);
        glPopMatrix();
    }

    void AbstractParticle::clearChildren()
    {
        for(ParticleS i : _children)
        {
            i.reset();
        }
        _children.clear();
    }

    void AbstractParticle::clearTraectory()
    {
        for(ParticleS i : _children)
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
        /*qDebug() << "Drawing particle: " << getName() << ' ' << "(children: " << _children.size() << ")";
        for(AbstractParticle* i : _children)
        {
            qDebug() << "Drawing: " << i << "\n";
            qDebug() << i->getName();
            i->draw();
        }

        Core& core = Core::getInstance();

        _drawDot();
        if(core.isDrawingTraectories())
            _drawTraectory();
        if(core.isDrawingSpheres())
            _drawSphere();*/
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

    long double       AbstractParticle::getCharge   () const {return 0;}
    QList<ParticleS>& AbstractParticle::getChildren () {return _children;}
    Hcl::Coord        AbstractParticle::getCoord    () const {return _traectory.back();}
    QString           AbstractParticle::getName     () const
    {
        QString name = metaObject()->className();
        int i, n = name.length();
        for(i = n - 1; i >= 0; --i)
            if(name[i] == ':')
                break;
        return name.right(n - i - 1);
    }
    ParticleW                AbstractParticle::getParent   () const {return _parent;}
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
        for(ParticleS i: _children)
        {
            str << i->getName() << ' ';
            i->writeData(str);
            str << '\n';
        }
    }

    void AbstractParticle::readData(QTextStream& str)
    {
        int i, n;
        QString tmpread;
        _traectory.clear();
        _traectory.push_back(0);
        clearChildren();
        str >> n;

        qDebug() << "Children: " << n;
        for(ParticleField* i: _fields)
        {
            str >> tmpread;
            i->setValue(tmpread);
            qDebug() << "Field \"" + i->name + "\" set to " + tmpread;
        }
        for(i = 0; i < n; ++i)
        {
            str >> tmpread;
            qDebug() << "\nRequesting particle: " << tmpread;
            std::shared_ptr<AbstractParticle> c = Hcl::Factory<AbstractParticle>::getInstance().get(tmpread);
            qDebug() << "Address: " << c.get();
            c->setParent(shared_from_this());
            c->readData(str);
        }
        str >> _traectory.front();
        updateGroup();
    }

    void AbstractParticle::setParent(ParticleW p)
    {
        try
        {
            ParticleS parent_new = p.lock();
            ParticleS parent_old = _parent.lock();
            _parent = parent_new;
            if(parent_new)
            {
                parent_new->_addChild(shared_from_this());
            }
            if(parent_old)
            {
                parent_old->_delChild(shared_from_this());
            }
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
}
