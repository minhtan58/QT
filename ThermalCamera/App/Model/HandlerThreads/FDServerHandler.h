#ifndef FDSERVERHANDLER_H
#define FDSERVERHANDLER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QTcpSocket>

#include "Delivery.h"
#include "Common.h"
#include "DataManager.h"
#include "Defines.h"

class FDServerHandler : public QObject
{
    Q_OBJECT
public:
    explicit FDServerHandler(QObject *parent = nullptr);

public slots:
    void sendDataToServer();
    void sendAlarmToFDServer();
    void updateData(int dpid, QString value);
    void handleEvent(QString objectName, int eventId, QString params);

private:
    QTcpSocket *m_tcpSocket = nullptr;
    QString m_serverIp;
    int m_serverPort;

    bool connectToServer(QString ip, int port);
};

//thread define
class FDServerHandlerThread : public QThread
{
    Q_OBJECT
public:
    FDServerHandlerThread(QObject *parent = nullptr)
        : QThread(parent)
    {}

protected:
    void run() {
        DLOG("Start");
        FDServerHandler handler;
        exec();
    }
};

#endif // FDSERVERHANDLER_H
