#include "../include/Core.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QApplication>
#include <QFile>
#include <QMessageBox>
// HCL
#include <HCL/Exception.hpp>
// Kilo
#include "../include/Phy.hpp"
#include "../include/Runner.hpp"
#include "../include/Particles/Dot.hpp"

namespace Kilo
{
    Core::Core()
    {
        _p_orig    = 0;
        _precision = 1;
        _shadow    = 50000;
        _z_orig    = 0;
        _zoom      = 1;
        _autoclean   = true;
        _spheres     = true;
        _traectories = true;
    }

    Core::~Core()
    {
        Runner::getInstance().stop();
        mutexParticles.unlock();
    }

    Core& Core::getInstance()
    {
        static Core _instance;
        return _instance;
    }

    // Mess next

    void Core::run()
    {
        try
        {
            _w = new MainWindow();
            _w->show();

            Runner  * r = &Runner  ::getInstance();
            r->moveToThread(&_runner);
            connect(&_runner, &QThread::started,  r, &Runner    ::start);
            connect(&_runner, &QThread::finished, r, &QObject   ::deleteLater);
            connect(this,     &Core   ::stop,     r, &Runner    ::stop);
            _runner.start();
        }
        CATCH("Core::run");
    }

    bool Core::isAutoclean         (){return _autoclean;}
    bool Core::isDrawingSpheres    (){return _spheres;}
    bool Core::isDrawingTraectories(){return _traectories;}
    bool Core::isSmartClean        (){return _smartclean;}
    int   Core::getShadow    (){return _shadow;}
    float Core::getPrecision (){return _precision;}
    float Core::getZoom      (){return _zoom;}
    int   Core::getSmartClean(){return _sc_v;}

    QString Core::getPath()
    {
        return _path;
    }

    void Core::clear()
    {
        try
        {
            mutexParticles.lock();
            Universe::getInstance().clearTraectory();
            mutexParticles.unlock();
        }
        CATCH("Core::clear");
    }

    void Core::error(QString text)
    {
        if(text == QString::null){text = tr("Unknown error");}
        QMessageBox::critical(_w, "Kilo", text, QMessageBox::Ok);
    }

    void Core::open(QString p)
    {
        try
        {
            QFile f(p);
            if(!f.open(QFile::ReadOnly))
            {
                error(tr("Failed to open file"));
                return;
            }
            if(f.read(4) != "kmf.")
            {
                error(tr("File is not a Kilo Model File"));
                return;
            }
            _path = p;
            QTextStream str(&f);

            str >> _shadow >> _p_orig >> _z_orig >> _sc_v >> _autoclean >> _spheres >> _traectories >> _smartclean;
            _precision = pow(1.1, _p_orig);
            _zoom      = pow(1.1, _z_orig);

            _w->modReceiver(_p_orig, _shadow, _sc_v, _z_orig, _autoclean, _smartclean, _spheres, _traectories);
            Universe::getInstance().readData(str);
            f.close();
        }
        CATCH("Core::open");
    }

    void Core::save(QString p)
    {
        // TODO: check extension
        try
        {
            QFile f(p + '~');
            if(!f.open(QFile::WriteOnly))
            {
                error(tr("Failed to open file"));
                return;
            }
            QTextStream str(&f);
            str.setRealNumberNotation(QTextStream::FixedNotation);
            str.setRealNumberPrecision(16);
            str << "kmf." << _shadow << ' ' << _p_orig << ' ' << _z_orig << ' ' << _sc_v << ' ' << _autoclean << ' ' << _spheres << ' ' << _traectories << ' ' << _smartclean << '\n';
            Universe::getInstance().writeData(str);
            str.flush();
            f.close();
            if(QFile::exists(p) && !QFile::remove(p))
            {
                error(tr("Failed to remove old file"));
                return;
            }
            f.rename(p);
            _path = p;
        }
        CATCH("Core::save");
    }

    void Core::setModparams(int p, int s, int sc_v, int z, bool ac, bool sc, bool sp, bool tr)
    {
        _p_orig      = p;
        _shadow      = s;
        _z_orig      = z;
        _sc_v        = sc_v;
        _autoclean   = ac;
        _smartclean  = sc;
        _spheres     = sp;
        _traectories = tr;
        _precision = pow(1.1, _p_orig);
        _zoom      = pow(1.1, _z_orig);
    }

    void Core::quit()
    {
        emit stop();
    }
}
