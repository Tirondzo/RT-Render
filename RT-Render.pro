TEMPLATE = subdirs
SUBDIRS += RT-Core RT-Render
CONFIG += ordered
CONFIG += с++11

#QMAKE_CXXFLAGS_RELEASE -= -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE -= -O3
#QMAKE_CXXFLAGS_RELEASE *= -Ofast
#QMAKE_CXXFLAGS_RELEASE += -march=native

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/RT-Core/release/ -lRT-Core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/RT-Core/debug/ -lRT-Core
else:unix: LIBS += -L$$OUT_PWD/RT-Core/ -lRT-Core

INCLUDEPATH += $$PWD/RT-Core
DEPENDPATH += $$PWD/RT-Core

INCLUDEPATH += $$PWD/Dependencies/eigen-eigen-5a0156e40feb/
DEPENDPATH += $$PWD/Dependencies/eigen-eigen-5a0156e40feb/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/RT-Core/release/libRT-Core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/RT-Core/debug/libRT-Core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/RT-Core/release/RT-Core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/RT-Core/debug/RT-Core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/RT-Core/libRT-Core.a
