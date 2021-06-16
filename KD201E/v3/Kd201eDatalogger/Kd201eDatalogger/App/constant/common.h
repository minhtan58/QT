#ifndef COMMON_H
#define COMMON_H

#include <QThread>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <thread>

#include "KD201EEnum.h"
#include "DBManager.h"

#ifdef __linux__
    #define INI_CONFIG_FOLDER   "/usr/KD201E"
    #define INI_CONFIG_FILE     "/usr/KD201E/kd201e.ini"
#elif _WIN32
    #define INI_CONFIG_FOLDER   "D://KD201E"
    #define INI_CONFIG_FILE     "D://KD201E/kd201e.ini"
#endif
#define DLOG(msg, args...)  qDebug("[%s][Thread-%d][%s] " msg, QDateTime::currentDateTime().toString("HH:mm:ss:zzz").toStdString().c_str(), std::this_thread::get_id(), ##args)
#define DLG_THR             qDebug()    << "[" << QThread::currentThreadId() << "][" << Q_FUNC_INFO << "]"
#define MCR_DEL_PTR(ptr)    if(!ptr) { \
                                delete ptr; \
                                ptr = NULL; \
                            }

#define SETDPDATA(DPID, VALUE)              Datapool::getInstance()->setData(DPID, VALUE)
#define GETDPDATA(DPID)                     Datapool::getInstance()->getData(DPID)

#define PATH_INI            ":/config/resources/config.ini"
#define PATH_WEB_SETTING    ":/web/resources/web/KD201ESettings.html"
#define PATH_WEB_DATALOGGER ":/web/resources/web/KD201E.html"
#define PATH_WEB_DATAVIEW   ":/web/resources/web/dataview.html"

#define MSG_UPDATE_STATUS   "update"

#define TIME_RELOAD_INI     10000
#define TIME_LOAD_UNSEND    3600000     //1h
#define TIME_LOAD_STORAGE   21600000    //6h

#define MAX_FILE_SAVED      60000    //15d

#define FORMAT_TIME_STD    "yyyyMMddHHmmss"
#define FORMAT_TIME_DB     "yyyy-MM-dd HH:mm:ss"

inline bool isExistsIniSettingFile()
{
    return QFile::exists(INI_CONFIG_FILE);
}


#endif // COMMON_H
