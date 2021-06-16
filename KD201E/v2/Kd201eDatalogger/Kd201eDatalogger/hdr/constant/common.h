#ifndef COMMON_H
#define COMMON_H

#include <QThread>
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QString>

#include "pivariables.h"

#define KEY_STATION_NAME    QString("StationName")
#define KEY_STATION_ID      QString("StationID")
#define KEY_STATION_TYPE    QString("StationType")
#define KEY_STATION_LINK    QString("StationLink")
#define KEY_READ_INTERVAL   QString("StationInterval")
#define KEY_FTP_SERVER      QString("FtpServer")
#define KEY_FTP_USER        QString("FtpUser")
#define KEY_FTP_PASSWD      QString("FtpPasswd")
#define KEY_USE_TIME_HTML   QString("UseTimeHtml")

#define STATE_INVALID_ALL               0b00000000
#define STATE_VALID_STATION_NAME        0b00000001
#define STATE_VALID_STATION_ID          0b00000010
#define STATE_VALID_STATION_TYPE        0b00000100
#define STATE_VALID_STATION_LINK        0b00001000
#define STATE_VALID_INTERVAL            0b00010000
#define STATE_VALID_FTP_SERVER          0b00100000
#define STATE_VALID_FTP_USER            0b01000000
#define STATE_VALID_FTP_PASSWD          0b10000000
#define STATE_VALID_ALL                 0b11111111

#ifdef __linux__
    #define INI_CONFIG_FILE     "/usr/KD201E/config/kd201e.ini"
#elif _WIN32
    #define INI_CONFIG_FILE     "D://KD201E/config/kd201e.ini"
#endif

#define DLG_THR             qDebug() << "[" << QThread::currentThreadId() << "]"
#define DLG                 qDebug()

#define PATH_INI            ":/config/resources/config.ini"
#define PATH_WEB_SETTING    ":/web/resources/web/settingpage.html"
#define PATH_WEB_DATALOGGER ":/web/resources/web/KD201E.html"

#define MSG_UPDATE_STATUS   "update"

#define WRITE_FILE          true

#define TIME_RELOAD_INI     10000
#define TIME_LOAD_UNSEND    12345

inline uint8_t getSettingsState()
{
    uint8_t state = 0b00000000;
    if(kd201eSetting.m_stationName != "" && kd201eSetting.m_stationName != "")
        state |= STATE_VALID_STATION_NAME;

    if(kd201eSetting.m_stationID != "" && kd201eSetting.m_stationID != "")
        state |= STATE_VALID_STATION_ID;

    if(kd201eSetting.m_stationType != "" && kd201eSetting.m_stationType != "")
        state |= STATE_VALID_STATION_TYPE;

    if(kd201eSetting.m_stationLink != "" && kd201eSetting.m_stationLink != "")
        state |= STATE_VALID_STATION_LINK;

    if(kd201eSetting.m_readInterval != "" && kd201eSetting.m_readInterval != "")
        if(QString::fromStdString(kd201eSetting.m_readInterval).toInt() >= 1000)
            state |= STATE_VALID_INTERVAL;

    if(kd201eSetting.m_ftpServerIP != "" && kd201eSetting.m_ftpServerIP != "")
        state |= STATE_VALID_FTP_SERVER;

    if(kd201eSetting.m_ftpUser != "" && kd201eSetting.m_ftpUser != "")
        state |= STATE_VALID_FTP_USER;

    if(kd201eSetting.m_ftpPwd != "" && kd201eSetting.m_ftpPwd != "")
        state |= STATE_VALID_FTP_PASSWD;

    return state;
}

inline bool checkIniFile()
{
    if(QFile::exists(INI_CONFIG_FILE))
        return true;
    return false;
}

inline bool loadSettingFromFile()
{
    if (!checkIniFile())
        return false;

    QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
    QString temp;
    if (checkIniFile()) {
        settingFile.beginGroup("General");
        temp = settingFile.value(KEY_STATION_NAME).toString();
        kd201eSetting.m_stationName = temp.toStdString();

        temp = settingFile.value(KEY_STATION_ID).toString();
        kd201eSetting.m_stationID = temp.toStdString();

        temp = settingFile.value(KEY_STATION_TYPE).toString();
        kd201eSetting.m_stationType = temp.toStdString();

        temp = settingFile.value(KEY_STATION_LINK).toString();
        if (temp.size() >= 8 && (!temp.contains("http://")) && (!temp.contains("https://"))) {           //1.1.1.1
            temp = QString("http://%1").arg(temp);
        }
        kd201eSetting.m_stationLink = temp.toStdString();

        temp = settingFile.value(KEY_READ_INTERVAL).toString();
        if (temp.toInt() >= 1000 && temp.toInt() <= 12*60*60*1000) {    //1s -> 12h
            kd201eSetting.m_readInterval = temp.toStdString();
        }

        temp = settingFile.value(KEY_FTP_SERVER).toString();
        if (temp.size() >= 8 && (!temp.contains("ftp://")) && (!temp.contains("ftps://"))) {             //1.1.1.1
            temp.replace("ftp://", "");
            temp.replace("ftps://", "");
            temp.replace("/", "");
        }
        kd201eSetting.m_ftpServerIP = temp.toStdString();

        temp = settingFile.value(KEY_FTP_USER).toString();
        kd201eSetting.m_ftpUser = temp.toStdString();

        temp = settingFile.value(KEY_FTP_PASSWD).toString();
        kd201eSetting.m_ftpPwd = temp.toStdString();

        QString qtemp = settingFile.value(KEY_USE_TIME_HTML).toString();
        kd201eSetting.m_useTimeHtml = ((qtemp == "0") || (qtemp == "false")) ? false : true;

        settingFile.endGroup();

        DLG << QString("Loadded setting fromm file: %1,%2,%3,%4,%5,%6,%7,%8")
               .arg(QString::fromStdString(kd201eSetting.m_stationName))
               .arg(QString::fromStdString(kd201eSetting.m_stationID))
               .arg(QString::fromStdString(kd201eSetting.m_stationType))
               .arg(QString::fromStdString(kd201eSetting.m_stationLink))
               .arg(QString::fromStdString(kd201eSetting.m_readInterval))
               .arg(QString::fromStdString(kd201eSetting.m_ftpServerIP))
               .arg(QString::fromStdString(kd201eSetting.m_ftpUser))
               .arg(QString::fromStdString(kd201eSetting.m_ftpPwd));
        return true;
    }
    return false;
}

#endif // COMMON_H
