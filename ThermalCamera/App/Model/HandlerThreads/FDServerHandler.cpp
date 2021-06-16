#include "HMIEvents.h"
#include "DataManager.h"
#include "FDServerHandler.h"

FDServerHandler::FDServerHandler(QObject *parent)
    : QObject(parent)
    , m_serverIp(GETDP(DPID::DP_SETTINGS_SERVERIP))
    , m_serverPort(GETDP(DPID::DP_SETTINGS_SERVERPORT).toInt())
{
    DLOG("Create");
    m_tcpSocket = new QTcpSocket(this);
    connect(DataManager::getInstance(), SIGNAL(dataChanged(int,QString)), this, SLOT(updateData(int,QString)));
    connect(Delivery::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), this, SLOT(handleEvent(QString,int,QString)));
}

void FDServerHandler::sendDataToServer()
{
    if(!connectToServer(m_serverIp, m_serverPort)) {
        DLOG("Can't connect to %s:%d", m_serverIp.toStdString().data(), m_serverPort);
        return;
    }

    if (m_tcpSocket->state() == QTcpSocket::ConnectedState) {
        QString data = QString("$[TIME,%1][DEVICEID,%2][TEMP,%3]\r\n")
                    .arg(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"))
                    .arg(GETDP(DPID::DP_SETTINGS_DEVICEID))
                    .arg(GETDP(DPID::DP_THERMAL_TEMPERATURE));

        m_tcpSocket->write(QByteArray::fromStdString(data.toStdString()));
        m_tcpSocket->waitForBytesWritten(500);

        DLOG("Send message to %s - %d: %s", m_serverIp.toStdString().data(), m_serverPort, data.toStdString().data());
    } else {
        DLOG("Can't connect to server: %s - %d", m_serverIp.toStdString().data(), m_serverPort);
    }
}

void FDServerHandler::sendAlarmToFDServer()
{
    if(!connectToServer(m_serverIp, m_serverPort)) {
        DLOG("Can't connect to %s:%d", m_serverIp.toStdString().data(), m_serverPort);
        return;
    }

    if (m_tcpSocket->state() == QTcpSocket::ConnectedState) {
        QString data = QString("#%1#\r\n").arg(GETDP(DPID::DP_SETTINGS_DEVICEID));
        m_tcpSocket->write(QByteArray::fromStdString(data.toStdString()));
        m_tcpSocket->waitForBytesWritten(500);

        DLOG("Send message to %s - %d: %s", m_serverIp.toStdString().data(), m_serverPort, data.toStdString().data());
    } else {
        DLOG("Can't connect to server: %s - %d", m_serverIp.toStdString().data(), m_serverPort);
    }
}

void FDServerHandler::updateData(int dpid, QString value)
{
    switch (dpid) {
    case DPID::DP_SETTINGS_SERVERIP: {
        m_serverIp = value;
        break;
    }
    case DPID::DP_SETTINGS_SERVERPORT: {
        m_serverPort = value.toInt();
        break;
    }
    default:
        break;
    }
}

bool FDServerHandler::connectToServer(QString ip, int port)
{
    if(m_tcpSocket->state() == QTcpSocket::ConnectedState)
        return true;

    if(ip.isEmpty() || port <= 0) {
        DLOG("Server IP or Port not set!");
        return false;
    }

    if (m_tcpSocket->state() != QTcpSocket::ConnectedState) {
        DLOG("Reconnect to host");
        m_tcpSocket->connectToHost(ip, port);
        m_tcpSocket->waitForConnected(500);
    }
    return m_tcpSocket->state() == QTcpSocket::ConnectedState;
}

void FDServerHandler::handleEvent(QString objectName, int eventId, QString params)
{
    switch (eventId) {
    case REQUEST_SEND_FDALARM:
        sendAlarmToFDServer();
        break;
    default:
        break;
    }
}
