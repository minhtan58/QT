TEMPLATE = app

QT += qml quick serialport sql
CONFIG += c++11 qtquickcompiler

QMAKE_CXXFLAGS += -Wno-deprecated

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += \
    $$PWD/App/Common \
    $$PWD/App/View \
    $$PWD/App/View/Adapter \
    $$PWD/App/View/QMLModel \
    $$PWD/App/Model \
    $$PWD/App/Model/DataManager \
    $$PWD/App/Model/HandlerThreads \
    $$PWD/App/Model/HandlerThreads/Core

HEADERS += \
    App/Window.h \
    App/Common/Common.h \
    App/Common/HMIEvents.h \
    App/Common/Defines.h \
    App/Common/Constants.h \
    App/Common/ScreenList.h \
    App/Model/ModelHandler.h \
    App/Model/DataManager/AppModel.h \
    App/Model/DataManager/SettingsLoader.h \
    App/Model/DataManager/DBManager.h \
    App/Model/HandlerThreads/TimeSystemHandler.h \
    App/Model/HandlerThreads/SettingsHandler.h \
    App/Model/HandlerThreads/GPSHandler.h \
    App/Model/HandlerThreads/CommonHandler.h \
    App/Model/HandlerThreads/DbHandler.h \
    App/View/UIBridge.h \
    App/View/Adapter/KeyboardAdapter.h \
    App/Model/DataManager/FontManager.h \
    App/View/QMLModel/LoginHistoryListModel.h \
    App/View/Adapter/ScreenAdapter.h \
    App/Model/HandlerThreads/DataTransferHandler.h \
    App/Model/HandlerThreads/Core/SIM800C.h \
    App/View/QMLModel/AccountListModel.h \
    App/Model/HandlerThreads/SensorHandler.h \
    App/View/QMLModel/DataviewListModel.h

SOURCES += \
    App/main.cpp \
    App/Window.cpp \
    App/Model/ModelHandler.cpp \
    App/Model/DataManager/AppModel.cpp \
    App/Model/DataManager/SettingsLoader.cpp \
    App/Model/DataManager/DBManager.cpp \
    App/Model/HandlerThreads/TimeSystemHandler.cpp \
    App/Model/HandlerThreads/SettingsHandler.cpp \
    App/Model/HandlerThreads/GPSHandler.cpp \
    App/Model/HandlerThreads/CommonHandler.cpp \
    App/Model/HandlerThreads/DbHandler.cpp \
    App/View/UIBridge.cpp \
    App/View/Adapter/KeyboardAdapter.cpp \
    App/View/QMLModel/LoginHistoryListModel.cpp \
    App/View/Adapter/ScreenAdapter.cpp \
    App/Model/HandlerThreads/DataTransferHandler.cpp \
    App/Model/HandlerThreads/Core/SIM800C.cpp \
    App/View/QMLModel/AccountListModel.cpp \
    App/Model/HandlerThreads/SensorHandler.cpp \
    App/View/QMLModel/DataviewListModel.cpp

RESOURCES += qml.qrc \
    images.qrc \
    js.qrc \
    fonts.qrc

!win32: {
    include(Lib/wiringPi/wiringpi.pri)
}

#---------------------Raspi Config---------------------
target.path = /usr/KTTVAuto/bin
INSTALLS += target

#unix:!macx: LIBS += -L$$PWD/../../All/Embedded/SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/lib/ -lwiringPi

#INCLUDEPATH += $$PWD/../../All/Embedded/SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/include
#DEPENDPATH += $$PWD/../../All/Embedded/SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/include
