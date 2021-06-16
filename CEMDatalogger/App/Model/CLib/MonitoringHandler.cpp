/****************************************************************************

    Copyright (C) 2018 by LGE
    File: MonitoringHandler.cpp
    Create: 15
    Author: Vuong Nguyen

 ****************************************************************************/

#include "MonitoringHandler.h"

MonitoringHandler::MonitoringHandler(QObject *parent) : QObject(parent)
{
    m_connect = new QTimer(this);
    connect(m_connect, SIGNAL(timeout()), this, SLOT(reConnectMonitoringServer()));
    m_monitoringRes = new QTcpSocket(this);
    connect(m_monitoringRes, SIGNAL(connected()), this, SLOT(connectedServer()));
    connect(m_monitoringRes, SIGNAL(disconnected()), this, SLOT(disconnectedServer()));
    connect(m_monitoringRes, SIGNAL(readyRead()), this, SLOT(monitoringMessageHandler()));
}

void MonitoringHandler::start()
{
    m_connect->start(3000);
    DLOG_THREAD << "start timer";
    m_monitoringRes->connectToHost(QHostAddress::LocalHost, LISTEN_PORT);
}

void MonitoringHandler::reConnectMonitoringServer()
{
    DLOG_THREAD << "reConnectMonitoringServer";
    if(m_monitoringRes->state() != QTcpSocket::ConnectedState) {
        m_monitoringRes->connectToHost(QHostAddress::LocalHost, LISTEN_PORT);
    }
}

void MonitoringHandler::connectedServer()
{
    if(m_connect->isActive()) {
        m_connect->stop();
        DLOG_THREAD << "pause timer";
    }
}

void MonitoringHandler::disconnectedServer()
{
    if(!m_connect->isActive()) {
        m_connect->start(10000);
        DLOG_THREAD << "restart timer";
    }
}

void MonitoringHandler::monitoringMessageHandler()
{
    QTcpSocket *pSocket = qobject_cast<QTcpSocket*>(QObject::sender());
    QString request = pSocket->readAll();
    DLOG_THREAD << "MonitoringHandler rev: " << request;

    m_msgContent = request.mid(4, 5);

    pSocket->write(QString("$CEMS,%1\r\n").arg(m_msgContent).toStdString().c_str());
}
