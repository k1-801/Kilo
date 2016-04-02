#pragma once

#ifndef RUNNER_HPP_INCLUDED
#define RUNNER_HPP_INCLUDED

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QEventLoop>
#include <QObject>

namespace Kilo
{
    class Runner;
}

namespace Kilo
{
    class Runner : public QObject
    {
        Q_OBJECT

        private:
            bool _b;
            bool _h;

        protected:
            Runner();
            ~Runner();

        public:
            static Runner& getInstance();
            bool isSimRunning();

        public slots:
            void start();
            void stop();

            void simRun();
            void simStop();

        signals:
            void stateChanged(bool);
            void finished();
            void error(QString);
    };
}

#endif // RUNNER_HPP_INCLUDED
