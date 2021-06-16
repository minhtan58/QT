/****************************************************************************

    Copyright (C) 2018 by LGE
    File: CEMSMonitoring.cpp
    Create: 15
    Author: Vuong Nguyen

 ****************************************************************************/

#include "CEMSMonitoring.h"

#define LISTEN_PORT     60001
#define CHECK_INTERVAL  15000

//#if __WIN32
#define CMD_RUNLOGGER               "C:/Users/ducvuongcity/Desktop/CEMS/CEMSDatalogger/release/CEMSDatalogger.exe"
#define CMD_CHECKLOGGER_RUNNING     QString("tasklist | FIND \"CEMSDatalogger\"")
#define CMD_CHECK_RESULT_CONTAIN    "CEMSDatalogger"
//#elif __linux__
//#define CMD_RUNLOGGER   "sudo /usr/CEMSDatalogger/bin/CEMSDatalogger"
//#define CMD_CHECKLOGGER_RUNNING QString("ps aux|grep \"%1\"").arg(CMD_RUNLOGGER)
//#define CMD_CHECK_RESULT_CONTAIN    CMD_RUNLOGGER
//#endif

CEMSMonitoring::CEMSMonitoring(QObject *parent)
    : QObject(parent)
{
    qDebug() << "Create CEMSMonitoring";
    m_server = new QTcpServer(this);
    m_server->setMaxPendingConnections(1);
    m_checkLogger = new QTimer(this);
    m_cmd = new QProcess(this);
    m_connectionCount = 0;
    connect(m_checkLogger, SIGNAL(timeout()), this, SLOT(loggerCheckLive()));
    m_checkLogger->start(CHECK_INTERVAL);
//    loggerCheckLive();
}

CEMSMonitoring::~CEMSMonitoring()
{
    if (m_server && m_server->isListening()) {
        m_server->close();
    }
}

void CEMSMonitoring::connectionHandler()
{
    m_logger = m_server->nextPendingConnection();
    QObject::connect(m_logger, SIGNAL(disconnected()), m_logger, SLOT(deleteLater()));
    QObject::connect(m_logger, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    QObject::connect(m_logger, SIGNAL(readyRead()), this, SLOT(readClientRequest()));
    ++m_connectionCount;
}

void CEMSMonitoring::readClientRequest()
{
    QTcpSocket *pSocket = qobject_cast<QTcpSocket*>(QObject::sender());
    QString request = pSocket->readAll();
    qDebug() << "CEMSDatalogger send: " << request;
    if(m_isWaitLoggerResp) {
        if(/*request.startsWith("$CEMS") &&*/ request.contains(m_msgContent)) {
            qDebug() << "CEMSDatalogger responsed";
            m_isWaitLoggerResp = false;
        }
    }
}

void CEMSMonitoring::loggerCheckLive()
{
    qDebug() << "loggerCheckLive";
    if(!m_connectionCount) {        //no any connection
        runLogger();
    }
    else if(m_isWaitLoggerResp) {   //CEMS connected but not response
        qDebug() << "CEMSDatalogger not response";
        runLogger();
        m_isWaitLoggerResp = false;
    }
    else if(m_logger) {             //(CEMS connected and responsed) or (after restart CEMS), send new check message
        m_msgContent = QTime::currentTime().toString("sszzz");
        m_logger->write(QString("$CM,%1\r\n").arg(m_msgContent).toStdString().c_str());
        m_isWaitLoggerResp = true;
    }
}

void CEMSMonitoring::clientDisconnected()
{
    qDebug() << "Client Disconnected";
    m_logger = nullptr;
    --m_connectionCount;
    runLogger();
}

void CEMSMonitoring::runLogger()
{
//    runCommand(CMD_CHECKLOGGER_RUNNING);
//    m_cmd->waitForFinished(-1);
//    m_cmd->waitForReadyRead();
//    QString result(m_cmd->readAllStandardOutput());
//    qDebug() << "readAllStandardOutput:" << result;
//    if(!result.contains(CMD_CHECK_RESULT_CONTAIN)) {
//        runCommand(CMD_RUNLOGGER);
//        qDebug() << "Restart CEMSDatalogger";
//    }
//    else
//        qDebug() << "CEMSDatalogger readly stared";
    runCommand(CMD_RUNLOGGER);
}

void CEMSMonitoring::runCommand(QString command)
{
    if(m_cmd->state() == QProcess::NotRunning)
        m_cmd->start(command);
    else
        m_cmd->write(command.append("\r\n").toStdString().c_str());
}

void CEMSMonitoring::startListen()
{
    if (m_server) {
        connect(m_server, SIGNAL(newConnection()), this, SLOT(connectionHandler()), Qt::UniqueConnection);
        if (m_server->isListening()) {
            qDebug() << "Server can't start";
            return;
        }

        if(m_server->listen(QHostAddress::LocalHost, LISTEN_PORT))
            qDebug() << "Server started";
        else
            qDebug() << "Server can't start";
    }
}
