#include "WebServer.h"

WebServer::WebServer(QObject *parent) : QObject(parent)
{
    configure();
}

void WebServer::startService()
{
    new HttpListener(listenerSettings, m_mapper, this);
}

void WebServer::configure()
{
    sessionSettings = new QSettings(PATH_INI, QSettings::IniFormat, this);
    sessionSettings->beginGroup("sessions");
    RequestMapper::sessionStore = new HttpSessionStore(sessionSettings, this);
    listenerSettings = new QSettings(PATH_INI, QSettings::IniFormat, this);
    listenerSettings->beginGroup("listener");
    m_mapper = new RequestMapper(this);
}
