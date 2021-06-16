#----------------------------------------------------
#---------------- KD201E Datalogger -----------------
#---------------- Create:           -----------------
#---------------- Version: 1.0      -----------------
#----------------------------------------------------

QT  += core network
QT  -= gui

CONFIG += c++11

TARGET = KD201ESimulator

TEMPLATE = app

INCLUDEPATH += \
    $$PWD/../QtWebApp/httpserver/ \
    $$PWD/../KD201ESimulator/hdr

SOURCES += \
    src/main.cpp \
    src/requestmapper.cpp \
    src/mainpagecontroller.cpp

HEADERS += \
    hdr/common.h \
    hdr/requestmapper.h \
    hdr/mainpagecontroller.h

OTHER_FILES +=

include(../QtWebApp/httpserver/httpserver.pri)

RESOURCES += ini.qrc
