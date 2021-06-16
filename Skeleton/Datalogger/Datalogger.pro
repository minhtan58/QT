TEMPLATE = app

QT += qml quick sql
CONFIG += c++11

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += \
    $$PWD/App/common \
    $$PWD/App/View \
    $$PWD/App/View/Adapter \
    $$PWD/App/Model \
    $$PWD/App/Model/DataManager \
    $$PWD/App/Model/core \
    $$PWD/App/Model/HandlerThreads

HEADERS += \
    App/common/Common.h \
    App/common/Defines.h \
    App/common/Constants.h \
    App/common/ScreenList.h \
    App/common/QMLConstants.h \
    App/Model/DataManager/CEMSEnum.h \
    App/Model/DataManager/DataManager.h \
    App/View/Delivery.h \
    App/View/Adapter/ScreenAdapter.h \
    App/View/Adapter/TopBarAdapter.h \
    App/View/Adapter/KeyboardAdapter.h \
    App/Datalogger.h \
    App/Model/core/SettingsLoader.h \
    App/Model/HandlerThreads/TimeSystemHandler.h \
    App/Model/ModelHandler.h \
    App/Model/HandlerThreads/SettingsHandler.h \
    App/Model/HandlerThreads/NetworkMainServerHandler.h \
    App/View/QMLModel/HistoryDataListModel.h \
    App/Model/DataManager/DbManager.h \
    App/Model/HandlerThreads/DbHandler.h \
    App/common/commontype.h

SOURCES += \
    App/main.cpp \
    App/common/QMLConstants.cpp \
    App/Model/DataManager/DataManager.cpp \
    App/View/Delivery.cpp \
    App/View/Adapter/ScreenAdapter.cpp \
    App/View/Adapter/TopBarAdapter.cpp \
    App/View/Adapter/KeyboardAdapter.cpp \
    App/Datalogger.cpp \
    App/Model/core/SettingsLoader.cpp \
    App/Model/HandlerThreads/TimeSystemHandler.cpp \
    App/Model/ModelHandler.cpp \
    App/Model/HandlerThreads/SettingsHandler.cpp \
    App/Model/HandlerThreads/NetworkMainServerHandler.cpp \
    App/View/QMLModel/HistoryDataListModel.cpp \
    App/Model/DataManager/DbManager.cpp \
    App/Model/HandlerThreads/DbHandler.cpp

RESOURCES += qml.qrc \
    images.qrc

#---------------------Raspi Config---------------------
target.path = /usr/Datalogger/bin
INSTALLS += target

