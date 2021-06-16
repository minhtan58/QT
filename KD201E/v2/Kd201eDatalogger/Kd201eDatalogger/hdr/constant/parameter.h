#ifndef PARAMETER
#define PARAMETER

#include <QDebug>

#include "pivariables.h"

#define DATA_LINK           "http://45.124.93.149/data.html"
#define DLG_THR             qDebug() << "[" << QThread::currentThreadId() << "]"
#define DLG                 qDebug()

#define PATH_INI            ":/config/resources/config.ini"
#define PATH_WEB_SETTING    ":/web/resources/web/settingpage.html"
#define PATH_WEB_DATALOGGER ":/web/resources/web/KD201E.html"

#define INI_CONFIG_FILE     "/usr/KD201E/config/kd201e.ini"

#define MSG_UPDATE_STATUS   "update"
#define MSG_SET_INTERVAL    "interval"
#define TOKEN               QString(",")

#define INTERVAL_DEFAULT    3000

#define WRITE_FILE          true

#define KEY_STATION_NAME    QString("StationName")
#define KEY_STATION_ID      QString("StationID")
#define KEY_STATION_TYPE    QString("StationType")
#define KEY_STATION_LINK    QString("StationLink")
#define KEY_READ_INTERVAL   QString("StationInterval")
#define KEY_FTP_SERVER      QString("FtpServer")
#define KEY_FTP_USER        QString("FtpUser")
#define KEY_FTP_PASSWD      QString("FtpPasswd")

#define TIME_RELOAD_INI     10000
#define TIME_LOAD_UNSEND    10000

#endif // PARAMETER
