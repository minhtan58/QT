/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: TimeSystemHandler.h
    Create: 06/03/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef TIMESYSTEMHANDLER_H
#define TIMESYSTEMHANDLER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QProcess>

#include "Common.h"
#include "AppModel.h"
#include "UIBridge.h"
#include "SettingsLoader.h"

class TimeSystemHandler : public QObject
{
    Q_OBJECT
public:
    explicit TimeSystemHandler(QObject *parent = nullptr);

public slots:
    void updateSystemTime();
    void eventHandler(QString objectName, int eventId, QString param);
};

class TimeSystemHandlerThread : public QThread
{
    Q_OBJECT
public:
    explicit TimeSystemHandlerThread(QObject *parent = nullptr) : QThread(parent){}

protected:
    void run() {
        DLOG("Starting...");
        QTimer updateSystemTime;
        TimeSystemHandler handler;
        connect(&updateSystemTime, SIGNAL(timeout()), &handler, SLOT(updateSystemTime()));
        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        updateSystemTime.start(1000);
        exec();
    }

#ifdef  __linux__
void sltSetSystemTime();
#endif

};

#endif // TIMESYSTEMHANDLER_H
