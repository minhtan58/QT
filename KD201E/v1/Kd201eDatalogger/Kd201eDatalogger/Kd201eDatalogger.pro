#----------------------------------------------------
#---------------- KD201E Datalogger -----------------
#---------------- Create:           -----------------
#---------------- Version: 1.0      -----------------
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
    src/Datapool.cpp

HEADERS += \
    hdr/requestmapper.h \
    hdr/mainpagecontroller.h \
    hdr/settingpage.h \
    hdr/constant/common.h \
    hdr/KD201E.h \
    hdr/Datapool.h \
    hdr/constant/Kd201eEnum.h

OTHER_FILES +=

include(../QtWebApp/httpserver/httpserver.pri)

RESOURCES += ini.qrc

#---------------------Raspi Config---------------------
target.path = /usr/KD201E/bin
INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../../../../../../All/Embedded/SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/lib/ -lPocoNet -lPocoFoundation

INCLUDEPATH += $$PWD/../../../../../../All/Embedded/SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/include
DEPENDPATH += $$PWD/../../../../../../All/Embedded/SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/include
