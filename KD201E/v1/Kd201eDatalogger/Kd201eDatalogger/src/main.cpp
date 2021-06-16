#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QString>

#include <QNetworkAddressEntry>

#include "httplistener.h"
#include "requestmapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString configFileName=PATH_INI;

    // Session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    sessionSettings->beginGroup("sessions");
    RequestMapper::sessionStore=new HttpSessionStore(sessionSettings,&app);

    // HTTP server
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    listenerSettings->beginGroup("listener");

    RequestMapper *mapper = new RequestMapper(&app);

    new HttpListener(listenerSettings, mapper, &app);

    DLOG("Main Thread");

//    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
//        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
//             qDebug() << address.toString();
//    }

    return app.exec();
}
