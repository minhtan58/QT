#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QString>

#include <QNetworkAddressEntry>

#include "common.h"
#include "httplistener.h"
#include "RequestMapper.h"

class WebServer : public QObject
{
    Q_OBJECT
public:
    explicit WebServer(QObject *parent = nullptr);
    void startService();

private:
    RequestMapper *m_mapper = nullptr;
    QSettings *sessionSettings = nullptr;
    QSettings *listenerSettings = nullptr;

    void configure();
};

#endif // WEBSERVER_H
