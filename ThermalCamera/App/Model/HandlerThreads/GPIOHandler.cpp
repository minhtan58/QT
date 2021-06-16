#include "HMIEvents.h"
#include "DataManager.h"
#include "GPIOHandler.h"

GPIOHandler::GPIOHandler(QObject *parent)
    : QObject(parent)
{
    DLOG("Create");
    m_timCpuTemp = new QTimer(this);
    m_timCpuTemp->setInterval(1000);
    connect(m_timCpuTemp, SIGNAL(timeout()), this, SLOT(updateCPUTemperature()));
    gpioConfigure();
    m_timCpuTemp->start();
}

void GPIOHandler::dummy()
{
    digitalWrite(VINCAM_GPIO_FAN, LOW);
}

void GPIOHandler::updateData(int dpid, QString value)
{
    switch (dpid) {
    case 1: {
        break;
    }
    default:
        break;
    }
}

void GPIOHandler::handleEvent(QString objectName, int eventId, QString params)
{
    switch (eventId) {
    case REQUEST_SEND_FDALARM:
        break;
    default:
        break;
    }
}

void GPIOHandler::updateCPUTemperature()
{
    FILE *fd;
    double cpuTemp;
    fd = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
    if (fd == NULL)
        DLOG("Can't read CPU temperature");
    fscanf (fd, "%lf", &cpuTemp);
    cpuTemp /= 1000;
    fprintf ("The temperature is %6.3f C.\n", cpuTemp);
    fclose (fd);

    SETDP(DPID::DP_SYSTEM_CPU_TEMPERATURE, QString::number(cpuTemp));
}

void GPIOHandler::gpioConfigure()
{
    wiringPiSetupPhys();
    pinMode(VINCAM_GPIO_ALARM1, OUTPUT);
    pinMode(VINCAM_GPIO_ALARM2, OUTPUT);
    pinMode(VINCAM_GPIO_FAN, OUTPUT);
}
