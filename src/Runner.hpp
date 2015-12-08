#pragma once

#ifndef RUNNER_HPP_INCLUDED
#define RUNNER_HPP_INCLUDED

namespace Kilo
{
    class Runner;
}

#include <QEventLoop>
#include <QObject>

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
    };
}

#endif // RUNNER_HPP_INCLUDED
