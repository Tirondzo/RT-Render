#-------------------------------------------------
#
# Project created by QtCreator 2018-04-11T19:57:11
#
#-------------------------------------------------

QT       -= core gui

TEMPLATE = lib
CONFIG += staticlib
CONFIG += с++11

#QMAKE_CXXFLAGS_RELEASE -= -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE -= -O3
#QMAKE_CXXFLAGS_RELEASE *= -Ofast
#QMAKE_CXXFLAGS_RELEASE += -march=native

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ray.cpp \
    vector3d.cpp \
    integrator.cpp \
    color.cpp \
    nvector.cpp \
    scene.cpp \
    object.cpp \
    intersection.cpp \
    material.cpp \
    plane.cpp \
    sphere.cpp \
    camera.cpp \
    randomly.cpp

HEADERS += \
        ray.h \
    vector3d.h \
    integrator.h \
    color.h \
    nvector.h \
    scene.h \
    object.h \
    intersection.h \
    material.h \
    plane.h \
    sphere.h \
    camera.h \
    randomly.h
