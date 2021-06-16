/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: SettingsHandler.cpp
    Create: 07/03/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#include "SettingsHandler.h"

SettingsHandler::SettingsHandler(QObject *parent)
    : QObject(parent)
{
    loadIniSettings();
    checkerSerialConfigure();
    connect(m_serial, SIGNAL(readyRead()), this, SLOT(readResponse()));
//    m_serialList = getAvaiableSerialPort("ttyUSB");

    m_checkSession = new QTimer(this);
    m_checkSession->setSingleShot(true);
    connect(m_checkSession, SIGNAL(timeout()), this, SLOT(checkSerialSessionFinished()));

    m_checkScheduce = new QTimer(this);
    connect(m_checkScheduce, SIGNAL(timeout()), this, SLOT(checkSerialAutomatic()));
    m_checkScheduce->start(10000);
    checkSerialAutomatic();
}

void SettingsHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case HMIEvents::HMI_TEXTINPUT_DONE_DEVICE_CODE: {
        MODEL->deviceCodeSet(param);
        SettingsLoader::setValue(SETTINGS_GROUP_DEVICE, SETTINGS_DEVICE_CODE, param);
        break;
    }
    case HMIEvents::HMI_TEXTINPUT_DONE_DEVICE_NAME: {
        MODEL->deviceNameSet(param);
        SettingsLoader::setValue(SETTINGS_GROUP_DEVICE, SETTINGS_DEVICE_NAME, param);
        break;
    }
    case HMIEvents::HMI_TEXTINPUT_DONE_DEVICE_LOCATION: {
        MODEL->deviceLocationSet(param);
        SettingsLoader::setValue(SETTINGS_GROUP_DEVICE, SETTINGS_DEVICE_LOCATION, param);
        break;
    }
    case HMIEvents::HMI_TEXTINPUT_DONE_TELEMETRY_INTERNET_SERVER1: {
        MODEL->telemetryInternetServer1Set(param);
        SettingsLoader::setValue(SETTINGS_GROUP_TELEMETRY, SETTINGS_TELEMETRY_INTERNET_SERVER1, param);
        break;
    }
    case HMIEvents::HMI_TEXTINPUT_DONE_TELEMETRY_INTERNET_SERVER2: {
        MODEL->telemetryInternetServer2Set(param);
        SettingsLoader::setValue(SETTINGS_GROUP_TELEMETRY, SETTINGS_TELEMETRY_INTERNET_SERVER2, param);
        break;
    }
    case HMIEvents::HMI_SWITCH_UPDATE_TIME_AUTOMATIC: {
        MODEL->isSystemTimeAutoUpdateSet(param.toInt() == 1);
        SettingsLoader::setValue(SETTINGS_GROUP_DEVICE, SETTINGS_DEVICE_SYSTEMTIME_UPDATE_AUTOMATIC, param);
        break;
    }
    case HMIEvents::HMI_COMBOBOX_TELEMETRY_SENDTYPE_CHANGED: {
        MODEL->telemetryGeneralSendTypeSet(param.toInt());
        SettingsLoader::setValue(SETTINGS_GROUP_TELEMETRY, SETTINGS_TELEMETRY_GENERAL_SEND_TYPE, param);
        break;
    }
    case HMIEvents::HMI_COMBOBOX_TELEMETRY_CONTROLTYPE_CHANGED: {
        MODEL->telemetryGeneralControlTypeSet(param.toInt());
        SettingsLoader::setValue(SETTINGS_GROUP_TELEMETRY, SETTINGS_TELEMETRY_GENERAL_CONTROL_TYPE, param);
        break;
    }
    case HMIEvents::HMI_TEXTINPUT_DONE_TELEMETRY_GENERAL_SMSNOTIFY: {
        MODEL->telemetryGeneralSMSNotifySet(param);
        SettingsLoader::setValue(SETTINGS_GROUP_TELEMETRY, SETTINGS_TELEMETRY_GENERAL_SMS_NOTIFY, param);
        break;
    }
    case HMIEvents::HMI_SPINBOX_TELEMETRY_GENERAL_SENDINTERVAL: {
        MODEL->telemetryGeneralSendIntervalSet(param.toInt());
        SettingsLoader::setValue(SETTINGS_GROUP_TELEMETRY, SETTINGS_TELEMETRY_GENERAL_SEND_INTERVAL, param);
        break;
    }
    case HMIEvents::HMI_COMBOBOX_TELEMETRY_NETWORKTYPE_CHANGED: {
        MODEL->telemetryInternetNetworkTypeSet(param.toInt());
        SettingsLoader::setValue(SETTINGS_GROUP_TELEMETRY, SETTINGS_TELEMETRY_INTERNET_NETWORK_TYPE, param);
        break;
    }
    case HMIEvents::HMI_COMBOBOX_TELEMETRY_PROTOCOLTYPE_CHANGED: {
        MODEL->telemetryInternetProtocolTypeSet(param.toInt());
        SettingsLoader::setValue(SETTINGS_GROUP_TELEMETRY, SETTINGS_TELEMETRY_INTERNET_PROTOCOL_TYPE, param);
        break;
    }
    case HMIEvents::HMI_SPINBOX_SENSOR_INTERVAL: {
        MODEL->dataSendAutomaticRequestIntervalSet(param.toInt());
        SettingsLoader::setValue(SETTINGS_GROUP_SERIALPORT, SETTINGS_SERIALPORT_SENSOR_READ_INTERVAL, param);
        break;
    }
    case HMIEvents::HMI_COMBOBOX_DEVICETYPE_CHANGED: {
        MODEL->deviceTypeSet(param.toInt());
        SettingsLoader::setValue(SETTINGS_GROUP_DEVICE, SETTINGS_DEVICE_TYPE, param);
        break;
    }
    default:
        break;
    }
}

void SettingsHandler::readResponse()
{
    QString response = m_serial->readAll();
    DLOG("pressure response %s", response.toStdString().data());
    if(response.contains("p")) {
        m_serial->close();
        DLOG("Set sensor portname is %s", m_serial->portName().toStdString().data());
        MODEL->sensorPortNameSet(m_serial->portName());
        if(m_serialList.size() > 0) {
            DLOG("Set sim portname is %s", m_serial->portName().toStdString().data());
            MODEL->simPortNameSet(m_serialList.at(0));
        }
        m_checkSession->stop();
    }
}

void SettingsHandler::loadIniSettings()
{
    DLOG("Load ini settings start...");
    if(!SettingsLoader::exists())
        SettingsLoader::createSettingsFile();
    else {
        SettingsStruct settingsStruct = SettingsLoader::loadSettings();
        MODEL->deviceNameSet(settingsStruct.dDeviceName);
        MODEL->deviceCodeSet(settingsStruct.dDeviceCode);
        MODEL->deviceLocationSet(settingsStruct.dDeviceLocation);
        MODEL->isSystemTimeAutoUpdateSet(settingsStruct.dSystemTimeAutoUpdate.toUInt() == 1);
        MODEL->deviceTypeSet(settingsStruct.dDeviceType.toInt());

        MODEL->gpsPortNameSet(settingsStruct.sGpsPortName);
        MODEL->gpsBaudrateSet(settingsStruct.sGpsBaudrate);
//        MODEL->simPortNameSet(settingsStruct.sSimPortName);
//        MODEL->simBaudrateSet(settingsStruct.sSimBaudrate);
        MODEL->dataSendAutomaticRequestIntervalSet(settingsStruct.sSensorInterval.toInt());

        MODEL->telemetryGeneralSendTypeSet(settingsStruct.tgSendType.toInt());
        MODEL->telemetryGeneralControlTypeSet(settingsStruct.tgControlType.toInt());
        MODEL->telemetryGeneralSMSNotifySet(settingsStruct.tgSmsNotify);
        MODEL->telemetryGeneralSendIntervalSet(settingsStruct.tgSendInterval.toInt());

        MODEL->telemetryInternetNetworkTypeSet(settingsStruct.tiNetworkType.toInt());
        MODEL->telemetryInternetProtocolTypeSet(settingsStruct.tiProtocolType.toInt());
        MODEL->telemetryInternetServer1Set(settingsStruct.tiServer1);
        MODEL->telemetryInternetServer2Set(settingsStruct.tiServer2);
    }
    DLOG("Load ini settings finished");
    SENDRESPONSE(HMIEvents::HMI_RESPONSE_LOAD_SETTINGS_INI_FINISHED, "");
}

void SettingsHandler::checkSerialAutomatic()
{
    if(MODEL->isConnectedSIM() && MODEL->isConnectedSensor()){
        //DLOG("Return because all serial connected");
        return;
    }

    if(m_serialList.isEmpty()) {
        m_serialList = getAvaiableSerialPort("ttyUSB");
    }

    if(m_serialList.size() > 0) {
        DLOG("Checking port %s", m_serialList.at(0).toStdString().data());
        m_serial->setPortName(m_serialList.at(0));
        m_serialList.removeAt(0);
        if(m_serial->open(QIODevice::ReadWrite)) {
            m_checkSession->start(3000);
            m_serial->write("ptest\r\n");
            m_serial->waitForBytesWritten(50);
        }
    }
}

void SettingsHandler::checkSerialSessionFinished()
{
    DLOG("check Session Finished");
    if(m_serial->isOpen()) {
        m_serial->close();
    }
    checkSerialAutomatic();
}

QStringList SettingsHandler::getAvaiableSerialPort(QString pattern)
{
    QStringList list;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if(!info.isBusy()) {
            if(info.portName().contains(pattern)) {
                DLOG("Port Avaiable: %s", info.portName().toStdString().data());
                list << info.portName();
            }
        }
    }
    return list;
}

void SettingsHandler::checkerSerialConfigure()
{
    m_serial = new QSerialPort(this);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setBaudRate(QSerialPort::Baud9600);
}
