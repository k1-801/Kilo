#pragma once

#ifndef KILO_CORE_HPP_INCLUDED
#define KILO_CORE_HPP_INCLUDED

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
// Qt
#include <QObject>
#include <QMutex>
#include <QThread>
#include <QTranslator>

namespace Kilo
{
    class Core;
}

#include "MainWindow.hpp"
#include "Universe.hpp"

namespace Kilo
{
    class Core : public QObject
    {
        Q_OBJECT
        private:
            int   _shadow;
            float _precision;
            int   _sc_v;
            float _zoom;
            bool  _autoclean;
            bool  _spheres;
            bool  _smartclean;
            bool  _traectories;
            int   _p_orig;
            int   _z_orig;

            QString     _path;
            QThread     _runner;
            MainWindow* _w;

        protected:
            Core();
            ~Core();

        public:
            Hcl::Coord cam;
            Hcl::Rotation rotation;

            QMutex mutexParams;
            std::mutex mutexParticles;

            static Core& getInstance();
            QString getPath();

            void clear();
            void error(QString);
            void run();

            // TODO: rewrite it all as soon as possible
            bool  isAutoclean();
            bool  isDrawingSpheres();
            bool  isDrawingTraectories();
            bool  isSmartClean();
            int   getShadow();
            float getPrecision();
            float getZoom();
            int   getSmartClean();
            void  setModparams(int, int, int, int, bool, bool, bool, bool);

        public slots:
            void open(QString);
            void save(QString);
            void quit();

        private slots:
            void runnerFinished();

        signals:
            void stop();
            void start();
    };
}

#define CATCH(fun) \
    catch(Hcl::Exception& e) \
    { \
        Core::getInstance().error(tr("%1(): %2").arg(fun).arg(e.getText())); \
    } \
    catch(std::exception& e) \
    { \
        Core::getInstance().error(tr("%1() cought an std::exception: %2").arg(fun).arg(e.what())); \
    } \
    catch(...) \
    { \
        Core::getInstance().error(tr("%1() cought an unknown exception").arg(fun)); \
    }

#endif // KILO_CORE_HPP_INCLUDED
