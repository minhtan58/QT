/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: NetworkMainServerHandler.cpp
    Create: 12/03/2018
    Author: Minh Tan

 ****************************************************************************/

#include "NetworkMainServerHandler.h"

NetworkMainServerHandler::NetworkMainServerHandler(QObject *parent) : QObject(parent)
{
    m_tcpSocket = new QTcpSocket(this);
    m_updateStatus = new QTimer(this);

    connect(m_updateStatus, SIGNAL(timeout()), this, SLOT(updateConnectionState()), Qt::UniqueConnection);
    m_updateStatus->start(TIM_UPDATE_STATUS);
}

NetworkMainServerHandler::~NetworkMainServerHandler()
{
    if (m_tcpSocket && m_tcpSocket->state() == QTcpSocket::ConnectedState) {
        m_tcpSocket->disconnectFromHost();
        m_tcpSocket->waitForDisconnected();
    }
}

void NetworkMainServerHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case CEMSEnum::HMI_BUTTON_TEST_CONNECTIONS_NETWORK_SERVER: {
        QStringList paramList = getListParam(param);
        SENDEVENT("" , CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Connecting...");
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_TEST_CONNECTION, QString::number(int(TC_TESTING)));
        testConnection(paramList.at(0), paramList.at(1).toInt());
        break;
    }
    case CEMSEnum::DB_REQUEST_SENDDATA_TO_SERVER: {
        sendDataToServer();
        break;
    }
    default:
        break;
    }
}

void NetworkMainServerHandler::sendDataToServer()
{
    try {
        QString serverIP = GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP);
        int serverPort = GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT).toInt();
        if(serverIP.isEmpty() || serverPort == 0) {
            DLOG("Server IP or Port not set!");
            return;
        }

        if (m_tcpSocket->state() != QTcpSocket::ConnectedState) {
            DLOG("Reconnect to host");
            m_tcpSocket->connectToHost(serverIP, serverPort);
            m_tcpSocket->waitForConnected(500);
        }

        if (m_tcpSocket->state() == QTcpSocket::ConnectedState) {
            QStringList dataRow = DataManager::getInstance()->getWorkingDataRow();
            QString data = QString("$[DEVICE,CEMS][TIME,%1][O2,%2][CO,%3][NO,%4][NOX,%5][SO2,%6][TEMP,%7][OPP,%8][DUSTPM,%9][VEL,%10][FLOW,%11]\r\n")
                        .arg(QDateTime::fromString(dataRow.at(0), "yyyy-MM-dd HH:mm:ss").toString("yyyyMMddHHmmss"))
                        .arg(dataRow.at(1))
                        .arg(dataRow.at(2))
                        .arg(dataRow.at(3))
                        .arg(dataRow.at(4))
                        .arg(dataRow.at(5))
                        .arg(dataRow.at(6))
                        .arg(dataRow.at(7))
                        .arg(dataRow.at(8))
                        .arg(dataRow.at(9))
                        .arg(dataRow.at(10));
            m_tcpSocket->write(QByteArray::fromStdString(data.toStdString()));
            m_tcpSocket->waitForBytesWritten(500);

            QList<CemsDataRow> missingList = DataManager::getInstance()->getMissingDataList();
            for (int i = 0; i < missingList.size(); ++i) {
                if (m_tcpSocket->state() == QTcpSocket::ConnectedState) {       //long time may be disconnect
                    QString missingMessage =
                            QString("$[DEVICE,CEMS][TIME,%1][O2,%2][CO,%3][NO,%4][NOX,%5][SO2,%6][TEMP,%7][OPP,%8][DUSTPM,%9][VEL,%10][FLOW,%11]\r\n")
                            .arg(QDateTime::fromString(missingList.at(i).time, "yyyy-MM-dd HH:mm:ss").toString("yyyyMMddHHmmss"))
                            .arg(missingList.at(i).valO2)
                            .arg(missingList.at(i).valCO)
                            .arg(missingList.at(i).valNO)
                            .arg(missingList.at(i).valNOX)
                            .arg(missingList.at(i).valSO2)
                            .arg(missingList.at(i).valTEMP)
                            .arg(missingList.at(i).valOPP)
                            .arg(missingList.at(i).valDUSTPM)
                            .arg(missingList.at(i).valVEL)
                            .arg(missingList.at(i).valFLOW);
                    m_tcpSocket->write(QByteArray::fromStdString(missingMessage.toStdString()));
                    m_tcpSocket->waitForBytesWritten(500);
                    SENDEVENT("", CEMSEnum::DB_REQUEST_REMOVE_MISSING_DATA_ROW, missingList.at(i).time);
                }
            }
            //m_tcpSocket->disconnectFromHost();
            DLOG("Send message to %s - %d: %s", serverIP.toStdString().data(), serverPort, data.toStdString().data());
            SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_STATUS, "1");
        } else {
            DLOG("Can't connect to server: %s - %d", serverIP.toStdString().data(), serverPort);
            SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_STATUS, "0");
            SENDEVENT("", CEMSEnum::DB_REQUEST_ADD_MISSING_DATA_ROW, "");
        }
    } catch (std::exception ex) {
        DLOG("ERROR: sendDataToServer: %s", ex.what());
    }
}

void NetworkMainServerHandler::testConnection(QString serverIP, int serverPort)
{
    QString currentServerIP = GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP);
    int currentServerPort = GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT).toInt();
    if (currentServerIP == serverIP && currentServerPort == serverPort) {
        if(m_tcpSocket && m_tcpSocket->state() == QTcpSocket::ConnectedState) {
            SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_TEST_CONNECTION, QString::number(int(TC_TEST_RESULT_OK)));
        } else {
            SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_TEST_CONNECTION, QString::number(int(TC_TEST_RESULT_FAIL)));
        }
    } else {
        try {
            DLOG("Test connection to new host");
            QTcpSocket testSocket;
            testSocket.connectToHost(serverIP, serverPort);
            testSocket.waitForConnected(1000);

            if (testSocket.state() == QTcpSocket::ConnectedState) {
                SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_TEST_CONNECTION, QString::number(int(TC_TEST_RESULT_OK)));
                testSocket.disconnectFromHost();
                if (testSocket.state() != QAbstractSocket::UnconnectedState) {
                    testSocket.waitForDisconnected(1000);
                }
            } else {
                SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_TEST_CONNECTION, QString::number(int(TC_TEST_RESULT_FAIL)));
            }
        } catch (std::exception ex) {
            Q_UNUSED(ex)
            SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_TEST_CONNECTION, QString::number(int(TC_TEST_RESULT_FAIL)));
        }
    }
}

void NetworkMainServerHandler::updateConnectionState()
{
    if(m_tcpSocket->state() == QTcpSocket::ConnectedState) {
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_STATUS, "1");
    } else {
        m_tcpSocket->connectToHost(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP), GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT).toInt());
        m_tcpSocket->waitForConnected(1000);
        if(m_tcpSocket->state() == QTcpSocket::ConnectedState) {
            SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_STATUS, "1");
            //m_tcpSocket->disconnectFromHost();
        } else {
            SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_STATUS, "0");
        }

    }
}
