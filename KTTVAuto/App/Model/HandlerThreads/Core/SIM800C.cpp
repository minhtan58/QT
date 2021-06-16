/****************************************************************************

    Copyright (C) 2018 by LGE
    File: SIM800C.cpp
    Create: 26
    Author: Vuong Nguyen

 ****************************************************************************/

#include "SIM800C.h"

SIM800C::SIM800C(QObject *parent)
    : QObject(parent)
{
    initCommand();
    serialPortConfigure();
    connect(MODEL, SIGNAL(simPortNameChanged()), this, SLOT(onSimPortNameChanged()), Qt::QueuedConnection);
    m_response = "";
}

void SIM800C::sendData(QString data)
{
    DLOG("SIM send data");
    if(avaiableGPRS()) {
        sendOverGPRS(data);
    } else {
        sendOverGSM(data);
    }
}

QString SIM800C::getResponse()
{
    return m_response;
}

void SIM800C::clearResponse()
{
    m_response.clear();
    m_resStatus = RES_IDLE;
}

void SIM800C::getNetworkTime()
{
    sendCommand(CMD_AT_CCLK);
    waitAllResponeFinished();
}

void SIM800C::readResponse()
{
    m_serial->waitForReadyRead(500);
    QString responseText = m_serial->readAll();
    DLOG_THREAD << "SIM response: %s" << responseText;
    if(RES_READ_STARTED == m_resStatus) {
        m_response.append(responseText);
    }
}

void SIM800C::onSimPortNameChanged()
{
    if(MODEL->simPortName() == m_serial->portName()) {
        return;
    }

    if(m_serial->isOpen()) {
        m_serial->close();
        sleep(500);
    }

    if(!m_serial->isOpen()) {
        m_serial->setPortName(MODEL->simPortName());
        MODEL->isConnectedSIMSet(m_serial->open(QIODevice::ReadWrite));
        DLOG("%s to serial port %s, baudrate %d", (MODEL->isConnectedSIM() ? "Connected" : "Cannot connect"), m_serial->portName().toStdString().data(), m_serial->baudRate());
    } else {
        DLOG("Can't restart serial port");
    }
}

void SIM800C::serialPortConfigure()
{
    m_serial = new QSerialPort(this);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    connect(m_serial, SIGNAL(readyRead()), this, SLOT(readResponse()));
//    tryConnectSIM();
}

void SIM800C::initCommand()
{
    /* system command */
    m_commandMap.insert(CMD_AT_CLTS,             "AT+CLTS");
    m_commandMap.insert(CMD_AT_CCLK,             "AT+CCLK?");

    m_commandMap.insert(CMD_AT,             "AT");
    m_commandMap.insert(CMD_AT_CGATT,       "AT+CGATT");
    m_commandMap.insert(CMD_AT_CIPMUX,      "AT+CIPMUX");
    m_commandMap.insert(CMD_AT_CSTT,        "AT+CSTT");
    m_commandMap.insert(CMD_AT_CWMODE,      "AT+CWMODE");
    m_commandMap.insert(CMD_AT_CIICR,       "AT+CIICR");
    m_commandMap.insert(CMD_AT_CIFSR,       "AT+CIFSR");
    m_commandMap.insert(CMD_AT_CIPSTART,    "AT+CIPSTART");
    m_commandMap.insert(CMD_AT_CIPSEND,     "AT+CIPSEND");
    m_commandMap.insert(CMD_AT_CIPCLOSE,    "AT+CIPCLOSE");
    m_commandMap.insert(CMD_AT_CIPSHUT,     "AT+CIPSHUT");
    m_commandMap.insert(CMD_AT_CFUN,        "AT+CFUN");

    //GSM Command
    m_commandMap.insert(CMD_AT_CMGF,        "AT+CMGF");
    m_commandMap.insert(CMD_AT_CMGW,        "AT+CMGW");
    m_commandMap.insert(CMD_AT_CMSS,        "AT+CMSS");
}

void SIM800C::sendCommand(QString command, int timeout)
{
    tryConnectSIM();
    if(m_serial->isOpen()) {
        if(command.endsWith("\r\n")) {
            m_serial->write(command.toStdString().data());
        } else {
            m_serial->write(QString("%1\r\n").arg(command).toStdString().data());
        }
    }
    m_serial->waitForBytesWritten(timeout);
    DLOG_THREAD << "Sent command: " << command;
    sleep(timeout);
}

void SIM800C::sendCommand(eCommandID commandId, QString value, int timeout)
{
    tryConnectSIM();
    if(m_serial->isOpen()) {
        QString command = m_commandMap.value(commandId);
        if(value.endsWith("\r\n")) {
            command = QString("%1=%2").arg(command).arg(value);
        } else {
            command = QString("%1=%2\r\n").arg(command).arg(value);
        }
        m_serial->write(command.toStdString().data());
        m_serial->waitForBytesWritten(timeout);
        DLOG_THREAD << "Sent command: " << command;
        sleep(timeout);
    }
}

void SIM800C::sendCommand(eCommandID commandId, int timeout)
{
    tryConnectSIM();
    if(m_serial->isOpen()) {
        m_serial->write(QString("%1\r\n").arg(m_commandMap.value(commandId)).toStdString().data());
        m_serial->waitForBytesWritten(timeout);
        DLOG_THREAD << "Sent command: " << m_commandMap.value(commandId);
        sleep(timeout);
    }
}

void SIM800C::sendCommand(char ch, int timeout)
{
    tryConnectSIM();
    if(m_serial->isOpen()) {
        m_serial->putChar(ch);
        m_serial->waitForBytesWritten(timeout);
        DLOG_THREAD << "Sent command: " << ch;
        sleep(timeout);
    }
}

void SIM800C::tryConnectSIM()
{
    if(!m_serial->isOpen()) {
        m_serial->setPortName(MODEL->simPortName());
        m_serial->setBaudRate(QSerialPort::Baud9600);
        MODEL->isConnectedSIMSet(m_serial->open(QIODevice::ReadWrite));
        DLOG("%s to serial port %s, baudrate %d", (MODEL->isConnectedSIM() ? "Connected" : "Can't connect"), m_serial->portName().toStdString().data(), m_serial->baudRate());
    } else {
        MODEL->isConnectedSIMSet(true);
    }
}

bool SIM800C::avaiableGPRS()
{
    return true;
}

void SIM800C::sendOverGPRS(QString command)
{
    tryConnectSIM();
    if (!MODEL->isConnectedSIM()) {
        DLOG("Can't connect to SIM module");
        return;
    }

    QString ip, port;
    ip = MODEL->getServer1IP();
    port = MODEL->getServer1Port();
    DLOG("IP - %s, port - %s", ip.toStdString().data(), port.toStdString().data());

    if(ip.isEmpty() || port.isEmpty())
    {
        DLOG("IP or Port incorrect");
        return;
    }

    /* Start read response from SIM */
    if(RES_IDLE == m_resStatus) {
        m_resStatus = RES_READ_STARTED;
    }
    sendCommand(CMD_AT_CIPSTART, QString("\"TCP\",\"%1\",\"%2\"").arg(ip).arg(port), 4000);
    sendCommand(CMD_AT_CIPSEND, 2000);
    sendCommand(command, 0);
    sendCommand(26, 0);
    waitAllResponeFinished();
    sendCommand(CMD_AT_CIPSHUT, 1000);
    waitAllResponeFinished();

    /* Response read finished */
    m_resStatus = RES_READ_FINISHED;


}

void SIM800C::sendOverGSM(QString command)
{
    sendCommand(command);
}

void SIM800C::sleep(int msec)
{
    QThread::msleep(msec);
}

void SIM800C::waitAllResponeFinished()
{
    m_serial->waitForBytesWritten(2000);
    m_serial->waitForReadyRead(2000);
}
