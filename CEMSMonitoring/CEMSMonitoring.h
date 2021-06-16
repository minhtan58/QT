/****************************************************************************

    Copyright (C) 2018 by LGE
    File: CEMSMonitoring.h
    Create: 15
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef CEMSMONITORING_H
#define CEMSMONITORING_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QTime>
#include <QProcess>

class CEMSMonitoring : public QObject
{
    Q_OBJECT
public:
    explicit CEMSMonitoring(QObject *parent = nullptr);
    ~CEMSMonitoring();
    void startListen();

public slots:
    void connectionHandler();
    void readClientRequest();
    void loggerCheckLive();
    void clientDisconnected();

private:
    QTcpServer *m_server = nullptr;
    QTcpSocket *m_logger = nullptr;
    QTimer *m_checkLogger = nullptr;
    QProcess *m_cmd = nullptr;

    bool m_isWaitLoggerResp = false;
    QString m_msgContent;

    int m_connectionCount;

    void runLogger();
    void runCommand(QString command);
};

#endif // CEMSMONITORING_H
