#include "SettingsLoader.h"

void SettingsLoader::createSettingsFile(SettingsStruct *settingsStruct)
{
    if(!exists()) {
        if(!QDir().exists(CEMS_SETTINGS_FOLDERPATH)) {
            if(!QDir().mkpath(QFileInfo(CEMS_SETTINGS_FOLDERPATH).absolutePath())) {
                DLOG("can't create storage folder %s", CEMS_SETTINGS_FOLDERPATH);
            }
        }
        QFile fileWrite(CEMS_SETTINGS_FILENAME);
        if(fileWrite.open(QIODevice::WriteOnly | QIODevice::Text)) {
            DLOG("Create %s", fileWrite.fileName().toStdString().data());
            fileWrite.close();
        } else {
            DLOG("Can't create %s", fileWrite.fileName().toStdString().data());
        }

    }

    if(!settingsStruct && exists()) {
        QSettings settingFile(CEMS_SETTINGS_FILENAME, QSettings::IniFormat);

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_ID),        "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_SYSTEMTIME_UPDATE_AUTOMATIC),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_RADIUS),            "");
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_SERIALPORT));
        settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_PORTNAME),       "");
        settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_BAUDRATE),       "");
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_SERVER));
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_IP),         "");
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_PORT),       "");
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_INTERVAL),   "");
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_FTP));
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_IP),            "");
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_PORT),          "");
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_USER),          "");
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_PASSWORD),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_INTERVAL),      "");
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_ALARM));
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_O2),           "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_O2),              "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_O2),              "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_CO),           "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_CO),              "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_CO),              "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_NO),           "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_NO),              "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_NO),              "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_NOX),          "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_NOX),             "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_NOX),             "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_SO2),          "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_SO2),             "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_SO2),             "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_TEMP),         "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_TEMP),            "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_TEMP),            "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_OPP),          "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_OPP),             "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_OPP),             "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_DUST_PM),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_DUST_PM),         "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_DUST_PM),         "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_VEL),          "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_VEL),             "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_VEL),             "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_FLOW),         "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_FLOW),            "");
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_FLOW),            "");
        settingFile.endGroup();
    } else if (settingsStruct && exists()) {
        QSettings settingFile(CEMS_SETTINGS_FILENAME, QSettings::IniFormat);
        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_ID),        settingsStruct->gStationId);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME),      settingsStruct->gStationName);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_SYSTEMTIME_UPDATE_AUTOMATIC),      settingsStruct->gSystemTimeAutoUpdate);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_RADIUS),            settingsStruct->gRadius);
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_SERIALPORT));
        settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_PORTNAME),       settingsStruct->spPortName);
        settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_BAUDRATE),       settingsStruct->spBaudrate);
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_SERVER));
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_IP),         settingsStruct->nServerIp);
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_PORT),       settingsStruct->nServerPort);
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_INTERVAL),   settingsStruct->nServerInterval);
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_FTP));
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_IP),            settingsStruct->nFtpIp);
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_PORT),          settingsStruct->nFtpPort);
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_USER),          settingsStruct->nFtpUser);
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_PASSWORD),      settingsStruct->nFtpPassword);
        settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_INTERVAL),      settingsStruct->nFtpInterval);
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_ALARM));
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_O2),           settingsStruct->aStatusO2);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_O2),              settingsStruct->aMinO2);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_O2),              settingsStruct->aMaxO2);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_CO),           settingsStruct->aStatusCO);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_CO),              settingsStruct->aMinCO);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_CO),              settingsStruct->aMaxCO);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_NO),           settingsStruct->aStatusNO);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_NO),              settingsStruct->aMinNO);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_NO),              settingsStruct->aMaxNO);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_NOX),          settingsStruct->aStatusNOX);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_NOX),             settingsStruct->aMinNOX);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_NOX),             settingsStruct->aMaxNOX);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_SO2),          settingsStruct->aStatusSO2);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_SO2),             settingsStruct->aMinSO2);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_SO2),             settingsStruct->aMaxSO2);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_TEMP),         settingsStruct->aStatusTEMP);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_TEMP),            settingsStruct->aMinTEMP);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_TEMP),            settingsStruct->aMaxTEMP);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_OPP),          settingsStruct->aStatusOPP);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_OPP),             settingsStruct->aMinOPP);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_OPP),             settingsStruct->aMaxOPP);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_DUST_PM),      settingsStruct->aStatusDUSTPM);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_DUST_PM),         settingsStruct->aMinDUSTPM);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_DUST_PM),         settingsStruct->aMaxDUSTPM);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_VEL),          settingsStruct->aStatusVEL);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_VEL),             settingsStruct->aMinVEL);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_VEL),             settingsStruct->aMaxVEL);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_FLOW),         settingsStruct->aStatusFLOW);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_FLOW),            settingsStruct->aMinFLOW);
        settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_FLOW),            settingsStruct->aMaxFLOW);
        settingFile.endGroup();
    }
}

SettingsStruct SettingsLoader::loadSettings()
{
    if(exists()) {
        SettingsStruct settingsStruct;
        QSettings settingFile(CEMS_SETTINGS_FILENAME, QSettings::IniFormat);

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
        settingsStruct.gStationId = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_STATION_ID)).toString();
        settingsStruct.gStationName = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME)).toString();
        settingsStruct.gSystemTimeAutoUpdate = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_SYSTEMTIME_UPDATE_AUTOMATIC)).toString();
        settingsStruct.gRadius = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_RADIUS)).toString();
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_SERIALPORT));
        settingsStruct.spPortName = settingFile.value(settingsMapName.value(SETTINGS_SERIALPORT_PORTNAME)).toString();
        settingsStruct.spBaudrate = settingFile.value(settingsMapName.value(SETTINGS_SERIALPORT_BAUDRATE)).toString();
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_SERVER));
        settingsStruct.nServerIp = settingFile.value(settingsMapName.value(SETTINGS_NETWORK_SERVER_IP)).toString();
        settingsStruct.nServerPort = settingFile.value(settingsMapName.value(SETTINGS_NETWORK_SERVER_PORT)).toString();
        settingsStruct.nServerInterval = settingFile.value(settingsMapName.value(SETTINGS_NETWORK_SERVER_INTERVAL)).toString();
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_FTP));
        settingsStruct.nFtpIp = settingFile.value(settingsMapName.value(SETTINGS_NETWORK_FTP_IP)).toString();
        settingsStruct.nFtpPort = settingFile.value(settingsMapName.value(SETTINGS_NETWORK_FTP_PORT)).toString();
        settingsStruct.nFtpUser = settingFile.value(settingsMapName.value(SETTINGS_NETWORK_FTP_USER)).toString();
        settingsStruct.nFtpPassword = settingFile.value(settingsMapName.value(SETTINGS_NETWORK_FTP_PASSWORD)).toString();
        settingsStruct.nFtpInterval = settingFile.value(settingsMapName.value(SETTINGS_NETWORK_FTP_INTERVAL)).toString();
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_ALARM));
        settingsStruct.aStatusO2 = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_O2)).toString();
        settingsStruct.aMinO2 = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_O2)).toString();
        settingsStruct.aMaxO2 = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_O2)).toString();
        settingsStruct.aStatusCO = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_CO)).toString();
        settingsStruct.aMinCO = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_CO)).toString();
        settingsStruct.aMaxCO = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_CO)).toString();
        settingsStruct.aStatusNO = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_NO)).toString();
        settingsStruct.aMinNO = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_NO)).toString();
        settingsStruct.aMaxNO = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_NO)).toString();
        settingsStruct.aStatusNOX = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_NOX)).toString();
        settingsStruct.aMinNOX = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_NOX)).toString();
        settingsStruct.aMaxNOX = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_NOX)).toString();
        settingsStruct.aStatusSO2 = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_SO2)).toString();
        settingsStruct.aMinSO2 = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_SO2)).toString();
        settingsStruct.aMaxSO2 = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_SO2)).toString();
        settingsStruct.aStatusTEMP = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_TEMP)).toString();
        settingsStruct.aMinTEMP = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_TEMP)).toString();
        settingsStruct.aMaxTEMP = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_TEMP)).toString();
        settingsStruct.aStatusOPP = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_OPP)).toString();
        settingsStruct.aMinOPP = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_OPP)).toString();
        settingsStruct.aMaxOPP = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_OPP)).toString();
        settingsStruct.aStatusDUSTPM = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_DUST_PM)).toString();
        settingsStruct.aMinDUSTPM = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_DUST_PM)).toString();
        settingsStruct.aMaxDUSTPM = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_DUST_PM)).toString();
        settingsStruct.aStatusVEL = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_VEL)).toString();
        settingsStruct.aMinVEL = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_VEL)).toString();
        settingsStruct.aMaxVEL = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_VEL)).toString();
        settingsStruct.aStatusFLOW = settingFile.value(settingsMapName.value(SETTINGS_ALARM_STATUS_FLOW)).toString();
        settingsStruct.aMinFLOW = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MIN_FLOW)).toString();
        settingsStruct.aMaxFLOW = settingFile.value(settingsMapName.value(SETTINGS_ALARM_MAX_FLOW)).toString();
        settingFile.endGroup();

        return settingsStruct;
    }
    return SettingsStruct {"", "" ,"" ,"" ,"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
}

bool SettingsLoader::saveSettings(SettingsStruct *settingsStruct)
{
    if(exists()) {
        if(!settingsStruct) {
            QSettings settingFile(CEMS_SETTINGS_FILENAME, QSettings::IniFormat);

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_ID),        "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_SYSTEMTIME_UPDATE_AUTOMATIC),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_RADIUS),            "");
            settingFile.endGroup();

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_SERIALPORT));
            settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_PORTNAME),       "");
            settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_BAUDRATE),       "");
            settingFile.endGroup();

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_SERVER));
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_IP),         "");
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_PORT),       "");
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_INTERVAL),   "");
            settingFile.endGroup();

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_FTP));
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_IP),            "");
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_PORT),          "");
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_USER),          "");
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_PASSWORD),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_INTERVAL),      "");
            settingFile.endGroup();

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_ALARM));
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_O2),           "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_O2),              "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_O2),              "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_CO),           "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_CO),              "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_CO),              "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_NO),           "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_NO),              "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_NO),              "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_NOX),          "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_NOX),             "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_NOX),             "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_SO2),          "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_SO2),             "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_SO2),             "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_TEMP),         "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_TEMP),            "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_TEMP),            "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_OPP),          "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_OPP),             "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_OPP),             "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_DUST_PM),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_DUST_PM),         "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_DUST_PM),         "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_VEL),          "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_VEL),             "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_VEL),             "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_FLOW),         "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_FLOW),            "");
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_FLOW),            "");
            settingFile.endGroup();
        } else if (settingsStruct) {
            QSettings settingFile(CEMS_SETTINGS_FILENAME, QSettings::IniFormat);

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_ID),        settingsStruct->gStationId);
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME),      settingsStruct->gStationName);
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_SYSTEMTIME_UPDATE_AUTOMATIC),      settingsStruct->gSystemTimeAutoUpdate);
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_RADIUS),            settingsStruct->gRadius);
            settingFile.endGroup();

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_SERIALPORT));
            settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_PORTNAME),       settingsStruct->spPortName);
            settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_BAUDRATE),       settingsStruct->spBaudrate);
            settingFile.endGroup();

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_SERVER));
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_IP),         settingsStruct->nServerIp);
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_PORT),       settingsStruct->nServerPort);
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_SERVER_INTERVAL),   settingsStruct->nServerInterval);
            settingFile.endGroup();

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_NETWORK_FTP));
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_IP),            settingsStruct->nFtpIp);
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_PORT),          settingsStruct->nFtpPort);
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_USER),          settingsStruct->nFtpUser);
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_PASSWORD),      settingsStruct->nFtpPassword);
            settingFile.setValue(settingsMapName.value(SETTINGS_NETWORK_FTP_INTERVAL),      settingsStruct->nFtpInterval);
            settingFile.endGroup();

            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_ALARM));
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_O2),           settingsStruct->aStatusO2);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_O2),              settingsStruct->aMinO2);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_O2),              settingsStruct->aMaxO2);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_CO),           settingsStruct->aStatusCO);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_CO),              settingsStruct->aMinCO);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_CO),              settingsStruct->aMaxCO);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_NO),           settingsStruct->aStatusNO);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_NO),              settingsStruct->aMinNO);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_NO),              settingsStruct->aMaxNO);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_NOX),          settingsStruct->aStatusNOX);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_NOX),             settingsStruct->aMinNOX);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_NOX),             settingsStruct->aMaxNOX);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_SO2),          settingsStruct->aStatusSO2);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_SO2),             settingsStruct->aMinSO2);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_SO2),             settingsStruct->aMaxSO2);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_TEMP),         settingsStruct->aStatusTEMP);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_TEMP),            settingsStruct->aMinTEMP);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_TEMP),            settingsStruct->aMaxTEMP);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_OPP),          settingsStruct->aStatusOPP);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_OPP),             settingsStruct->aMinOPP);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_OPP),             settingsStruct->aMaxOPP);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_DUST_PM),      settingsStruct->aStatusDUSTPM);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_DUST_PM),         settingsStruct->aMinDUSTPM);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_DUST_PM),         settingsStruct->aMaxDUSTPM);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_VEL),          settingsStruct->aStatusVEL);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_VEL),             settingsStruct->aMinVEL);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_VEL),             settingsStruct->aMaxVEL);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_STATUS_FLOW),         settingsStruct->aStatusFLOW);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MIN_FLOW),            settingsStruct->aMinFLOW);
            settingFile.setValue(settingsMapName.value(SETTINGS_ALARM_MAX_FLOW),            settingsStruct->aMaxFLOW);
            settingFile.endGroup();
        }
        return true;
    }
    return false;
}

bool SettingsLoader::exists()
{
    return QFile::exists(CEMS_SETTINGS_FILENAME);
}

void SettingsLoader::setValue(int group, int key, QString value)
{
    QSettings settingFile(CEMS_SETTINGS_FILENAME, QSettings::IniFormat);
    settingFile.beginGroup(settingsMapName.value(group));
//    if(settingFile.contains(settingsMapName.value(key)) && settingFile.value(settingsMapName.value(key)).toString() != value)
    if(settingsMapName.contains(group) && settingsMapName.contains(key)) {
        settingFile.setValue(settingsMapName.value(key), value);
    }
    settingFile.endGroup();
}

QString SettingsLoader::getValue(int group, int key)
{
    QSettings settingFile(CEMS_SETTINGS_FILENAME, QSettings::IniFormat);
    if(!settingsMapName.contains(key) || (settingsMapName.contains(key) && !settingFile.contains(settingsMapName.value(key)))) {
        DLOG("Settings File haven't key %d", key);
        return "";
    }

    QString rvalue;
    settingFile.beginGroup(settingsMapName.value(group));
    rvalue = settingFile.value(settingsMapName.value(key)).toString();
    settingFile.endGroup();
    return rvalue;
}
