INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

HEADERS += \
    $$PWD/cameracontrol.h \
    $$PWD/graphics.h \
    $$PWD/camera.h \
    $$PWD/mmalincludes.h

SOURCES += \
    $$PWD/graphics.cpp \
#    $$PWD/picam.cpp \
    $$PWD/camera.cpp \
    $$PWD/cameracontrol.cpp
