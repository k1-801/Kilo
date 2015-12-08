QT                                   += core gui opengl xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS           += -lGLU
CONFIG         += thread
QMAKE_CXXFLAGS += -std=c++11

TARGET = Kilo
TEMPLATE = app

TRANSLATIONS += \
    qrc/lang/Kilo_en.ts \
    qrc/lang/Kilo_ru.ts

SOURCES += \
    src/Core.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/ParticleFactory.cpp \
    src/ParticleFinal.cpp \
    src/ParticleGroup.cpp \
    src/Particles/Dot.cpp \
    src/Runner.cpp \
    src/Vector3.cpp \
    src/Universe.cpp \
    src/Widget3D.cpp \
    src/WidgetAxis.cpp \
    src/WidgetModel.cpp \
    src/DialogParticleList.cpp \
    src/WidgetParticle.cpp \
    src/WidgetParticleList.cpp \
    src/ParticleField.cpp \
    src/AbstractParticle.cpp

HEADERS += \
    src/MainWindow.hpp \
    src/Core.hpp \
    src/Runner.hpp \
    src/ParticleFactory.hpp \
    src/ParticleFinal.hpp \
    src/ParticleGroup.hpp \
    src/Particles/Dot.hpp \
    src/Phy.hpp \
    src/Universe.hpp \
    src/Vector3.hpp \
    src/Widget3D.hpp \
    src/WidgetAxis.hpp \
    src/WidgetModel.hpp \
    src/DialogParticleList.hpp \
    src/WidgetParticle.hpp \
    src/WidgetParticleList.hpp \
    src/ParticleField.hpp \
    src/AbstractParticle.hpp

FORMS += \
        ui/DialogParticleList.ui \
        ui/MainWindow.ui

RESOURCES += \
    qrc/resources.qrc
