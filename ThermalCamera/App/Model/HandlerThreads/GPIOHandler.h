#ifndef GPIOHANDLER_H
#define GPIOHANDLER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "Delivery.h"
#include "Common.h"
#include "DataManager.h"
#include "Defines.h"

#include "wiringPi.h"

#define VINCAM_GPIO_ALARM1  15
#define VINCAM_GPIO_ALARM2  16
#define VINCAM_GPIO_FAN     7


class GPIOHandler : public QObject
{
    Q_OBJECT
public:
    explicit GPIOHandler(QObject *parent = nullptr);
    void dummy();

public slots:
    void updateData(int dpid, QString value);
    void handleEvent(QString objectName, int eventId, QString params);
    void updateCPUTemperature();

private:
    QTimer *m_timCpuTemp = nullptr;
    void gpioConfigure();

};

//thread define
class GPIOHandlerThread : public QThread
{
    Q_OBJECT
public:
    GPIOHandlerThread(QObject *parent = nullptr)
        : QThread(parent)
    {}

protected:
    void run() {
        DLOG("Start");
        GPIOHandler handler;
        exec();
    }
};

#endif // GPIOHANDLER_H
