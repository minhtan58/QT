#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QDir>

#include "Common.h"
#include "Constants.h"

enum Settings {
    SETTINGS_GROUP_DEVICE,
    SETTINGS_DEVICE_CODE,
    SETTINGS_DEVICE_NAME,
    SETTINGS_DEVICE_LOCATION,
    SETTINGS_DEVICE_SYSTEMTIME_UPDATE_AUTOMATIC,
    SETTINGS_DEVICE_TYPE,

    SETTINGS_GROUP_SERIALPORT,
    SETTINGS_SERIALPORT_GPS_PORTNAME,
    SETTINGS_SERIALPORT_GPS_BAUDRATE,
    SETTINGS_SERIALPORT_SIM_PORTNAME,
    SETTINGS_SERIALPORT_SIM_BAUDRATE,
    SETTINGS_SERIALPORT_SENSOR_READ_INTERVAL,

    SETTINGS_GROUP_TELEMETRY,
    SETTINGS_TELEMETRY_GENERAL_SEND_TYPE,
    SETTINGS_TELEMETRY_GENERAL_CONTROL_TYPE,
    SETTINGS_TELEMETRY_GENERAL_SMS_NOTIFY,
    SETTINGS_TELEMETRY_GENERAL_SEND_INTERVAL,
    SETTINGS_TELEMETRY_INTERNET_NETWORK_TYPE,
    SETTINGS_TELEMETRY_INTERNET_PROTOCOL_TYPE,
    SETTINGS_TELEMETRY_INTERNET_SERVER1,
    SETTINGS_TELEMETRY_INTERNET_SERVER2
};

const QHash<int, QString> settingsMapName = {
    {SETTINGS_GROUP_DEVICE,                         "DeviceSettings"    },
    {SETTINGS_DEVICE_CODE,                          "deviceCode"        },
    {SETTINGS_DEVICE_NAME,                          "deviceName"        },
    {SETTINGS_DEVICE_LOCATION,                      "deviceLocation"    },
    {SETTINGS_DEVICE_SYSTEMTIME_UPDATE_AUTOMATIC,   "systemTimeAutoUpdate"},
    {SETTINGS_DEVICE_TYPE,                          "deviceType"        },

    {SETTINGS_GROUP_SERIALPORT,                     "SerialPort"        },
    {SETTINGS_SERIALPORT_GPS_PORTNAME,              "gpsPortName"       },
    {SETTINGS_SERIALPORT_GPS_BAUDRATE,              "gpsBaudrate"       },
    {SETTINGS_SERIALPORT_SIM_PORTNAME,              "simPortName"       },
    {SETTINGS_SERIALPORT_SIM_BAUDRATE,              "simBaudrate"       },
    {SETTINGS_SERIALPORT_SENSOR_READ_INTERVAL,      "sensorInterval"    },

    {SETTINGS_GROUP_TELEMETRY,                      "Telemetry"         },
    {SETTINGS_TELEMETRY_GENERAL_SEND_TYPE,          "sendType"          },
    {SETTINGS_TELEMETRY_GENERAL_CONTROL_TYPE,       "controlType"       },
    {SETTINGS_TELEMETRY_GENERAL_SMS_NOTIFY,         "smsNotify"         },
    {SETTINGS_TELEMETRY_GENERAL_SEND_INTERVAL,      "sendInterval"      },
    {SETTINGS_TELEMETRY_INTERNET_NETWORK_TYPE,      "internetNetworkType"   },
    {SETTINGS_TELEMETRY_INTERNET_PROTOCOL_TYPE,     "internetProtocolType"  },
    {SETTINGS_TELEMETRY_INTERNET_SERVER1,           "internetServer1"       },
    {SETTINGS_TELEMETRY_INTERNET_SERVER2,           "internetServer2"   },
};

typedef struct
{
    QString dDeviceCode = "";
    QString dDeviceName = "";
    QString dDeviceLocation = "";
    QString dSystemTimeAutoUpdate = "";
    QString dDeviceType = "";

    QString sGpsPortName = "";
    QString sGpsBaudrate = "";
    QString sSimPortName = "";
    QString sSimBaudrate = "";
    QString sSensorInterval = "";

    QString tgSendType = "";
    QString tgControlType = "";
    QString tgSmsNotify = "";
    QString tgSendInterval = "";

    QString tiNetworkType = "";
    QString tiProtocolType = "";
    QString tiServer1 = "";
    QString tiServer2 = "";
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
