#-------------------------------------------------
#
# Project created by QtCreator 2018-04-11T19:54:53
#
#-------------------------------------------------

QT       += core gui testlib xml
CONFIG += с++11

#QMAKE_CXXFLAGS_RELEASE -= -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE -= -O3
#QMAKE_CXXFLAGS_RELEASE *= -Ofast
#QMAKE_CXXFLAGS_RELEASE += -march=native

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RT-Render
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEPENDPATH += . ../RT-Core/
INCLUDEPATH += ../RT-Core/

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    graphicsview.cpp \
    render.cpp \
    xmlsceneparser.cpp \
    rendersettings.cpp \
    defaultscenes.cpp

HEADERS += \
        mainwindow.h \
    graphicsview.h \
    render.h \
    xmlsceneparser.h \
    rendersettings.h \
    defaultscenes.h

FORMS += \
        mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../RT-Core/release/ -lRT-Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../RT-Core/debug/ -lRT-Core
else:unix: LIBS += -L$$OUT_PWD/../RT-Core/ -lRT-Core

INCLUDEPATH += $$PWD/../RT-Core
DEPENDPATH += $$PWD/../RT-Core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RT-Core/release/libRT-Core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RT-Core/debug/libRT-Core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RT-Core/release/RT-Core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RT-Core/debug/RT-Core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../RT-Core/libRT-Core.a
