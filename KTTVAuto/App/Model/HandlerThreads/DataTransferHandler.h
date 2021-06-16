/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: DataTransferHandler.h
    Create: 17
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef DATATRANSFERHANDLER_H
#define DATATRANSFERHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

#include "Common.h"
#include "AppModel.h"
#include "UIBridge.h"
#include "SIM800C.h"

class DataTransferHandler : public QObject
{
    Q_OBJECT
public:
    explicit DataTransferHandler(QObject *parent = nullptr);
    void start();

signals:

public slots:
    void eventHandler(QString objectName, int eventId, QString param);
    void autoSendData();

    void changeTelemetryControlType();
    void changeTelemetrySendInterval();

private:
    SIM800C sim800c;
    QTimer *m_sendAutomaticTimer = nullptr;

    void startSendAutomatic();
    void stopSendAutomatic();
    void restartSendAutomatic();
    int send(QString data);
};

//thread define
class DataTransferHandlerThread : public QThread
{
    Q_OBJECT
public:
    DataTransferHandlerThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() {
        DLOG("Starting...");
        DataTransferHandler handler;
        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        handler.start();
        exec();
    }
};

#endif // DATATRANSFERHANDLER_H
