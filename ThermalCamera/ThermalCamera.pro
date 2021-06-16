QT += quick network
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    $$PWD/App/common \
    $$PWD/App/model \
    $$PWD/App/model/core \
    $$PWD/App/model/DataManager \
    $$PWD/App/model/HandlerThreads \
    $$PWD/App/model/WebServer \
    $$PWD/App/view \
    $$PWD/App/view/Adapter \
    $$PWD/App/view/QmlItem \
    $$PWD/Lib/ThermalCameraSDK/sdk \
    $$PWD/Lib/ThermalCameraSDK/leptonSDKEmb32PUB \
    $$PWD/Lib/wiringPi

HEADERS += \
    App/Window.h \
    App/common/Common.h \
    App/common/Defines.h \
    App/common/HMIEvents.h \
    App/view/QmlItem/QMLConstants.h \
    App/view/QmlItem/QQuickImage.h \
    App/view/adapter/ScreenAdapter.h \
    App/view/Delivery.h \
    App/model/ModelHandler.h \
    App/model/DataManager/DataManager.h \
    App/model/DataManager/DPID.h \
    App/model/DataManager/SettingsLoader.h \
    App/model/WebServer/MainPageHandler.h \
    App/model/WebServer/SettingPageHandler.h \
    App/model/WebServer/RequestMapper.h \
    App/model/WebServer/WebServer.h \
    App/model/HandlerThreads/FDServerHandler.h \
    App/model/HandlerThreads/TemperatureAlarmHandler.h

SOURCES += App/main.cpp \
    App/Window.cpp \
    App/model/DataManager/DataManager.cpp \
    App/view/QmlItem/QMLConstants.cpp \
    App/view/QmlItem/QQuickImage.cpp \
    App/view/Adapter/ScreenAdapter.cpp \
    App/view/Delivery.cpp \
    App/model/ModelHandler.cpp \
    App/model/WebServer/MainPageHandler.cpp \
    App/model/WebServer/SettingPageHandler.cpp \
    App/model/WebServer/RequestMapper.cpp \
    App/model/WebServer/WebServer.cpp \
    App/model/DataManager/SettingsLoader.cpp \
    App/model/HandlerThreads/FDServerHandler.cpp \
    App/model/HandlerThreads/TemperatureAlarmHandler.cpp

RESOURCES += \
    qml.qrc \
    images.qrc \
    web.qrc

include($$PWD/Lib/QtWebApp/httpserver/httpserver.pri)

#Linux OS
unix:!macx {
    include($$PWD/Lib/ThermalCameraSDK/LeptonSDK.pri)
    include($$PWD/Lib/wiringPi/wiringpi.pri)
    HEADERS += App/model/HandlerThreads/ThermalCameraHandler.h \
        App/model/HandlerThreads/GPIOHandler.h \
        App/model/HandlerThreads/MonitoringHandler.h

    SOURCES += App/model/HandlerThreads/ThermalCameraHandler.cpp \
        App/Model/HandlerThreads/GPIOHandler.cpp \
        App/model/HandlerThreads/MonitoringHandler.cpp
}

#Window OS
win32 {
}

#---------------------Raspi Config---------------------
target.path = /usr/ThermalCamera
INSTALLS += target
