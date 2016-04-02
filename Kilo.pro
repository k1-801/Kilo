QT                                   += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS           += -lGLU -lhcl
CONFIG         += thread
QMAKE_CXXFLAGS += -std=c++14 -Wall

TARGET = Kilo
TEMPLATE = app
VERSION = 0.4.2

TRANSLATIONS += \
    qrc/lang/Kilo_en.ts \
    qrc/lang/Kilo_ru.ts

SOURCES += \
    src/AbstractParticle.cpp \
    src/Core.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/ParticleField.cpp \
    src/ParticleFinal.cpp \
    src/ParticleGroup.cpp \
    src/Particles/Dot.cpp \
    src/Runner.cpp \
    src/Universe.cpp \
    src/Widget3D.cpp \
    src/WidgetAxis.cpp \
    src/WidgetModel.cpp \
    src/DialogParticleList.cpp \
    src/WidgetParticle.cpp \
    src/WidgetParticleList.cpp


HEADERS += \
    include/AbstractParticle.hpp \
    include/MainWindow.hpp \
    include/Core.hpp \
    include/Runner.hpp \
    include/ParticleField.hpp \
    include/ParticleFinal.hpp \
    include/ParticleGroup.hpp \
    include/Particles/Dot.hpp \
    include/Phy.hpp \
    include/Universe.hpp \
    include/Widget3D.hpp \
    include/WidgetAxis.hpp \
    include/WidgetModel.hpp \
    include/DialogParticleList.hpp \
    include/WidgetParticle.hpp \
    include/WidgetParticleList.hpp

FORMS += \
        ui/DialogParticleList.ui \
        ui/MainWindow.ui \
        ui/DialogAddParticle.ui

RESOURCES += \
    qrc/resources.qrc
