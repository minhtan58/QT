#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QDir>

#include "DataManager.h"
#include "Common.h"

enum Settings {
    SETTINGS_GROUP_GENERAL,
    SETTINGS_GENERAL_STATION_ID,
    SETTINGS_GENERAL_STATION_NAME,
    SETTINGS_GENERAL_SYSTEMTIME_UPDATE_AUTOMATIC,
    SETTINGS_GENERAL_RADIUS,

    SETTINGS_GROUP_SERIALPORT,
    SETTINGS_SERIALPORT_PORTNAME,
    SETTINGS_SERIALPORT_BAUDRATE,

    SETTINGS_GROUP_NETWORK_SERVER,
    SETTINGS_NETWORK_SERVER_IP,
    SETTINGS_NETWORK_SERVER_PORT,
    SETTINGS_NETWORK_SERVER_INTERVAL,

    SETTINGS_GROUP_NETWORK_FTP,
    SETTINGS_NETWORK_FTP_IP,
    SETTINGS_NETWORK_FTP_PORT,
    SETTINGS_NETWORK_FTP_USER,
    SETTINGS_NETWORK_FTP_PASSWORD,
    SETTINGS_NETWORK_FTP_INTERVAL,

    SETTINGS_GROUP_COEFFICIENT,
    SETTINGS_COEFFICIENT_O2,
    SETTINGS_COEFFICIENT_CO_AMP_PPM,
    SETTINGS_COEFFICIENT_CO_PPM_STD,
    SETTINGS_COEFFICIENT_NO_AMP_PPM,
    SETTINGS_COEFFICIENT_NO_PPM_STD,
    SETTINGS_COEFFICIENT_NOX,
    SETTINGS_COEFFICIENT_SO2,
    SETTINGS_COEFFICIENT_O2_AMP_2_PPM,

    SETTINGS_GROUP_ALARM,
    SETTINGS_ALARM_STATUS_O2,
    SETTINGS_ALARM_MIN_O2,
    SETTINGS_ALARM_MAX_O2,
    SETTINGS_ALARM_STATUS_CO,
    SETTINGS_ALARM_MIN_CO,
    SETTINGS_ALARM_MAX_CO,
    SETTINGS_ALARM_STATUS_NO,
    SETTINGS_ALARM_MIN_NO,
    SETTINGS_ALARM_MAX_NO,
    SETTINGS_ALARM_STATUS_NOX,
    SETTINGS_ALARM_MIN_NOX,
    SETTINGS_ALARM_MAX_NOX,
    SETTINGS_ALARM_STATUS_SO2,
    SETTINGS_ALARM_MIN_SO2,
    SETTINGS_ALARM_MAX_SO2,
    SETTINGS_ALARM_STATUS_TEMP,
    SETTINGS_ALARM_MIN_TEMP,
    SETTINGS_ALARM_MAX_TEMP,
    SETTINGS_ALARM_STATUS_OPP,
    SETTINGS_ALARM_MIN_OPP,
    SETTINGS_ALARM_MAX_OPP,
    SETTINGS_ALARM_STATUS_DUST_PM,
    SETTINGS_ALARM_MIN_DUST_PM,
    SETTINGS_ALARM_MAX_DUST_PM,
    SETTINGS_ALARM_STATUS_VEL,
    SETTINGS_ALARM_MIN_VEL,
    SETTINGS_ALARM_MAX_VEL,
    SETTINGS_ALARM_STATUS_FLOW,
    SETTINGS_ALARM_MIN_FLOW,
    SETTINGS_ALARM_MAX_FLOW,
};

const QHash<int, QString> settingsMapName = {
    {SETTINGS_GROUP_GENERAL,                "GeneralSettings"   },
    {SETTINGS_GENERAL_STATION_ID,           "stationId"         },
    {SETTINGS_GENERAL_STATION_NAME,         "stationName"       },
    {SETTINGS_GENERAL_SYSTEMTIME_UPDATE_AUTOMATIC,         "systemTimeAutoUpdate"       },
    {SETTINGS_GENERAL_RADIUS,               "radius"            },

    {SETTINGS_GROUP_SERIALPORT,             "SerialPort"        },
    {SETTINGS_SERIALPORT_PORTNAME,          "portName"          },
    {SETTINGS_SERIALPORT_BAUDRATE,          "baudrate"          },

    {SETTINGS_GROUP_NETWORK_SERVER,         "NetworkServer"     },
    {SETTINGS_NETWORK_SERVER_IP,            "serverIp"          },
    {SETTINGS_NETWORK_SERVER_PORT,          "serverPort"        },
    {SETTINGS_NETWORK_SERVER_INTERVAL,      "serverInterval"    },

    {SETTINGS_GROUP_NETWORK_FTP,            "NetworkFtp"        },
    {SETTINGS_NETWORK_FTP_IP,               "ftpIp"             },
    {SETTINGS_NETWORK_FTP_PORT,             "ftpPort"           },
    {SETTINGS_NETWORK_FTP_USER,             "ftpUser"           },
    {SETTINGS_NETWORK_FTP_PASSWORD,         "ftpPassword"       },
    {SETTINGS_NETWORK_FTP_INTERVAL,         "ftpInterval"       },

    {SETTINGS_GROUP_ALARM,                  "AlarmSettings"     },
    {SETTINGS_ALARM_STATUS_O2,              "alarmStatusO2"     },
    {SETTINGS_ALARM_MIN_O2,                 "alarmMinO2"        },
    {SETTINGS_ALARM_MAX_O2,                 "alarmMaxO2"        },
    {SETTINGS_ALARM_STATUS_CO,              "alarmStatusCO"     },
    {SETTINGS_ALARM_MIN_CO,                 "alarmMinCO"        },
    {SETTINGS_ALARM_MAX_CO,                 "alarmMaxCO"        },
    {SETTINGS_ALARM_STATUS_NO,              "alarmStatusNO"     },
    {SETTINGS_ALARM_MIN_NO,                 "alarmMinNO"        },
    {SETTINGS_ALARM_MAX_NO,                 "alarmMaxNO"        },
    {SETTINGS_ALARM_STATUS_NOX,             "alarmStatusNOX"    },
    {SETTINGS_ALARM_MIN_NOX,                "alarmMinNOX"       },
    {SETTINGS_ALARM_MAX_NOX,                "alarmMaxNOX"       },
    {SETTINGS_ALARM_STATUS_SO2,             "alarmStatusSO2"    },
    {SETTINGS_ALARM_MIN_SO2,                "alarmMinSO2"       },
    {SETTINGS_ALARM_MAX_SO2,                "alarmMaxSO2"       },
    {SETTINGS_ALARM_STATUS_TEMP,            "alarmStatusTEMP"   },
    {SETTINGS_ALARM_MIN_TEMP,               "alarmMinTEMP"      },
    {SETTINGS_ALARM_MAX_TEMP,               "alarmMaxTEMP"      },
    {SETTINGS_ALARM_STATUS_OPP,             "alarmStatusOPP"    },
    {SETTINGS_ALARM_MIN_OPP,                "alarmMinOPP"       },
    {SETTINGS_ALARM_MAX_OPP,                "alarmMaxOPP"       },
    {SETTINGS_ALARM_STATUS_DUST_PM,         "alarmStatusDUSTPM" },
    {SETTINGS_ALARM_MIN_DUST_PM,            "alarmMinDUSTPM"    },
    {SETTINGS_ALARM_MAX_DUST_PM,            "alarmMaxDUSTPM"    },
    {SETTINGS_ALARM_STATUS_VEL,             "alarmStatusVEL"    },
    {SETTINGS_ALARM_MIN_VEL,                "alarmMinVEL"       },
    {SETTINGS_ALARM_MAX_VEL,                "alarmMaxVEL"       },
    {SETTINGS_ALARM_STATUS_FLOW,            "alarmStatusFLOW"   },
    {SETTINGS_ALARM_MIN_FLOW,               "alarmMinFLOW"      },
    {SETTINGS_ALARM_MAX_FLOW,               "alarmMaxFLOW"      },
};

typedef struct
{
    QString gStationId;
    QString gStationName;
    QString gSystemTimeAutoUpdate;
    QString gRadius;
    QString spPortName;
    QString spBaudrate;
    QString nServerIp;
    QString nServerPort;
    QString nServerInterval;
    QString nFtpIp;
    QString nFtpPort;
    QString nFtpUser;
    QString nFtpPassword;
    QString nFtpInterval;
    QString aStatusO2;
    QString aMinO2;
    QString aMaxO2;
    QString aStatusCO;
    QString aMinCO;
    QString aMaxCO;
    QString aStatusNO;
    QString aMinNO;
    QString aMaxNO;
    QString aStatusNOX;
    QString aMinNOX;
    QString aMaxNOX;
    QString aStatusSO2;
    QString aMinSO2;
    QString aMaxSO2;
    QString aStatusTEMP;
    QString aMinTEMP;
    QString aMaxTEMP;
    QString aStatusOPP;
    QString aMinOPP;
    QString aMaxOPP;
    QString aStatusDUSTPM;
    QString aMinDUSTPM;
    QString aMaxDUSTPM;
    QString aStatusVEL;
    QString aMinVEL;
    QString aMaxVEL;
    QString aStatusFLOW;
    QString aMinFLOW;
    QString aMaxFLOW;
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
