QT += core network
QT -= gui

CONFIG += c++11

TARGET = CEMSMonitoring
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    CEMSMonitoring.cpp

HEADERS += \
    CEMSMonitoring.h

#DEFINES += QT_NO_DEBUG_OUTPUT

#---------------------Raspi Config---------------------
target.path = /usr/CEMSDatalogger/bin
INSTALLS += target
