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

#include "Common.h"
#include "DataManager.h"
#include "SettingsLoader.h"

class SettingsHandler : public QObject
{
    Q_OBJECT
public:
    explicit SettingsHandler(QObject *parent = nullptr);

public slots:
    void eventHandler(QString objectName, int eventId, QString param);

private:
    void loadIniSettings();
};


//thread define
class SettingsHandlerThread : public QThread
{
    Q_OBJECT
public:
    SettingsHandlerThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() {
        DLOG("Start");
        SettingsHandler handler;
        connect(Delivery::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        exec();
    }
};

#endif // SETTINGSHANDLER_H
