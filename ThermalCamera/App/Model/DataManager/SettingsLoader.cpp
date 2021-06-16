#include "SettingsLoader.h"
#include "DPID.h"
#include "Defines.h"

void SettingsLoader::createSettingsFile(SettingsStruct *settingsStruct)
{
    QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
    bool isEmptyStruct = settingsStruct == nullptr;

    if(settingFile.isWritable()) {
        if(isEmptyStruct) {
            settingsStruct = new SettingsStruct();
        }

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_DEVICEID),          settingsStruct->gDeviceId);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_DEVICENAME),        settingsStruct->gDeviceName);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_DEVICETYPE),        settingsStruct->gDeviceType);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_THRESOLD_MAXTEMP),  settingsStruct->gThresoldMaxTemp);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_THRESOLD_MINTEMP),  settingsStruct->gThresoldMinTemp);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_VERIFYTIME),        settingsStruct->gVerifyTime);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_SERVERIP),          settingsStruct->gServerIP);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_SERVERPORT),        settingsStruct->gServerPort);
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
        QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);

        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
        settingsStruct.gDeviceId        = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_DEVICEID)).toString();
        settingsStruct.gDeviceName      = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_DEVICENAME)).toString();
        settingsStruct.gDeviceType      = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_DEVICETYPE)).toString();
        settingsStruct.gThresoldMaxTemp = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_THRESOLD_MAXTEMP)).toString();
        settingsStruct.gThresoldMinTemp = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_THRESOLD_MINTEMP)).toString();
        settingsStruct.gVerifyTime      = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_VERIFYTIME)).toString();
        settingsStruct.gServerIP        = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_SERVERIP)).toString();
        settingsStruct.gServerPort      = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_SERVERPORT)).toString();
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
    return QFile::exists(INI_CONFIG_FILE);
}

void SettingsLoader::setValue(int group, int key, QString value)
{
    QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
    settingFile.beginGroup(settingsMapName.value(group));
    if(settingsMapName.contains(group) && settingsMapName.contains(key))
        settingFile.setValue(settingsMapName.value(key), value);
    settingFile.endGroup();
}

QString SettingsLoader::getValue(int group, int key)
{
    QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
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
