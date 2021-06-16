/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: SettingsHandler.h
    Create: 07/03/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

#include "Common.h"
#include "AppModel.h"
#include "SettingsLoader.h"
#include "DBManager.h"
#include "UIBridge.h"

#ifdef __WIN32
#define SIM_PORTNAME    ""
#define SENSOR_PORTNAME ""
#endif

class SettingsHandler : public QObject
{
    Q_OBJECT
public:
    explicit SettingsHandler(QObject *parent = nullptr);

public slots:
    void eventHandler(QString objectName, int eventId, QString param);
    void readResponse();
    void checkSerialAutomatic();
    void checkSerialSessionFinished();

private:
    QSerialPort *m_serial = nullptr;
    QStringList m_serialList;
    QTimer *m_checkSession = nullptr;
    QTimer *m_checkScheduce = nullptr;
    bool m_serialConnected = false;

    void loadIniSettings();

    void checkerSerialConfigure();
    QStringList getAvaiableSerialPort(QString pattern);
};


//thread define
class SettingsHandlerThread : public QThread
{
    Q_OBJECT
public:
    SettingsHandlerThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() {
        DLOG("Starting...");
        SettingsHandler handler;
        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        exec();
    }
};

#endif // SETTINGSHANDLER_H
