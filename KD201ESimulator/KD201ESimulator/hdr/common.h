#ifndef COMMON_H
#define COMMON_H

#include <QThread>
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QString>
#include <QDateTime>
#include <thread>

#define DLOG(msg, args...)  qDebug("[%s][Thread-%d][%s] " msg, QDateTime::currentDateTime().toString("HH:mm:ss:zzz").toStdString().c_str(), std::this_thread::get_id(), __PRETTY_FUNCTION__, ##args)

#define PATH_INI            ":/config/resources/config.ini"
#define PATH_WEB_DATALOGGER ":/web/resources/web/IQ WEB CONNECT.html"

#endif // COMMON_H
