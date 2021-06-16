/****************************************************************************

    Copyright (C) 2018 by LGE
    File: MonitoringHandler.h
    Create: 15
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef MONITORINGHANDLER_H
#define MONITORINGHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>
#include <QTimer>
#include <QTcpServer>

#include "Common.h"

#define LISTEN_PORT     60001

class MonitoringHandler : public QObject
{
    Q_OBJECT
public:
    explicit MonitoringHandler(QObject *parent = nullptr);
    void start();

signals:

public slots:
    void reConnectMonitoringServer();
    void connectedServer();
    void disconnectedServer();
    void monitoringMessageHandler();

private:
    QString m_msgContent;
    QTimer *m_connect = nullptr;
    QTcpSocket *m_monitoringRes;
};

class MonitoringHandlerThread : public QThread
{
    Q_OBJECT
public:
    MonitoringHandlerThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() {
        DLOG_THREAD << "Start";
        MonitoringHandler handler;
        handler.start();
        exec();
    }
};

#endif // MONITORINGHANDLER_H
