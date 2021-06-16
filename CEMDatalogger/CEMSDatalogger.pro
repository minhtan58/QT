TEMPLATE = app

QT += qml quick serialport sql
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
    $$PWD/App/Model/CLib \
    $$PWD/App/Model/HandlerThreads

HEADERS += \
    App/common/Common.h \
    App/common/Defines.h \
    App/common/Constants.h \
    App/common/CEMSScreenList.h \
    App/common/QMLConstants.h \
    App/Model/DataManager/CEMSEnum.h \
    App/Model/DataManager/DataManager.h \
    App/View/UIBridge.h \
    App/View/Adapter/ScreenAdapter.h \
    App/View/Adapter/TopBarAdapter.h \
    App/View/Adapter/KeyboardAdapter.h \
    App/Model/CLib/DConI7017RC.h \
    App/CEMSDatalogger.h \
    App/Model/CLib/SettingsLoader.h \
    App/Model/HandlerThreads/TimeSystemHandler.h \
    App/Model/ModelHandler.h \
    App/Model/HandlerThreads/SettingsHandler.h \
    App/Model/HandlerThreads/NetworkMainServerHandler.h \
    App/Model/HandlerThreads/SerialPortHandler.h \
    App/Model/HandlerThreads/CommonHandler.h \
    App/View/QMLModel/HistoryDataListModel.h \
    App/Model/DataManager/DbManager.h \
    App/Model/HandlerThreads/DbHandler.h \
    App/common/commontype.h

SOURCES += \
    App/main.cpp \
    App/common/QMLConstants.cpp \
    App/Model/DataManager/DataManager.cpp \
    App/View/UIBridge.cpp \
    App/View/Adapter/ScreenAdapter.cpp \
    App/View/Adapter/TopBarAdapter.cpp \
    App/View/Adapter/KeyboardAdapter.cpp \
    App/Model/CLib/DConI7017RC.cpp \
    App/CEMSDatalogger.cpp \
    App/Model/CLib/SettingsLoader.cpp \
    App/Model/HandlerThreads/TimeSystemHandler.cpp \
    App/Model/ModelHandler.cpp \
    App/Model/HandlerThreads/SettingsHandler.cpp \
    App/Model/HandlerThreads/NetworkMainServerHandler.cpp \
    App/Model/HandlerThreads/SerialPortHandler.cpp \
    App/Model/HandlerThreads/CommonHandler.cpp \
    App/View/QMLModel/HistoryDataListModel.cpp \
    App/Model/DataManager/DbManager.cpp \
    App/Model/HandlerThreads/DbHandler.cpp

RESOURCES += qml.qrc \
    images.qrc

#---------------------Raspi Config---------------------
target.path = /usr/CEMSDatalogger/bin
INSTALLS += target

