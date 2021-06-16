/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: NetworkMainServerHandler.h
    Create: 12/03/2018
    Author: Minh Tan

 ****************************************************************************/

#ifndef NETWORKMAINSERVERHANDLER_H
#define NETWORKMAINSERVERHANDLER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include <QDateTime>
#include <QProcess>

#include "Common.h"
#include "DataManager.h"
#include "CEMSEnum.h"

class NetworkMainServerHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkMainServerHandler(QObject *parent = 0);
    ~NetworkMainServerHandler();

public slots:
    void eventHandler(QString objectName, int eventId, QString param);
    void sendDataToServer();
    void updateConnectionState();

private:
    QTcpSocket *m_tcpSocket = nullptr;
    QTimer *m_updateStatus = nullptr;

    void updateTime();
    void testConnection(QString serverIP, int serverPort);
};

//thread define
class NetworkMainServerHandlerThread : public QThread
{
    Q_OBJECT
public:
    NetworkMainServerHandlerThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() {
        DLOG("Start");
        NetworkMainServerHandler handler;
        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        exec();
    }
};

#endif // NETWORKMAINSERVERHANDLER_H
