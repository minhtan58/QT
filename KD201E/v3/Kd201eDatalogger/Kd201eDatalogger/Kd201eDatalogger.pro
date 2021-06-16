#----------------------------------------------------
#---------------- KD201E Datalogger -----------------
#---------------- Create:           -----------------
#---------------- Version: 3.0      -----------------
#----------------------------------------------------

QT  += core network sql
QT  -= gui

CONFIG += c++11

TARGET = Kd201eDatalogger

TEMPLATE = app

INCLUDEPATH += \
    $$PWD/../QtWebApp/httpserver \
    $$PWD/../Kd201eDatalogger/App \
    $$PWD/../Kd201eDatalogger/App/constant \
    $$PWD/../Kd201eDatalogger/App/model \
    $$PWD/../Kd201eDatalogger/App/model/datamanager \
    $$PWD/../Kd201eDatalogger/App/model/core \
    $$PWD/../Kd201eDatalogger/App/webserver \
    $$PWD/../PocoLib

SOURCES += \
    App/main.cpp \
    App/model/core/KD201E.cpp \
    App/model/datamanager/Datapool.cpp \
    App/model/datamanager/DBManager.cpp \
    App/webserver/RequestMapper.cpp \
    App/webserver/MainPageHandler.cpp \
    App/webserver/SettingPageHandler.cpp \
    App/webserver/WebServer.cpp \
    App/model/ModelHandler.cpp \
    App/webserver/DataViewPageHandler.cpp \
    App/model/datamanager/SettingsLoader.cpp

HEADERS += \
    App/constant/common.h \
    App/constant/KD201EEnum.h \
    App/model/core/KD201E.h \
    App/model/datamanager/Datapool.h \
    App/model/datamanager/DBManager.h \
    App/webserver/RequestMapper.h \
    App/webserver/MainPageHandler.h \
    App/webserver/SettingPageHandler.h \
    App/webserver/WebServer.h \
    App/model/ModelHandler.h \
    App/webserver/DataViewPageHandler.h \
    App/model/datamanager/SettingsLoader.h

include(../QtWebApp/httpserver/httpserver.pri)

RESOURCES += ini.qrc

#---------------------Raspi Config---------------------
target.path = /usr/KD201E
INSTALLS += target

INCLUDEPATH += $$PWD/../Poco/include
DEPENDPATH += $$PWD/../Poco/include

unix:!macx: LIBS += -L$$PWD/../Poco/lib/ -lPocoNet
unix:!macx: PRE_TARGETDEPS += $$PWD/../Poco/lib/libPocoNet.a
unix:!macx: LIBS += -L$$PWD/../Poco/lib/ -lPocoEncodings
unix:!macx: PRE_TARGETDEPS += $$PWD/../Poco/lib/libPocoEncodings.a
unix:!macx: LIBS += -L$$PWD/../Poco/lib/ -lPocoFoundation
unix:!macx: PRE_TARGETDEPS += $$PWD/../Poco/lib/libPocoFoundation.a
unix:!macx: LIBS += -L$$PWD/../Poco/lib/ -lPocoJSON
unix:!macx: PRE_TARGETDEPS += $$PWD/../Poco/lib/libPocoJSON.a
unix:!macx: LIBS += -L$$PWD/../Poco/lib/ -lPocoUtil
unix:!macx: PRE_TARGETDEPS += $$PWD/../Poco/lib/libPocoUtil.a
unix:!macx: LIBS += -L$$PWD/../Poco/lib/ -lPocoXML
unix:!macx: PRE_TARGETDEPS += $$PWD/../Poco/lib/libPocoXML.a
