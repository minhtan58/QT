/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: SerialPortHandler.h
    Create: 12/03/2018
    Author: Minh Tan

 ****************************************************************************/

#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "Common.h"
#include "DataManager.h"
#include "CEMSEnum.h"
#include "DConI7017RC.h"

class SerialPortHandler : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortHandler(QObject *parent = 0);

signals:
    void requestConnectSerialPort();

public slots:
    void eventHandler(QString objectName, int eventId, QString param);
    void sltReadConnect();
    void updateAppData(int dpid);

private:
    DConI7017RC *m_dcon = nullptr;

    void updateSerialPortList();
    void readDConChanel(int chanel, int ampType);
};

//thread define
class SerialPortHandlerThread : public QThread
{
    Q_OBJECT
public:
    SerialPortHandlerThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() {
        DLOG("Start");
        SerialPortHandler handler;
        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        connect(DataManager::getInstance(), SIGNAL(dataChanged(int)), &handler, SLOT(updateAppData(int)));
        exec();
    }
};

#endif // SERIALPORTHANDLER_H
