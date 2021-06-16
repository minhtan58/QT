/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: TimeSystemHandler.h
    Create: 06/03/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QSerialPort>

#include "Common.h"
#include "AppModel.h"
#include "UIBridge.h"

#ifdef __linux__
#include "wiringPi.h"
#include "pcf8591.h"
#include "wiringPiI2C.h"

#define PCF8591     0x48
#define BASE        64
#define A0          BASE+0
#define A1          BASE+1
#define A2          BASE+2
#define A3          BASE+3

#define RAIN        11
#endif

#define WIND_DIRRECT_SE     31//21
#define WIND_DIRRECT_E      37//23
#define WIND_DIRRECT_NE     21//27
#define WIND_DIRRECT_N      33//29
#define WIND_DIRRECT_NW     29//31
#define WIND_DIRRECT_W      27//33
#define WIND_DIRRECT_SW     23//35
#define WIND_DIRRECT_S      35//37

enum WinDirrect {
    DIRRECT_SE,
    DIRRECT_E,
    DIRRECT_NE,
    DIRRECT_N,
    DIRRECT_NW,
    DIRRECT_W,
    DIRRECT_SW,
    DIRRECT_S
};

const QHash<int, QString> windDirrectMap = {
    {DIRRECT_SE,    "SE"},
    {DIRRECT_E,     "E"},
    {DIRRECT_NE,    "NE"},
    {DIRRECT_N,     "N"},
    {DIRRECT_NW,    "NW"},
    {DIRRECT_W,     "W"},
    {DIRRECT_SW,    "SW"},
    {DIRRECT_S,     "S"}
};

class SensorHandler : public QObject
{
    Q_OBJECT
public:
    explicit SensorHandler(QObject *parent = nullptr);

public slots:
    void eventHandler(QString objectName, int eventId, QString param);
    void requestReadData();
    void readResponse();
    void responseAlynasis(QString &response);

    void onDataSendAutomaticRequestIntervalChanged();
    void onSystemTimeChanged();
    void onIsConnectedSensorChanged();

    void onSensorPortNameChanged();

#ifdef __linux__
    void updateWind();
    void updateRain();
#endif

private:
    QSerialPort *m_serial = nullptr;
    QTimer *m_updatePressure = nullptr;
    QTimer *m_updateFF = nullptr;
    QTimer *m_updateRain = nullptr;
    QString m_line;

    void serialConfigure();
    void tryConnectSensor();

#ifdef __linux__
    void i2cConfigWindff();
    void inputPinConfigRain();
    void inputPinConfigWindDirrect();
#endif
};

class SensorHandlerThread : public QThread
{
    Q_OBJECT
public:
    explicit SensorHandlerThread(QObject *parent = nullptr) : QThread(parent){}

protected:
    void run() {
        DLOG("Starting...");
        SensorHandler handler;
        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        exec();
    }
};

#endif // SENSORHANDLER_H
