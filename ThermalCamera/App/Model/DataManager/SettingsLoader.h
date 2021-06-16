#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H

#include <QSettings>
#include <QDir>

#include "Common.h"

enum Settings {
    SETTINGS_GROUP_GENERAL,    
    SETTINGS_GENERAL_DEVICEID,
    SETTINGS_GENERAL_DEVICENAME,
    SETTINGS_GENERAL_DEVICETYPE,
    SETTINGS_GENERAL_THRESOLD_MAXTEMP,
    SETTINGS_GENERAL_THRESOLD_MINTEMP,
    SETTINGS_GENERAL_VERIFYTIME,
    SETTINGS_GENERAL_SERVERIP,
    SETTINGS_GENERAL_SERVERPORT,
};

const QHash<int, QString> settingsMapName = {
    {SETTINGS_GROUP_GENERAL,            "General"           },
    {SETTINGS_GENERAL_DEVICEID,         "deviceId"          },
    {SETTINGS_GENERAL_DEVICENAME,       "deviceName"        },
    {SETTINGS_GENERAL_DEVICETYPE,       "deviceType"        },
    {SETTINGS_GENERAL_THRESOLD_MAXTEMP, "thresoldMaxTemp"   },
    {SETTINGS_GENERAL_THRESOLD_MINTEMP, "thresoldMinTemp"   },
    {SETTINGS_GENERAL_VERIFYTIME,       "verifyTime"        },
    {SETTINGS_GENERAL_SERVERIP,         "serverIp"          },
    {SETTINGS_GENERAL_SERVERPORT,       "serverPort"        },
};

typedef struct {
    QString gDeviceId = "";
    QString gDeviceName = "";
    QString gDeviceType = "";
    QString gThresoldMaxTemp = "";
    QString gThresoldMinTemp = "";
    QString gVerifyTime = "";
    QString gServerIP = "";
    QString gServerPort = "";
} SettingsStruct;

class SettingsLoader
{
public:
    static void createSettingsFile(SettingsStruct *settingsStruct = nullptr);
    static SettingsStruct loadSettings();
    static bool saveSettings(SettingsStruct *settingsStruct);
    static bool exists();
    static void setValue(int group, int key, QString value);
    static QString getValue(int group, int key);
};

#endif // SETTINGSLOADER_H
