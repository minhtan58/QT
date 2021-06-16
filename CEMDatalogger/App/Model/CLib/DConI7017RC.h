/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: DConI7017RC.h
    Create: 11/12/2017
    Author: Minh Tan

 ****************************************************************************/

#ifndef DCONI7017RC_H
#define DCONI7017RC_H

#include <QTimer>
#include <QSerialPort>
#include "CEMSEnum.h"
#include "DataManager.h"
#include "Common.h"

#define ADDRESS_ID                          QString("[_ADDRESS_ID_]")
#define COMMAND_BUIDER(command, addressId)  command.replace(ADDRESS_ID, QString::number(addressId, 16).toUpper().rightJustified(2, '0'))

class DConI7017RC : public QObject
{
    Q_OBJECT
public:
    explicit DConI7017RC(QObject *parent = nullptr);

    enum {
        DCON_GET_MODULE_NAME = 0x00,
        DCON_GET_FIRMWARE,
        DCON_GET_MODULE_CONFIGURE,
        DCON_SET_MODULE_CONFIGURE,
        DCON_GET_CHANEL_ENABLE_STATUS,
        DCON_SET_CHANEL_ENABLE_STATUS,
        DCON_READ_AI_ALL,
        DCON_READ_AI_0,
        DCON_READ_AI_1,
        DCON_READ_AI_2,
        DCON_READ_AI_3,
        DCON_READ_AI_4,
        DCON_READ_AI_5,
        DCON_READ_AI_6,
        DCON_READ_AI_7
    };

    enum ReadMode {
        MODE_READ_ALL,
        MODE_READ_CHANEL
    };

    enum ReadStatus {
        STATUS_READ_IDLE,
        STATUS_READ_STARTED,
        STATUS_READ_FINISHED
    };

    void startReadData(int msec);
    void setReadMode(int mode);
    QString getChanelValue(int i);
    QStringList getChanelValueAll();


signals:
    void sgnReadComplete();

public slots:
    void sltReadSerialData();
    void sltRequestReadScheduce();
    void testConnection(QString portName, int baudrate);
    void sltConnectSerialPort();
    void sltUpdateStatus();

private:
    QSerialPort *m_serial = nullptr;
    QTimer *m_readScheduce = nullptr;
    QTimer *m_updateStatus = nullptr;
    QMap<int, QString> m_command;
    QString m_valueRegister[8];
    int m_readStatus;
    int m_readMode;
    int m_currentChanel;

    void configSerialPort();
    void initCommand();
    void sendCommand(int commandId, int addressId);
    void alynasisDConMessage(QByteArray message);
};

#endif // DCONI7017RC_H
