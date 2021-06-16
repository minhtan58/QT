/****************************************************************************

    Copyright (C) 2018 by LGE
    File: DbHandler.h
    Create: 14
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QObject>
#include <QTimer>
#include "DbManager.h"
#include <QProcess>

class DbHandler : public QObject
{
    Q_OBJECT
public:
    explicit DbHandler(QObject *parent = nullptr);

public slots:
    void eventHandler(QString objectName, int eventId, QString param);
    void updateAppData(int dpid);
    void checkSendServerData();

private:
    QTimer *m_timerSendDataToServer = nullptr;
    QProcess *m_process = nullptr;

    void saveToHistoryDb(QStringList dataRow);
    void saveToMissingDb(QStringList dataRow);

    void updateTime();
    void start();
    void exportDataFile();
};

class DbHandlerThread : public QThread
{
    Q_OBJECT
public:
    DbHandlerThread(QObject *parent = nullptr)
        : QThread(parent)
    {}

protected:
    void run() {
        DLOG("Start");
        DbHandler handler;
        connect(Delivery::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        connect(DataManager::getInstance(), SIGNAL(dataChanged(int)), &handler, SLOT(updateAppData(int)));
        exec();
    }
};

#endif // DBHANDLER_H
