#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T14:24:01
#
#-------------------------------------------------

QT       += core gui\
            opengl

TARGET = Geyser
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../GLCommon/

SOURCES += \
    main.cpp\
    Vector3f.cpp \
    RandomHelper.cpp \
    GeyserWindow.cpp \
    ParticleEngineView.cpp \
    ParticleEngine.cpp \
    Particle.cpp

HEADERS  += \
    Vector3f.h \
    RandomHelper.h \
    GeyserWindow.h \
    Particle.h \
    ParticleEngine.h \
    ParticleEngineView.h



FORMS    += \
    GeyserWindow.ui
