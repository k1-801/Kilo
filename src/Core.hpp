#pragma once

#ifndef KILO_CORE_HPP_INCLUDED
#define KILO_CORE_HPP_INCLUDED

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
#include "Vector3.hpp"

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
            Coord cam;
            Angle angle;

            QMutex mutexParams;
            QMutex mutexParticles;

            static Core& getInstance();
            QString getPath();

            void clear();
            void error(QString);
            void run();

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
    };
}

#endif // KILO_CORE_HPP_INCLUDED
