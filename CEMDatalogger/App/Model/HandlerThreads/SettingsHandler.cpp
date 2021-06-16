/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: SettingsHandler.cpp
    Create: 07/03/2018
    Author: Minh Tan

 ****************************************************************************/

#include "SettingsHandler.h"

SettingsHandler::SettingsHandler(QObject *parent)
    : QObject(parent)
{
    loadIniSettings();
}

void SettingsHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case CEMSEnum::HMI_TEXTINPUT_DONE_STATION_ID:
        SETDPDATA(CEMSEnum::DP_GENERAL_STATION_ID, param);
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_STATION_ID, param);
        break;

    case CEMSEnum::HMI_TEXTINPUT_DONE_STATION_NAME:
        SETDPDATA(CEMSEnum::DP_GENERAL_STATION_NAME, param);
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_STATION_NAME, param);
        break;

    case CEMSEnum::HMI_TEXTINPUT_DONE_SERVER_IP:
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP, param);
        SettingsLoader::setValue(SETTINGS_GROUP_NETWORK_SERVER, SETTINGS_NETWORK_SERVER_IP, param);
        break;

    case CEMSEnum::HMI_TEXTINPUT_DONE_SERVER_PORT:
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT, param);
        SettingsLoader::setValue(SETTINGS_GROUP_NETWORK_SERVER, SETTINGS_NETWORK_SERVER_PORT, param);
        break;

    case CEMSEnum::HMI_SPINBOX_CHANGE_SERVER_INTERVAL:
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_INTERVAL, param);
        SettingsLoader::setValue(SETTINGS_GROUP_NETWORK_SERVER, SETTINGS_NETWORK_SERVER_INTERVAL, param);
        break;

    case CEMSEnum::HMI_TEXTINPUT_DONE_FTP_IP:
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_IP, param);
        SettingsLoader::setValue(SETTINGS_GROUP_NETWORK_FTP, SETTINGS_NETWORK_FTP_IP, param);
        break;

    case CEMSEnum::HMI_TEXTINPUT_DONE_FTP_PORT:
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PORT, param);
        SettingsLoader::setValue(SETTINGS_GROUP_NETWORK_FTP, SETTINGS_NETWORK_FTP_PORT, param);
        break;

    case CEMSEnum::HMI_TEXTINPUT_DONE_FTP_USERNAME:
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_USER, param);
        SettingsLoader::setValue(SETTINGS_GROUP_NETWORK_FTP, SETTINGS_NETWORK_FTP_USER, param);
        break;

    case CEMSEnum::HMI_TEXTINPUT_DONE_FTP_PASSWORD:
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PASSWORD, param);
        SettingsLoader::setValue(SETTINGS_GROUP_NETWORK_FTP, SETTINGS_NETWORK_FTP_PASSWORD, param);
        break;

    case CEMSEnum::HMI_SPINBOX_CHANGE_FTP_INTERVAL:
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_INTERVAL, param);
        SettingsLoader::setValue(SETTINGS_GROUP_NETWORK_FTP, SETTINGS_NETWORK_FTP_INTERVAL, param);
        break;

    case CEMSEnum::HMI_BUTTON_SAVE_SETTINGS_SERIALPORT: {
        QStringList paramList = getListParam(param);
        QString sPortName = paramList.at(0);
        QString sBaudrate = paramList.at(1);
        SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME, sPortName);
        SettingsLoader::setValue(SETTINGS_GROUP_SERIALPORT, SETTINGS_SERIALPORT_PORTNAME, sPortName);
        SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE, sBaudrate);
        SettingsLoader::setValue(SETTINGS_GROUP_SERIALPORT, SETTINGS_SERIALPORT_BAUDRATE, sBaudrate);
        SENDEVENT("", CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Save Succesful");
        break;
    }
    case CEMSEnum::HMI_BUTTON_SAVE_SETTINGS_ALARM: {
        QStringList paramList = getListParam(param);
        int aCurrentIndex = paramList.at(0).toInt();
        QString aLow = paramList.at(1);
        QString aHigh = paramList.at(2);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MIN + aCurrentIndex * 3, aLow);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MAX + aCurrentIndex * 3, aHigh);
        SettingsLoader::setValue(SETTINGS_GROUP_ALARM, SETTINGS_ALARM_MIN_O2 + aCurrentIndex * 3, aLow);
        SettingsLoader::setValue(SETTINGS_GROUP_ALARM, SETTINGS_ALARM_MAX_O2 + aCurrentIndex * 3, aHigh);
        SENDEVENT("", CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Save Succesful");
        break;
    }
    case CEMSEnum::HMI_COMBOBOX_SETTINGS_ALARM: {
        QStringList paramList = getListParam(param);
        int aCurrentIndex = paramList.at(0).toInt();
        QString aStatus = paramList.at(1);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_STATUS + aCurrentIndex * 3, aStatus);
        SettingsLoader::setValue(SETTINGS_GROUP_ALARM, SETTINGS_ALARM_STATUS_O2 + aCurrentIndex * 3, aStatus);
        break;
    }
    case CEMSEnum::HMI_BUTTON_RELOAD_CONFIGURATION_FILE: {
        loadIniSettings();
        break;
    }
    case CEMSEnum::HMI_BUTTON_SET_RADIUS: {
        if(param.isEmpty())
            SENDEVENT("", CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Please fill valid radius");
        else {
            SETDPDATA(CEMSEnum::DP_GENERAL_RADIUS, param);
            SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_RADIUS, param);
            SENDEVENT("", CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Save Succesful");
        }
        break;
    }
    default:
        break;
    }
}

void SettingsHandler::loadIniSettings()
{
    if(!SettingsLoader::exists())
        SettingsLoader::createSettingsFile();
    else {
        SettingsStruct settingsStruct = SettingsLoader::loadSettings();

        SETDPDATA(CEMSEnum::DP_GENERAL_STATION_ID,                  settingsStruct.gStationId);
        SETDPDATA(CEMSEnum::DP_GENERAL_STATION_NAME,                settingsStruct.gStationName);
        SETDPDATA(CEMSEnum::DP_SYS_SETTINGS_TIME_AUTOMATIC_UPDATE,  settingsStruct.gSystemTimeAutoUpdate);
        SETDPDATA(CEMSEnum::DP_GENERAL_RADIUS,                      settingsStruct.gRadius);

        SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME,        settingsStruct.spPortName);
        SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE,        settingsStruct.spBaudrate);

        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP,          settingsStruct.nServerIp);
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT,        settingsStruct.nServerPort);
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_INTERVAL,    settingsStruct.nServerInterval);

        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_IP,             settingsStruct.nFtpIp);
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PORT,           settingsStruct.nFtpPort);
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_USER,           settingsStruct.nFtpUser);
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PASSWORD,       settingsStruct.nFtpPassword);
        SETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_INTERVAL,       settingsStruct.nFtpInterval);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_STATUS,            settingsStruct.aStatusO2);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MIN,               settingsStruct.aMinO2);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MAX,               settingsStruct.aMaxO2);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_CO_STATUS,            settingsStruct.aStatusCO);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_CO_MIN,               settingsStruct.aMinCO);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_CO_MAX,               settingsStruct.aMaxCO);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_NO_STATUS,            settingsStruct.aStatusNO);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_NO_MIN,               settingsStruct.aMinNO);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_NO_MAX,               settingsStruct.aMaxNO);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_NOX_STATUS,           settingsStruct.aStatusNOX);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_NOX_MIN,              settingsStruct.aMinNOX);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_NOX_MAX,              settingsStruct.aMaxNOX);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_SO2_STATUS,           settingsStruct.aStatusSO2);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_SO2_MIN,              settingsStruct.aMinSO2);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_SO2_MAX,              settingsStruct.aMaxSO2);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_TEMP_STATUS,          settingsStruct.aStatusTEMP);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_TEMP_MIN,             settingsStruct.aMinTEMP);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_TEMP_MAX,             settingsStruct.aMaxTEMP);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_OPP_STATUS,           settingsStruct.aStatusOPP);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_OPP_MIN,              settingsStruct.aMinOPP);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_OPP_MAX,              settingsStruct.aMaxOPP);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_STATUS,       settingsStruct.aStatusDUSTPM);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_MIN,          settingsStruct.aMinDUSTPM);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_MAX,          settingsStruct.aMaxDUSTPM);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_VEL_STATUS,           settingsStruct.aStatusVEL);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_VEL_MIN,              settingsStruct.aMinVEL);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_VEL_MAX,              settingsStruct.aMaxVEL);

        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_FLOW_STATUS,          settingsStruct.aStatusFLOW);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_FLOW_MIN,             settingsStruct.aMinFLOW);
        SETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_FLOW_MAX,             settingsStruct.aMaxFLOW);
    }
}
