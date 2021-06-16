#include "SettingsLoader.h"

void SettingsLoader::createSettingsFile(SettingsStruct *settingsStruct)
{
    QSettings settingFile(PH_INI_FILENAME, QSettings::IniFormat);
    bool isEmptyStruct = settingsStruct == nullptr;

    if(settingFile.isWritable()) {
        if(isEmptyStruct) {
            settingsStruct = new SettingsStruct();
        }

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_DEVICE));
        settingFile.setValue(settingsMapName.value(SETTINGS_DEVICE_CODE),                       settingsStruct->dDeviceCode);
        settingFile.setValue(settingsMapName.value(SETTINGS_DEVICE_NAME),                       settingsStruct->dDeviceName);
        settingFile.setValue(settingsMapName.value(SETTINGS_DEVICE_LOCATION),                   settingsStruct->dDeviceLocation);
        settingFile.setValue(settingsMapName.value(SETTINGS_DEVICE_SYSTEMTIME_UPDATE_AUTOMATIC),settingsStruct->dSystemTimeAutoUpdate);
        settingFile.setValue(settingsMapName.value(SETTINGS_DEVICE_TYPE),                       settingsStruct->dDeviceType);
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_SERIALPORT));
        settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_GPS_PORTNAME),           settingsStruct->sGpsPortName);
        settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_GPS_BAUDRATE),           settingsStruct->sGpsBaudrate);
        settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_SIM_PORTNAME),           settingsStruct->sSimPortName);
        settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_SIM_BAUDRATE),           settingsStruct->sSimBaudrate);
        settingFile.setValue(settingsMapName.value(SETTINGS_SERIALPORT_SENSOR_READ_INTERVAL),   settingsStruct->sSensorInterval);
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_TELEMETRY));
        settingFile.setValue(settingsMapName.value(SETTINGS_TELEMETRY_GENERAL_SEND_TYPE),       settingsStruct->tgSendType);
        settingFile.setValue(settingsMapName.value(SETTINGS_TELEMETRY_GENERAL_CONTROL_TYPE),    settingsStruct->tgControlType);
        settingFile.setValue(settingsMapName.value(SETTINGS_TELEMETRY_GENERAL_SMS_NOTIFY),      settingsStruct->tgSmsNotify);
        settingFile.setValue(settingsMapName.value(SETTINGS_TELEMETRY_GENERAL_SEND_INTERVAL),   settingsStruct->tgSendInterval);
        settingFile.setValue(settingsMapName.value(SETTINGS_TELEMETRY_INTERNET_NETWORK_TYPE),   settingsStruct->tiNetworkType);
        settingFile.setValue(settingsMapName.value(SETTINGS_TELEMETRY_INTERNET_PROTOCOL_TYPE),  settingsStruct->tiProtocolType);
        settingFile.setValue(settingsMapName.value(SETTINGS_TELEMETRY_INTERNET_SERVER1),        settingsStruct->tiServer1);
        settingFile.setValue(settingsMapName.value(SETTINGS_TELEMETRY_INTERNET_SERVER2),        settingsStruct->tiServer2);
        settingFile.endGroup();

        if(isEmptyStruct) {
            delete settingsStruct;
            settingsStruct = nullptr;
        }
    } else {
        DLOG("Can't create configuration file");
    }
}

SettingsStruct SettingsLoader::loadSettings()
{
    SettingsStruct settingsStruct;
    if(exists()) {
        DLOG("Configuration file loadding...");
        QSettings settingFile(PH_INI_FILENAME, QSettings::IniFormat);

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_DEVICE));
        settingsStruct.dDeviceCode              = settingFile.value(settingsMapName.value(SETTINGS_DEVICE_CODE)).toString();
        settingsStruct.dDeviceName              = settingFile.value(settingsMapName.value(SETTINGS_DEVICE_NAME)).toString();
        settingsStruct.dDeviceLocation          = settingFile.value(settingsMapName.value(SETTINGS_DEVICE_LOCATION)).toString();
        settingsStruct.dSystemTimeAutoUpdate    = settingFile.value(settingsMapName.value(SETTINGS_DEVICE_SYSTEMTIME_UPDATE_AUTOMATIC)).toString();
        settingsStruct.dDeviceType              = settingFile.value(settingsMapName.value(SETTINGS_DEVICE_TYPE)).toString();
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_SERIALPORT));
        settingsStruct.sGpsPortName     = settingFile.value(settingsMapName.value(SETTINGS_SERIALPORT_GPS_PORTNAME)).toString();
        settingsStruct.sGpsBaudrate     = settingFile.value(settingsMapName.value(SETTINGS_SERIALPORT_GPS_BAUDRATE)).toString();
        settingsStruct.sSimPortName     = settingFile.value(settingsMapName.value(SETTINGS_SERIALPORT_SIM_PORTNAME)).toString();
        settingsStruct.sSimBaudrate     = settingFile.value(settingsMapName.value(SETTINGS_SERIALPORT_SIM_BAUDRATE)).toString();
        settingsStruct.sSensorInterval  = settingFile.value(settingsMapName.value(SETTINGS_SERIALPORT_SENSOR_READ_INTERVAL)).toString();
        settingFile.endGroup();

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_TELEMETRY));
        settingsStruct.tgSendType       = settingFile.value(settingsMapName.value(SETTINGS_TELEMETRY_GENERAL_SEND_TYPE)).toString();
        settingsStruct.tgControlType    = settingFile.value(settingsMapName.value(SETTINGS_TELEMETRY_GENERAL_CONTROL_TYPE)).toString();
        settingsStruct.tgSmsNotify      = settingFile.value(settingsMapName.value(SETTINGS_TELEMETRY_GENERAL_SMS_NOTIFY)).toString();
        settingsStruct.tgSendInterval   = settingFile.value(settingsMapName.value(SETTINGS_TELEMETRY_GENERAL_SEND_INTERVAL)).toString();
        settingsStruct.tiNetworkType    = settingFile.value(settingsMapName.value(SETTINGS_TELEMETRY_INTERNET_NETWORK_TYPE)).toString();
        settingsStruct.tiProtocolType   = settingFile.value(settingsMapName.value(SETTINGS_TELEMETRY_INTERNET_PROTOCOL_TYPE)).toString();
        settingsStruct.tiServer1        = settingFile.value(settingsMapName.value(SETTINGS_TELEMETRY_INTERNET_SERVER1)).toString();
        settingsStruct.tiServer2        = settingFile.value(settingsMapName.value(SETTINGS_TELEMETRY_INTERNET_SERVER2)).toString();
        settingFile.endGroup();

        DLOG("Configuration file load successful");
    } else {
        DLOG("Configuration file not exist");
    }
    return settingsStruct;
}

bool SettingsLoader::saveSettings(SettingsStruct *settingsStruct)
{
    if(exists()) {
        createSettingsFile(settingsStruct);
        return true;
    }
    return false;
}

bool SettingsLoader::exists()
{
    return QFile::exists(PH_INI_FILENAME);
}

void SettingsLoader::setValue(int group, int key, QString value)
{
    QSettings settingFile(PH_INI_FILENAME, QSettings::IniFormat);
    settingFile.beginGroup(settingsMapName.value(group));
    if(settingsMapName.contains(group) && settingsMapName.contains(key))
        settingFile.setValue(settingsMapName.value(key), value);
    settingFile.endGroup();
}

QString SettingsLoader::getValue(int group, int key)
{
    QSettings settingFile(PH_INI_FILENAME, QSettings::IniFormat);
    if(!settingsMapName.contains(key) || (settingsMapName.contains(key) && !settingFile.contains(settingsMapName.value(key)))) {
        DLOG("Settings File haven't key: %d", key);
        return "";
    }

    QString rvalue;
    settingFile.beginGroup(settingsMapName.value(group));
    rvalue = settingFile.value(settingsMapName.value(key)).toString();
    settingFile.endGroup();
    return rvalue;
}
