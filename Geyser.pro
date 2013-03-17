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
    geyserView.cpp \
    particle.cpp \
    particleengine.cpp \
    Vector3f.cpp \
    RandomHelper.cpp \
    GeyserWindow.cpp

HEADERS  += \
    particle.h \
    particleengine.h \
    Vector3f.h \
    RandomHelper.h \
    geyserView.h \
    GeyserWindow.h



FORMS    += mainwindow.ui
