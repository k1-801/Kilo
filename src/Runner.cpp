#include "../include/Runner.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QCoreApplication>
// Kilo
#include "../include/Core.hpp"
#include "../include/Universe.hpp"

namespace Kilo
{
    Runner::Runner(){}
    Runner::~Runner(){}

    Runner& Runner::getInstance()
    {
        static Runner _instance;
        return _instance;
    }

    bool Runner::isSimRunning()
    {
        return _b;
    }

    void Runner::start()
    {
        Core    & core = Core    ::getInstance();
        Universe& u    = Universe::getInstance();
        if(!_h)
        {
            _h = true;
            while(_h)
            {
                QCoreApplication::processEvents();
                while(_b)
                {
                    QCoreApplication::processEvents();
                    core.mutexParticles.lock();
                    u.updateForce();
                    u.updateCoord();
                    u.updateGroup();
                    u.smartClean();
                    core.mutexParticles.unlock();
                }
                QObject().thread()->usleep(10);
            }
        }
    }

    void Runner::stop()
    {
        _h = false;
    }

    void Runner::simRun()
    {
        _b = true;
        emit stateChanged(true);
    }

    void Runner::simStop()
    {
        _b = false;
        emit stateChanged(false);
    }
}
