#ifndef TEMPERATUREALARMHANDLER_H
#define TEMPERATUREALARMHANDLER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QTcpSocket>

#include "Delivery.h"
#include "Common.h"
#include "DataManager.h"
#include "Defines.h"

class TemperatureAlarmHandler : public QObject
{
    Q_OBJECT
public:
    explicit TemperatureAlarmHandler(QObject *parent = nullptr);

public slots:
    void updateData(int dpid, QString value);

private:
    QTimer *m_timTempAlarm = nullptr;
    double m_thresoldMaxTemp;
    double m_thresoldMinTemp;
    int m_verifyTime;

};

//thread define
class TemperatureAlarmHandlerThread : public QThread
{
    Q_OBJECT
public:
    TemperatureAlarmHandlerThread(QObject *parent = nullptr)
        : QThread(parent)
    {}

protected:
    void run() {
        DLOG("Start");
        TemperatureAlarmHandler handler;
        exec();
    }
};

#endif // TEMPERATUREALARMHANDLER_H
