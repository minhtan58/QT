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
#include "DataManager.h"

class TimeSystemHandler : public QObject
{
    Q_OBJECT
public:
    explicit TimeSystemHandler(QObject *parent = nullptr);

public slots:
    void updateSystemTime();
    void eventHandler(QString objectName, int eventId, QString param);
    void updateAppData(int dpid);

private:
    QProcess *m_process = nullptr;
};

class TimeSystemHandlerThread : public QThread
{
    Q_OBJECT
public:
    explicit TimeSystemHandlerThread(QObject *parent = nullptr) : QThread(parent){}

protected:
    void run() {
        DLOG("Start");
        QTimer updateSystemTime;
        TimeSystemHandler handler;
        connect(&updateSystemTime, SIGNAL(timeout()), &handler, SLOT(updateSystemTime()));
        connect(Delivery::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        connect(DataManager::getInstance(), SIGNAL(dataChanged(int)), &handler, SLOT(updateAppData(int)));
        updateSystemTime.start(1000);
        exec();
    }
};

#endif // TIMESYSTEMHANDLER_H
