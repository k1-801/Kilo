#include <QApplication>

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

#include "../include/Core.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kilo::Core::getInstance().run();
    return a.exec();
}
