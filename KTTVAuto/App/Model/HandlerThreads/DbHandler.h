/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: DbHandler.h
    Create: 06
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QObject>
#include <QThread>

#include "Common.h"
#include "AppModel.h"
#include "UIBridge.h"
#include "ScreenList.h"

class DbHandler : public QObject
{
    Q_OBJECT
public:
    explicit DbHandler(QObject *parent = nullptr);

public slots:
    void eventHandler(QString objectName, int eventId, QString param);
};

class DbHandlerThread : public QThread
{
    Q_OBJECT
public:
    DbHandlerThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() {
        DLOG("Starting...");
        DbHandler handler;
        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)), Qt::QueuedConnection);
        exec();
    }
};

#endif // DBHANDLER_H
