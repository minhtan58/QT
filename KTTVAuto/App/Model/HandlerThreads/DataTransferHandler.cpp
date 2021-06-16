/****************************************************************************

    Copyright (C) 2018 by Kingkong JSC
    File: DataTransferHandler.cpp
    Create: 17
    Author: Vuong Nguyen

 ****************************************************************************/

#include "DataTransferHandler.h"

DataTransferHandler::DataTransferHandler(QObject *parent) : QObject(parent)
{
    connect(MODEL, SIGNAL(telemetryGeneralControlTypeChanged()), this, SLOT(changeTelemetryControlType()));
    connect(MODEL, SIGNAL(telemetryGeneralSendIntervalChanged()), this, SLOT(changeTelemetrySendInterval()));
    m_sendAutomaticTimer = new QTimer(this);
    connect(m_sendAutomaticTimer, SIGNAL(timeout()), this, SLOT(autoSendData()));
}

void DataTransferHandler::start()
{
    if(MODEL->telemetryGeneralControlType() == TELEMETRY_CONTROL_TYPE_AUTOMATIC
            && MODEL->telemetryGeneralSendInterval() > 0) {
        startSendAutomatic();
    }
}

void DataTransferHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case HMIEvents::HMI_BUTTON_WORK_MAIN_SEND: {
        SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "0Đang gửi ...");
        bool isGen = false;
        if(MODEL->workMainText().isEmpty()) {
            MODEL->workMainTextSet(MODEL->generateWorkMainText());
            isGen = true;
        }
        int resp = send(MODEL->workMainText());
        if(resp == SIM800C::SS_SIM_UNAVAIABLE) {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Gửi không thành công, vui lòng kiểm tra sim");
        } else if(resp == SIM800C::SS_SEND_OK) {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Gửi thành công!");
        } else {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Gửi không thành công");
        }

        if(isGen) {
            MODEL->workMainTextSet("");
        }
        break;
    }
    case HMIEvents::HMI_BUTTON_WORK_SIMPLE_SEND: {
        SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "0Đang gửi ...");
        bool isGen = false;
        if(MODEL->workSimpleText().isEmpty()) {
            MODEL->workSimpleTextSet(MODEL->generateWorkSimpleText());
            isGen = true;
        }
        int resp = send(MODEL->workSimpleText());
        if(resp == SIM800C::SS_SIM_UNAVAIABLE) {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Gửi không thành công, vui lòng kiểm tra sim");
        } else if(resp == SIM800C::SS_SEND_OK) {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Gửi thành công!");
        } else {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Gửi không thành công");
        }

        if(isGen) {
            MODEL->workSimpleTextSet("");
        }
        break;
    }
    case HMIEvents::HMI_REQUEST_GET_NETWORK_TIME: {
        sim800c.getNetworkTime();
        break;
    }
    default:
        break;
    }
}

void DataTransferHandler::autoSendData()
{
    MODEL->workMainTextSet(MODEL->generateWorkMainText());
    send(MODEL->workMainText());
}

void DataTransferHandler::changeTelemetryControlType()
{
    DLOG("Telemetry control type change to %d", MODEL->telemetryGeneralControlType());
    eTelemetryControlType controlType = (eTelemetryControlType)MODEL->telemetryGeneralControlType();
    switch (controlType) {
    case TELEMETRY_CONTROL_TYPE_USER:
        DLOG("Send data switch to user mode");
        if(m_sendAutomaticTimer->isActive()) {
            stopSendAutomatic();
        }
        break;

    case TELEMETRY_CONTROL_TYPE_AUTOMATIC:
        DLOG("Send data switch to automatic mode");
        if(MODEL->telemetryGeneralSendInterval() > 0) {
            if (!m_sendAutomaticTimer->isActive()) {
                startSendAutomatic();
            } else {
                restartSendAutomatic();
                DLOG("Interval unable");
            }
        }
        break;
    default:
        break;
    }
}

void DataTransferHandler::changeTelemetrySendInterval()
{
    eTelemetryControlType controlType = (eTelemetryControlType)MODEL->telemetryGeneralControlType();
    switch (controlType) {
    case TELEMETRY_CONTROL_TYPE_USER:
        break;
    case TELEMETRY_CONTROL_TYPE_AUTOMATIC:
        if(MODEL->telemetryGeneralSendInterval() > 0) {
            if(m_sendAutomaticTimer->isActive()) {
                restartSendAutomatic();
            } else {
                startSendAutomatic();
            }
        }
        break;
    default:
        break;
    }
}

void DataTransferHandler::startSendAutomatic()
{
    m_sendAutomaticTimer->start(MODEL->telemetryGeneralSendInterval());
    DLOG("Start auto send data with interval %d", m_sendAutomaticTimer->interval());
}

void DataTransferHandler::stopSendAutomatic()
{
    m_sendAutomaticTimer->stop();
    DLOG("Stop auto send data");
}

void DataTransferHandler::restartSendAutomatic()
{
    m_sendAutomaticTimer->stop();
    m_sendAutomaticTimer->start(MODEL->telemetryGeneralSendInterval());
    DLOG("Restart auto send data with interval %d", m_sendAutomaticTimer->interval());
}

int DataTransferHandler::send(QString data)
{
    sim800c.sendData(data);
    QString response = sim800c.getResponse();
    sim800c.clearResponse();
    DLOG_THREAD << "SIM RES" << response;
    if (response.contains("ALREADY CONNECT") || response.contains("CONNECT OK")) {
        DLOG("CONNECTED SERVER");
    }

    SENDREQUEST(HMIEvents::HMI_REQUEST_DB_SAVE_KHITUONG);

    if(response.isEmpty()) {
        DLOG("SIM Unavaiable");
        return SIM800C::SS_SIM_UNAVAIABLE;
    } else if(response.contains("SEND OK")) {
        DLOG("SEND OK");
        return SIM800C::SS_SEND_OK;
    } else {
        return SIM800C::SS_SEND_FAIL;
    }
}
