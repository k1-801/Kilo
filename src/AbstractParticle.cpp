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
// GL
#include <GL/glu.h>
// HCL
#include <HCL/Factory.hpp>
#include <HCL/Vector3.hpp>
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
        _parent = 0;
    }
    AbstractParticle::~AbstractParticle(){}

    void AbstractParticle::_addChild(AbstractParticle* p)
    {
        _children.push_back(p);
    }

    void AbstractParticle::_delChild(AbstractParticle* p)
    {
        QList<AbstractParticle*>::iterator it;
        for(it = _children.begin(); it != _children.end(); ++it)
        {
            if(p == *it)
            {
                _children.erase(it);
                break;
            }
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
        for(AbstractParticle* i : _children)
        {
            delete i;
        }
        _children.clear();
    }

    void AbstractParticle::clearTraectory()
    {
        for(AbstractParticle* i : _children)
        {
            i->clearTraectory();
        }
        Hcl::Coord t = _traectory.back();
        _traectory.clear();
        _traectory.push_back(t);
    }

    void AbstractParticle::draw()
    {
        for(AbstractParticle* i : _children)
        {
            i->draw();
        }

        Core& core = Core::getInstance();

        _drawDot();
        if(core.isDrawingTraectories())
            _drawTraectory();
        if(core.isDrawingSpheres())
            _drawSphere();
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

    long double               AbstractParticle::getCharge   () const {return 0;}
    QList<AbstractParticle*>& AbstractParticle::getChildren () {return _children;}
    Hcl::Coord                AbstractParticle::getCoord    () const {return _traectory.back();}
    QString                   AbstractParticle::getName     () const
    {
        QString name = metaObject()->className();
        int i, n = name.length();
        for(i = n - 1; i >= 0; --i)
            if(name[i] == ':')
                break;
        return name.right(n - i - 1);
    }
    AbstractParticle*        AbstractParticle::getParent   () const {return _parent;}
    Hcl::Speed               AbstractParticle::getSpeed    () const {return _speed;}
    const QList<Hcl::Coord>& AbstractParticle::getTraectory() const {return _traectory;}

    void AbstractParticle::getData(QTextStream& str) const
    {
        str << _children.size() << '\n';
        for(AbstractParticle* i : _children)
        {
            str << i->getName() << ' ';
            i->getData(str);
            str << '\n';
        }
    }

    void AbstractParticle::setData(QTextStream& str)
    {
        int i, n;
        clearChildren();
        str >> n;
        for(i = 0; i < n; ++i)
        {
            QString name;
            str >> name;
            std::shared_ptr<AbstractParticle> c = Hcl::Factory<AbstractParticle>::getInstance().get(name);
            c->setParent(this);
            c->setData(str);
        }
        updateGroup();
    }

    void AbstractParticle::setParent(AbstractParticle* p)
    {
        if(_parent)
        {
            _parent->_delChild(this);
        }
        _parent = p;
        if(p)
        {
            p->_addChild(this);
        }
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
