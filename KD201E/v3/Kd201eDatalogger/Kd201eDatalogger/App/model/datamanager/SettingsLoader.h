#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H

#include <QSettings>
#include <QDir>

#include "Common.h"

/* settings state uint16_t */
#define STATE_INVALID_ALL               0b0000000000000000
#define STATE_VALID_1                   0b0000000000000001
#define STATE_VALID_PROVINCE_CODE       STATE_VALID_1
#define STATE_VALID_COMPANY_NAME        STATE_VALID_1 << 1
#define STATE_VALID_COMPANY_CODE        STATE_VALID_1 << 2
#define STATE_VALID_STATION_NAME        STATE_VALID_1 << 3
#define STATE_VALID_STATION_CODE        STATE_VALID_1 << 4
#define STATE_VALID_STATION_TYPE        STATE_VALID_1 << 5
#define STATE_VALID_HTML_SOURCE         STATE_VALID_1 << 6
#define STATE_VALID_HTML_READ_INTERVAL  STATE_VALID_1 << 7
#define STATE_VALID_FTPSERVER_IP        STATE_VALID_1 << 8
#define STATE_VALID_FTPSERVER_PORT      STATE_VALID_1 << 9
#define STATE_VALID_FTPSERVER_USER      STATE_VALID_1 << 10
#define STATE_VALID_FTPSERVER_PASSWD    STATE_VALID_1 << 11
#define STATE_VALID_TIME_USINGHTML      STATE_VALID_1 << 12
#define STATE_VALID_ALL                 0b0000111111111111

enum Settings {
    SETTINGS_GROUP_GENERAL,
    SETTINGS_GENERAL_PROVINCE_CODE,
    SETTINGS_GENERAL_COMPANY_NAME,
    SETTINGS_GENERAL_COMPANY_CODE,
    SETTINGS_GENERAL_STATION_NAME,
    SETTINGS_GENERAL_STATION_CODE,
    SETTINGS_GENERAL_STATION_TYPE,
    SETTINGS_GENERAL_HTML_SOURCE,
    SETTINGS_GENERAL_HTML_READ_INTERVAL,
    SETTINGS_GENERAL_FTPSERVER_IP,
    SETTINGS_GENERAL_FTPSERVER_PORT,
    SETTINGS_GENERAL_FTPSERVER_USER,
    SETTINGS_GENERAL_FTPSERVER_PASSWD,
    SETTINGS_GENERAL_TIME_USINGHTML
};

const QHash<int, QString> settingsMapName = {
    {SETTINGS_GROUP_GENERAL,                "General"},
    {SETTINGS_GENERAL_PROVINCE_CODE,        "provinceCode"},
    {SETTINGS_GENERAL_COMPANY_NAME,         "companyName"},
    {SETTINGS_GENERAL_COMPANY_CODE,         "companyCode"},
    {SETTINGS_GENERAL_STATION_NAME,         "stationName"},
    {SETTINGS_GENERAL_STATION_CODE,         "stationCode"},
    {SETTINGS_GENERAL_STATION_TYPE,         "stationType"},
    {SETTINGS_GENERAL_HTML_SOURCE,          "htmlSource"},
    {SETTINGS_GENERAL_HTML_READ_INTERVAL,   "htmlReadInterval"},
    {SETTINGS_GENERAL_FTPSERVER_IP,         "ftpServerIP"},
    {SETTINGS_GENERAL_FTPSERVER_PORT,       "ftpServerPort"},
    {SETTINGS_GENERAL_FTPSERVER_USER,       "ftpServerUser"},
    {SETTINGS_GENERAL_FTPSERVER_PASSWD,     "ftpServerPasswd"},
    {SETTINGS_GENERAL_TIME_USINGHTML,       "timeUsingHtml"},
};

typedef struct
{
    QString gProvinceCode;
    QString gCompanyName;
    QString gCompanyCode;
    QString gStationName;
    QString gStationCode;
    QString gStationType;
    QString gHtmlSource;
    QString gHtmlReadInterval;
    QString gFtpServerIP;
    QString gFtpServerPort;
    QString gFtpServerUser;
    QString gFtpServerPasswd;
    QString gTimeUsingHtml;
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

    /**
     * @brief loadIniSettings load and set to datapool
     */
    static void loadIniSettings();
};

#endif // SETTINGSLOADER_H
