#ifndef GPSHANDLER_H
#define GPSHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

#include "Common.h"
#include "AppModel.h"

class GPSHandler : public QObject
{
    Q_OBJECT
public:
    explicit GPSHandler(QObject *parent = 0);

signals:

public slots:
    void readGPS();

private:
    QSerialPort *m_serial = nullptr;
    QTimer *m_timerReadData = nullptr;

    void serialPortConfigure();
    void analysisRMC(QString &msg);
    QString convertStdLatitude(const QString &gpsLat);
    QString convertStdLongitude(const QString &gpsLng);
};

//thread define
class GPSHandlerThread : public QThread
{
    Q_OBJECT
public:
    GPSHandlerThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() {
        DLOG("Starting...");
        GPSHandler handler;
//        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        exec();
    }
};

#endif // GPSHANDLER_H
