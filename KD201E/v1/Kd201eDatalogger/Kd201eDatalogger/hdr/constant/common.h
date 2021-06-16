#ifndef COMMON_H
#define COMMON_H

#include <QThread>
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QString>
#include <QDateTime>
#include <thread>

#include "kd201eenum.h"
#include "Datapool.h"

#define KEY_STATION_NAME    QString("StationName")
#define KEY_COMPANY_NAME    QString("CompanyName")
#define KEY_STATION_TYPE    QString("StationType")
#define KEY_STATION_LINK    QString("StationLink")
#define KEY_READ_INTERVAL   QString("StationInterval")
#define KEY_FTP_SERVER      QString("FtpServer")
#define KEY_FTP_USER        QString("FtpUser")
#define KEY_FTP_PASSWD      QString("FtpPasswd")
#define KEY_USE_TIME_HTML   QString("UseTimeHtml")

#define STATE_INVALID_ALL               0b00000000
#define STATE_VALID_STATION_NAME        0b00000001
#define STATE_VALID_COMPANY_NAME        0b00000010
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

#define DLG_THR             qDebug()    << "[" << QThread::currentThreadId() << "][" << Q_FUNC_INFO << "]"

#define DLOG(msg, args...)  qDebug("[%s][Thread-%d][%s] " msg, QDateTime::currentDateTime().toString("HH:mm:ss:zzz").toStdString().c_str(), std::this_thread::get_id(), __PRETTY_FUNCTION__, ##args)

#define MCR_DEL_PTR(ptr)    if(!ptr) { \
                                delete ptr; \
                                ptr = NULL; \
                            }

#define SETDPDATA(DPID, VALUE)              Datapool::getInstance()->setData(DPID, VALUE)
#define GETDPDATA(DPID)                     Datapool::getInstance()->getData(DPID)

#define PATH_INI            ":/config/resources/config.ini"
#define PATH_WEB_SETTING    ":/web/resources/web/settingpage.html"
#define PATH_WEB_DATALOGGER ":/web/resources/web/KD201E.html"

#define MSG_UPDATE_STATUS   "update"

#define WRITE_FILE          true

#define TIME_RELOAD_INI     10000
#define TIME_LOAD_UNSEND    3600000     //1h
#define TIME_LOAD_STORAGE   21600000    //6h

#define MAX_FILE_SAVED      60000    //15d



inline bool checkIniFile()
{
    if(QFile::exists(INI_CONFIG_FILE))
        return true;
    return false;
}

#endif // COMMON_H
