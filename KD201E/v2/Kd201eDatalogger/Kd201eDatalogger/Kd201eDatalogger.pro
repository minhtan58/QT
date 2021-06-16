#----------------------------------------------------
#---------------- KD201E Datalogger -----------------
#---------------- Create:           -----------------
#---------------- Version: 2.0      -----------------
#----------------------------------------------------

QT  += core network
QT  -= gui

CONFIG += c++11

TARGET = Kd201eDatalogger

TEMPLATE = app

INCLUDEPATH += \
    $$PWD/../QtWebApp/httpserver/ \
    $$PWD/../Kd201eDatalogger/hdr/constant \
    $$PWD/../Kd201eDatalogger/hdr

SOURCES += \
    src/main.cpp \
    src/requestmapper.cpp \
    src/mainpagecontroller.cpp \
    src/settingpage.cpp \
    src/KD201E.cpp \
    src/mobileviewer.cpp

HEADERS += \
    hdr/requestmapper.h \
    hdr/mainpagecontroller.h \
    hdr/settingpage.h \
    hdr/constant/common.h \
    hdr/constant/pivariables.h \
    hdr/KD201E.h \
    hdr/mobileviewer.h

OTHER_FILES +=

include(../QtWebApp/httpserver/httpserver.pri)

RESOURCES += \
    ini.qrc

#---------------------Raspi Config---------------------
target.path = /usr/KD201E/bin
INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../../../../../../All/Embedded/SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/opt/appinf/lib/ -lPocoNet -lPocoFoundation

INCLUDEPATH += $$PWD/../../../../../../All/Embedded/SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/opt/appinf/include
DEPENDPATH += $$PWD/../../../../../../All/Embedded/SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/opt/appinf/include
