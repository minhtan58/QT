/****************************************************************************

    Copyright (C) 2018 by LGE
    File: SIM800C.h
    Create: 26
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef SIM800C_H
#define SIM800C_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "common.h"
#include "AppModel.h"
#include "UIBridge.h"

#define RET_CODE_CONNECT_OK         0b00000001
#define RET_CODE_ALREADY_CONNECT    0b00000010
#define RET_CODE_CONNECT_FAIL       0b00000100
#define RET_CODE_SEND_OK            0b00001000
#define RET_CODE_SEND_FAIL          0b00010000
#define RET_CODE_SHUT_OK            0b00100000
#define RET_CODE_SHUT_FAIL          0b01000000

class SIM800C : public QObject
{
    Q_OBJECT
public:
    explicit SIM800C(QObject *parent = nullptr);

    enum eReadResponseStatus {
        RES_IDLE,
        RES_READ_STARTED,
        RES_READ_FINISHED,
    };

    enum eSendStatus {
        SS_SIM_UNAVAIABLE,
        SS_NOT_CONNECT,
        SS_SEND_OK,
        SS_SEND_FAIL,
    };

    void sendData(QString data);
    QString getResponse();
    void clearResponse();

    void getNetworkTime();

public slots:
    void readResponse();
    void onSimPortNameChanged();

private:
    QSerialPort *m_serial = nullptr;
    QHash<eCommandID, QString> m_commandMap;
    QString m_response;
    eReadResponseStatus m_resStatus = RES_IDLE;

    void serialPortConfigure();
    void initCommand();
    void sendCommand(QString command, int timeout = 1000);
    void sendCommand(eCommandID commandId, QString value, int timeout = 1000);
    void sendCommand(eCommandID commandId, int timeout = 1000);
    void sendCommand(char ch, int timeout = 1000);
    void tryConnectSIM();

    bool avaiableGPRS();
    void sendOverGPRS(QString command);
    void sendOverGSM(QString command);

    void sleep(int msec);
    void waitAllResponeFinished();
};

#endif // SIM800C_H
