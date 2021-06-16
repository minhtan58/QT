/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: DConI7017RC.cpp
    Create: 11/12/2017
    Author: Minh Tan

 ****************************************************************************/

#include "DConI7017RC.h"

DConI7017RC::DConI7017RC(QObject *parent)
    : QObject(parent)
{
    m_currentChanel = -1;
    m_readMode = MODE_READ_CHANEL;
    m_readStatus = STATUS_READ_IDLE;
    m_serial = new QSerialPort(this);
    m_readScheduce = new QTimer(this);
    m_updateStatus = new QTimer(this);
    configSerialPort();
    initCommand();

    connect(m_readScheduce, SIGNAL(timeout()), this, SLOT(sltRequestReadScheduce()), Qt::UniqueConnection);
    connect(m_updateStatus, SIGNAL(timeout()), this, SLOT(sltUpdateStatus()), Qt::UniqueConnection);
    m_updateStatus->start(TIM_UPDATE_STATUS);
}

void DConI7017RC::sltConnectSerialPort()
{
    if(m_serial->isOpen()) {
        if(m_serial->portName() != GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME)
                || m_serial->baudRate() != GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE).toInt()) {
            m_serial->close();
        } else {
            return;
        }
    }

    if(!m_serial->isOpen()) {
        m_serial->setPortName(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME));
        m_serial->setBaudRate(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE).toUInt());
        if(m_serial->open(QIODevice::ReadWrite)) {
            startReadData(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_INTERVAL).toUInt());
            DLOG("Connected to %s - %d", m_serial->portName().toStdString().data(), m_serial->baudRate());
            connect(m_serial, SIGNAL(readyRead()), this, SLOT(sltReadSerialData()), Qt::UniqueConnection);
            SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS, "1");
        } else {
            DLOG("Can't connect to %s - %d", m_serial->portName().toStdString().data(), m_serial->baudRate());
            SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS, "0");
        }
    } else {
        SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS, "0");
    }
}

void DConI7017RC::sltUpdateStatus()
{
    if (!m_serial->isOpen()) {
        sltConnectSerialPort();
    }
    SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS, m_serial->isOpen() ? "1" : "0");
}

void DConI7017RC::testConnection(QString portName, int baudrate)
{
    if(m_serial->portName() == portName) {
        if(m_serial->isOpen()) {
            SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_TEST_CONNECTION, QString::number(int(TC_TEST_RESULT_OK)));
            return;
        }
    }

    QSerialPort testSerial;
    testSerial.setPortName(portName);
    testSerial.setBaudRate(baudrate);
    testSerial.setParity(QSerialPort::NoParity);
    testSerial.setDataBits(QSerialPort::Data8);
    testSerial.setStopBits(QSerialPort::OneStop);

    if(testSerial.open(QIODevice::ReadWrite)) {
        SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_TEST_CONNECTION, QString::number(int(TC_TEST_RESULT_OK)));
    } else {
        SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_TEST_CONNECTION, QString::number(int(TC_TEST_RESULT_FAIL)));
    }
}

QString DConI7017RC::getChanelValue(int i)
{
    return m_valueRegister[i];
}

QStringList DConI7017RC::getChanelValueAll()
{
    return QStringList()
            << m_valueRegister[0]
            << m_valueRegister[1]
            << m_valueRegister[2]
            << m_valueRegister[3]
            << m_valueRegister[4]
            << m_valueRegister[5]
            << m_valueRegister[6]
            << m_valueRegister[7];
}

void DConI7017RC::startReadData(int msec)
{
    if(msec <= 0) {
        DLOG("Serial interval invalid");
        return;
    }
    sltRequestReadScheduce();
    m_readScheduce->start(msec);
}

void DConI7017RC::setReadMode(int mode)
{
    m_readMode = mode;
}

void DConI7017RC::sltReadSerialData()
{
    m_serial->waitForReadyRead(200);
    QByteArray message = m_serial->readAll();
    QString str = QString::fromStdString(message.toStdString());

    //DLOG("Read: %s", str.toStdString().data());

    if(!str.startsWith(">") || !str.endsWith("\x0D")) {
        QThread::msleep(DELAY_REQ_MS);
        sltRequestReadScheduce();
//        m_currentChanel = -1;
        return;
    }
    switch (m_readMode) {
    case MODE_READ_ALL:
        alynasisDConMessage(message);
        emit sgnReadComplete();
        break;
    case MODE_READ_CHANEL:
        if(m_currentChanel > -1 && m_currentChanel < 7) {
            m_valueRegister[m_currentChanel++] = str.remove(str.length() - 1, 1).remove(0, 2);
            QThread::msleep(DELAY_REQ_MS);
            sendCommand(DCON_READ_AI_0 + m_currentChanel, 1);
        } else if (m_currentChanel == 7) {
            m_valueRegister[m_currentChanel] = str.remove(str.length() - 1, 1).remove(0, 2);
            m_currentChanel = -1;
            m_readStatus = STATUS_READ_FINISHED;
            DLOG("Read Finished: %s, %s, %s, %s, %s, %s, %s, %s",
                    m_valueRegister[0].toStdString().data(),
                    m_valueRegister[1].toStdString().data(),
                    m_valueRegister[2].toStdString().data(),
                    m_valueRegister[3].toStdString().data(),
                    m_valueRegister[4].toStdString().data(),
                    m_valueRegister[5].toStdString().data(),
                    m_valueRegister[6].toStdString().data(),
                    m_valueRegister[7].toStdString().data());
            emit sgnReadComplete();
        }
        break;

    default:
        break;
    }

}

void DConI7017RC::sltRequestReadScheduce()
{
    if(!m_serial->isOpen())
        return;

    switch (m_readMode) {
    case MODE_READ_ALL:
        sendCommand(DCON_READ_AI_ALL, 1);
        break;
    case MODE_READ_CHANEL:
        if(m_readStatus == STATUS_READ_IDLE || m_readStatus == STATUS_READ_FINISHED) {
            m_currentChanel = 0;
            sendCommand(DCON_READ_AI_0 + m_currentChanel, 1);
            m_readStatus = STATUS_READ_STARTED;
        } else if(m_readStatus == STATUS_READ_STARTED) {
            sendCommand(DCON_READ_AI_0 + m_currentChanel, 1);
        }
        break;
    default:
        break;
    }
}

void DConI7017RC::configSerialPort()
{
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
}

void DConI7017RC::initCommand()
{
    m_command.insert(DCON_GET_MODULE_NAME,              QString("$[_ADDRESS_ID_]M\r"));
    m_command.insert(DCON_GET_FIRMWARE,                 QString("$[_ADDRESS_ID_]F\r"));
    m_command.insert(DCON_GET_MODULE_CONFIGURE,         QString("$[_ADDRESS_ID_]2\r"));
    m_command.insert(DCON_SET_MODULE_CONFIGURE,         QString("%[_ADDRESS_ID_]010D0A00\r"));
    m_command.insert(DCON_GET_CHANEL_ENABLE_STATUS,     QString("$[_ADDRESS_ID_]6\r"));
    m_command.insert(DCON_SET_CHANEL_ENABLE_STATUS,     QString("$[_ADDRESS_ID_]5FF\r"));
    m_command.insert(DCON_READ_AI_ALL,                  QString("#[_ADDRESS_ID_]\r"));
    m_command.insert(DCON_READ_AI_0,                    QString("#[_ADDRESS_ID_]0\r"));
    m_command.insert(DCON_READ_AI_1,                    QString("#[_ADDRESS_ID_]1\r"));
    m_command.insert(DCON_READ_AI_2,                    QString("#[_ADDRESS_ID_]2\r"));
    m_command.insert(DCON_READ_AI_3,                    QString("#[_ADDRESS_ID_]3\r"));
    m_command.insert(DCON_READ_AI_4,                    QString("#[_ADDRESS_ID_]4\r"));
    m_command.insert(DCON_READ_AI_5,                    QString("#[_ADDRESS_ID_]5\r"));
    m_command.insert(DCON_READ_AI_6,                    QString("#[_ADDRESS_ID_]6\r"));
    m_command.insert(DCON_READ_AI_7,                    QString("#[_ADDRESS_ID_]7\r"));

    for (int i = 0; i < 8; ++i) {
        m_valueRegister[i] = "";
    }
}

void DConI7017RC::sendCommand(int commandId, int addressId)
{
    if(m_serial->isOpen()) {
        QString command = m_command.value(commandId);
        command = COMMAND_BUIDER(command, addressId);
        m_serial->write(command.toStdString().c_str());
        //DLOG("Send command: %s", command.toStdString().c_str());
    }
}

void DConI7017RC::alynasisDConMessage(QByteArray message)
{
    QString msg = QString::fromStdString(message.toStdString());
    QStringList elements = msg.remove(msg.length() - 1, 1).remove(0, 1).split('+', QString::SkipEmptyParts);
    if(elements.size() == 8) {
        for (int i = 0; i < 8; ++i) {
            m_valueRegister[i] = elements[i];
        }
    }
}
