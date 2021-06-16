#include "SettingsLoader.h"
#include "Datapool.h"

void SettingsLoader::createSettingsFile(SettingsStruct *settingsStruct)
{
    if(!exists()) {
        if(!QDir().exists(INI_CONFIG_FOLDER)) {
            if(!QDir().mkpath(QFileInfo(INI_CONFIG_FOLDER).absolutePath())) {
                DLOG("Can't create ini folder %s", INI_CONFIG_FOLDER);
            }
        }
        QFile fileWrite(INI_CONFIG_FILE);
        if(fileWrite.open(QIODevice::WriteOnly | QIODevice::Text)) {
            DLOG("Create %s", fileWrite.fileName().toStdString().data());
            fileWrite.close();
        } else {
            DLOG("Can't create %s", fileWrite.fileName().toStdString().data());
        }
    }

    if(!settingsStruct && exists()) {
        QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_PROVINCE_CODE),     "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_COMPANY_NAME),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_COMPANY_CODE),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_CODE),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_TYPE),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_HTML_SOURCE),       "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_HTML_READ_INTERVAL),"");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_IP),      "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PORT),    "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_USER),    "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PASSWD),  "");
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_TIME_USINGHTML),    "");
        settingFile.endGroup();
    } else if (settingsStruct && exists()) {
        QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_PROVINCE_CODE),     settingsStruct->gProvinceCode);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_COMPANY_NAME),      settingsStruct->gCompanyName);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_COMPANY_CODE),      settingsStruct->gCompanyCode);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME),      settingsStruct->gStationName);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_CODE),      settingsStruct->gStationCode);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_TYPE),      settingsStruct->gStationType);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_HTML_SOURCE),       settingsStruct->gHtmlSource);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_HTML_READ_INTERVAL),settingsStruct->gHtmlReadInterval);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_IP),      settingsStruct->gFtpServerIP);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PORT),    settingsStruct->gFtpServerPort);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_USER),    settingsStruct->gFtpServerUser);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PASSWD),  settingsStruct->gFtpServerPasswd);
        settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_TIME_USINGHTML),    settingsStruct->gTimeUsingHtml);
        settingFile.endGroup();
    }
}

SettingsStruct SettingsLoader::loadSettings()
{
    if(exists()) {
        SettingsStruct settingsStruct;
        QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
        settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
        settingsStruct.gProvinceCode        = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_PROVINCE_CODE)).toString();
        settingsStruct.gCompanyName         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_COMPANY_NAME)).toString();
        settingsStruct.gCompanyCode         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_COMPANY_CODE)).toString();
        settingsStruct.gStationName         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME)).toString();
        settingsStruct.gStationCode         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_STATION_CODE)).toString();
        settingsStruct.gStationType         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_STATION_TYPE)).toString();
        settingsStruct.gHtmlSource          = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_HTML_SOURCE)).toString();
        settingsStruct.gHtmlReadInterval    = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_HTML_READ_INTERVAL)).toString();
        settingsStruct.gFtpServerIP         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_IP)).toString();
        settingsStruct.gFtpServerPort       = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PORT)).toString();
        settingsStruct.gFtpServerUser       = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_USER)).toString();
        settingsStruct.gFtpServerPasswd     = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PASSWD)).toString();
        settingsStruct.gTimeUsingHtml       = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_TIME_USINGHTML)).toString();
        settingFile.endGroup();
        return settingsStruct;
    }
    return SettingsStruct {"", "" ,"" ,"" ,"", "", "", "", "", "", "", "", ""};
}

bool SettingsLoader::saveSettings(SettingsStruct *settingsStruct)
{
    if(exists()) {
        if(!settingsStruct) {
            QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_PROVINCE_CODE),     "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_COMPANY_NAME),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_COMPANY_CODE),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_CODE),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_STATION_TYPE),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_HTML_SOURCE),       "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_HTML_READ_INTERVAL),"");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_IP),      "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PORT),    "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_USER),    "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PASSWD),  "");
            settingFile.setValue(settingsMapName.value(SETTINGS_GENERAL_TIME_USINGHTML),    "");
            settingFile.endGroup();
        } else if (settingsStruct) {
            QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
            settingFile.beginGroup(settingsMapName.value(SETTINGS_GROUP_GENERAL));
            settingsStruct->gProvinceCode        = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_PROVINCE_CODE)).toString();
            settingsStruct->gCompanyName         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_COMPANY_NAME)).toString();
            settingsStruct->gCompanyCode         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_COMPANY_CODE)).toString();
            settingsStruct->gStationName         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_STATION_NAME)).toString();
            settingsStruct->gStationCode         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_STATION_CODE)).toString();
            settingsStruct->gStationType         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_STATION_TYPE)).toString();
            settingsStruct->gHtmlSource          = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_HTML_SOURCE)).toString();
            settingsStruct->gHtmlReadInterval    = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_HTML_READ_INTERVAL)).toString();
            settingsStruct->gFtpServerIP         = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_IP)).toString();
            settingsStruct->gFtpServerPort       = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PORT)).toString();
            settingsStruct->gFtpServerUser       = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_USER)).toString();
            settingsStruct->gFtpServerPasswd     = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_FTPSERVER_PASSWD)).toString();
            settingsStruct->gTimeUsingHtml       = settingFile.value(settingsMapName.value(SETTINGS_GENERAL_TIME_USINGHTML)).toString();
            settingFile.endGroup();
        }
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
    if(settingFile.contains(settingsMapName.value(key))
            && settingFile.value(settingsMapName.value(key)).toString() != value) {
        settingFile.setValue(settingsMapName.value(key), value);
    }
    settingFile.endGroup();
}

QString SettingsLoader::getValue(int group, int key)
{
    QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
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

void SettingsLoader::loadIniSettings()
{
    if(!SettingsLoader::exists())
        SettingsLoader::createSettingsFile();
    else {
        SettingsStruct settingsStruct = SettingsLoader::loadSettings();
        SETDPDATA(KD201EEnum::DP_SETTINGS_PROVINCE_CODE,     settingsStruct.gProvinceCode);
        SETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_NAME,      settingsStruct.gCompanyName);
        SETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_CODE,      settingsStruct.gCompanyCode);
        SETDPDATA(KD201EEnum::DP_SETTINGS_STATION_NAME,      settingsStruct.gStationName);
        SETDPDATA(KD201EEnum::DP_SETTINGS_STATION_CODE,      settingsStruct.gStationCode);
        SETDPDATA(KD201EEnum::DP_SETTINGS_STATION_TYPE,      settingsStruct.gStationType);

        QString htmlSource = settingsStruct.gHtmlSource;
        if(htmlSource.size() >= 8 && (!htmlSource.contains("http://")) && (!htmlSource.contains("https://"))) {
            htmlSource = QString("http://%1").arg(htmlSource);
        }
        SETDPDATA(KD201EEnum::DP_SETTINGS_HTML_SOURCE,       htmlSource);
        SETDPDATA(KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL,settingsStruct.gHtmlReadInterval);

        QString ftpServerIP = settingsStruct.gFtpServerIP;
        if (ftpServerIP.size() >= 8 && (ftpServerIP.contains("ftp://")) && (ftpServerIP.contains("ftps://"))) {             //1.1.1.1
            ftpServerIP.replace("ftp://", "");
            ftpServerIP.replace("ftps://", "");
            ftpServerIP.replace("/", "");
        }
        SETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_IP,     ftpServerIP);

        QString ftpServerPort = settingsStruct.gFtpServerPort;
        ftpServerPort = ftpServerPort.isEmpty() ? QString::number(21) : ftpServerPort;
        SETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PORT,   ftpServerPort);

        SETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_USER,    settingsStruct.gFtpServerUser);
        SETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PASSWD,  settingsStruct.gFtpServerPasswd);

        SETDPDATA(KD201EEnum::DP_SETTINGS_TIME_USINGHTML, settingsStruct.gTimeUsingHtml);

        DLOG("Loadded: %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
             GETDPDATA(KD201EEnum::DP_SETTINGS_PROVINCE_CODE).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_NAME).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_CODE).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_NAME).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_CODE).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_TYPE).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_SOURCE).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_IP).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PORT).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_USER).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PASSWD).toStdString().data(),
             GETDPDATA(KD201EEnum::DP_SETTINGS_TIME_USINGHTML).toStdString().data());
    }
}
