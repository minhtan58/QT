/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: TimeSystemHandler.cpp
    Create: 06/03/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#include "SensorHandler.h"

SensorHandler::SensorHandler(QObject *parent)
    : QObject(parent)
{
    connect(MODEL, SIGNAL(sensorPortNameChanged()), this, SLOT(onSensorPortNameChanged()), Qt::QueuedConnection);
    connect(MODEL, SIGNAL(dataSendAutomaticRequestIntervalChanged()), this, SLOT(onDataSendAutomaticRequestIntervalChanged()), Qt::QueuedConnection);

    /* timer for reset rain */
    connect(MODEL, SIGNAL(systemMinuteChanged()), this, SLOT(onSystemTimeChanged()), Qt::QueuedConnection);
    connect(MODEL, SIGNAL(systemSecondChanged()), this, SLOT(onSystemTimeChanged()), Qt::QueuedConnection);
    connect(MODEL, SIGNAL(systemHourChanged()), this, SLOT(onSystemTimeChanged()), Qt::QueuedConnection);

    /* when sensor connected, run timer for update data */
    connect(MODEL, SIGNAL(isConnectedSensorChanged()), this, SLOT(onIsConnectedSensorChanged()), Qt::QueuedConnection);

    /* timer for pressure */
    m_updatePressure = new QTimer(this);
    connect(m_updatePressure, SIGNAL(timeout()), this, SLOT(requestReadData()), Qt::QueuedConnection);
    serialConfigure();
    m_updatePressure->start(1000);

#ifdef __linux__
    /* timer for wind */
    m_updateFF = new QTimer(this);
    connect(m_updateFF, SIGNAL(timeout()), this, SLOT(updateWind()), Qt::QueuedConnection);
    m_updateFF->start(5000);

    /* timer for rain */
    m_updateRain = new QTimer(this);
    connect(m_updateRain, SIGNAL(timeout()), this, SLOT(updateRain()), Qt::QueuedConnection);
    m_updateRain->start(50);

    /* hardware configure */
    wiringPiSetupPhys();
    i2cConfigWindff();
    inputPinConfigRain();
    inputPinConfigWindDirrect();
#endif
}

void SensorHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case HMIEvents::HMI_SWITCH_UPDATE_TIME_AUTOMATIC: {
        break;
    }
    default:
        break;
    }
}

void SensorHandler::requestReadData()
{
    if(!m_serial->isOpen()) {
        MODEL->isConnectedSensorSet(false);
        tryConnectSensor();
    }

    if(m_serial->isOpen()) {
        DLOG("send request");
        m_serial->write("ptest\r\n");
    }
}

void SensorHandler::readResponse()
{
    m_serial->waitForReadyRead(50);
    QString response = m_serial->readAll();
//    DLOG("res: %s", response.toStdString().data());
//    DLOG_THREAD << "res:" << response;
    if(response.startsWith("p")) {
        m_line = response;
    } else if(response.endsWith(">")) {
        m_line += response;
//        DLOG("response: %s", m_line.toStdString().data());
//        DLOG_THREAD << "response: " << m_line;
        responseAlynasis(m_line);
    } else {
        m_line += response;
    }
}

void SensorHandler::responseAlynasis(QString &response)
{
    QStringList list = response.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    if(list.size() > 1) {
        double khiap = list.at(1).toDouble();
        if(khiap > 3) {
            MODEL->work_thb_khiapSet(MCR_DPDATA_DOUBLE_STD(khiap - 3, 1));
        }
    }
}

void SensorHandler::onDataSendAutomaticRequestIntervalChanged()
{
    if(m_updatePressure->isActive())
        m_updatePressure->stop();
    m_updatePressure->start(MODEL->dataSendAutomaticRequestInterval());
    DLOG("Start sensor update interval %d", MODEL->dataSendAutomaticRequestInterval());
}

void SensorHandler::onSystemTimeChanged()
{
    if(!MODEL->isConnectedSensor()) {
        return;
    }

    if(MODEL->systemSecond() == 0 && MODEL->systemMinute() == 0) {
        DLOG("Check for reset rain");
        MODEL->work_rain_1hSet("0");
        if(MODEL->systemHour() == 0) {
            MODEL->work_rain_24hSet("0");
        }
    }
}

void SensorHandler::onIsConnectedSensorChanged()
{
    onDataSendAutomaticRequestIntervalChanged();
}

void SensorHandler::onSensorPortNameChanged()
{
    tryConnectSensor();
}

void SensorHandler::serialConfigure()
{
    m_serial = new QSerialPort(this);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    connect(m_serial, SIGNAL(readyRead()), this, SLOT(readResponse()));
    tryConnectSensor();
}

void SensorHandler::tryConnectSensor()
{
    if(MODEL->sensorPortName().isEmpty())
        return;

    if(!m_serial->isOpen()) {
        m_serial->setPortName(MODEL->sensorPortName());
        MODEL->isConnectedSensorSet(m_serial->open(QIODevice::ReadWrite));
        DLOG("%s to serial port %s, baudrate %d", (MODEL->isConnectedSensor() ? "Connected" : "Cannot connect"), m_serial->portName().toStdString().data(), m_serial->baudRate());
    } else {
        MODEL->isConnectedSensorSet(true);
    }
}

#ifdef __linux__
void SensorHandler::updateRain()
{
    if (digitalRead(RAIN) == 0) {
        DLOG("Rain rev");
        double rain1h = MODEL->work_rain_1h().toDouble();
        double rain24h = MODEL->work_rain_24h().toDouble();
        double slope = MODEL->dataSlope().toDouble();
        MODEL->work_rain_1hSet(MCR_DPDATA_DOUBLE_STD(rain1h + slope, 1));
        MODEL->work_rain_24hSet(MCR_DPDATA_DOUBLE_STD(rain24h + slope, 1));
        while(digitalRead(RAIN) == 0);
    }
}

void SensorHandler::updateWind()
{
    int digital = 0;
    double analog = 0;
    digital = analogRead(A2);
    analog = digital/255.0 * 5 * 2;
    DLOG("digital = %d, analog = %.1fV", digital, analog);

    double hs =  12.5;

//    if(analog < 0.2) {
//        hs = 12.5;
//    } else if (analog < 0.4) {
//        hs = 11.125;
//    } else if (analog < 0.8) {
//        hs = 8.4;
//    } else if (analog < 1.3) {
//        hs = 6.6;
//    } else if (analog < 1.8) {
//        hs = 5.8;
//    } else if (analog < 2.7) {
//        hs = 5.3;
//    } else if (analog < 4.5) {
//        hs = 4.95;
//    } else if (analog < 5.5) {
//        hs = 4.7;
//    } else {
//        hs = 4.7;
//    }

    if(analog < 0.2) {
        hs = 12.5;
    } else if (analog <= 0.4) {
        hs = 11.125;    //0.2 -> 0.4
    } else if (analog <= 0.6) {
        hs = 9.875;       //0.4-> 0.6
    } else if (analog <= 1.0) {
        hs = 9;    //0.6 -> 1.0
    } else if (analog <= 1.8) {
        hs = 7.86;    //1.0 -> 1.8
    } else if (analog <= 2.5) {
        hs = 8.18;       //1.8 -> 2.5
    } else if (analog <= 2.8) {
        hs = 8.8735;      //2.0 -> 2.8
    } else if (analog <= 3.1){
        hs = 9.3115;
    }

    MODEL->work_wind_ffSet(MCR_DPDATA_DOUBLE_STD(analog * hs, 1));
    MODEL->work_wind_ecode_ffSet(QString::number(analog));

    int winDirrect[8];
    winDirrect[0] = digitalRead(WIND_DIRRECT_SE);
    winDirrect[1] = digitalRead(WIND_DIRRECT_E);
    winDirrect[2] = digitalRead(WIND_DIRRECT_NE);
    winDirrect[3] = digitalRead(WIND_DIRRECT_N);
    winDirrect[4] = digitalRead(WIND_DIRRECT_NW);
    winDirrect[5] = digitalRead(WIND_DIRRECT_W);
    winDirrect[6] = digitalRead(WIND_DIRRECT_SW);
    winDirrect[7] = digitalRead(WIND_DIRRECT_S);

    DLOG("SE - %d, E - %d, NE - %d, N - %d, NW - %d, W - %d, SW - %d, S - %d",
         winDirrect[0],
            winDirrect[1],
            winDirrect[2],
            winDirrect[3],
            winDirrect[4],
            winDirrect[5],
            winDirrect[6],
            winDirrect[7]);

    for (int i = 0; i < 8; ++i) {
        if(winDirrect[i] == 0) {
            MODEL->work_wind_ddSet(windDirrectMap[i]);
            return;
        }
    }
}

void SensorHandler::i2cConfigWindff()
{
    pcf8591Setup(BASE, 0x48);
}

void SensorHandler::inputPinConfigRain()
{
    pinMode(RAIN, INPUT);
    pullUpDnControl(RAIN, PUD_UP);
//    wiringPiISR(RAIN, INT_EDGE_FALLING, &SensorHandler::updateRain);
}

void SensorHandler::inputPinConfigWindDirrect()
{
    pinMode(WIND_DIRRECT_SE,    INPUT);
    pinMode(WIND_DIRRECT_E,     INPUT);
    pinMode(WIND_DIRRECT_NE,    INPUT);
    pinMode(WIND_DIRRECT_N,     INPUT);
    pinMode(WIND_DIRRECT_NW,    INPUT);
    pinMode(WIND_DIRRECT_W,     INPUT);
    pinMode(WIND_DIRRECT_SW,    INPUT);
    pinMode(WIND_DIRRECT_S,     INPUT);

    /* pull */
    pullUpDnControl(WIND_DIRRECT_SE,    PUD_UP);
    pullUpDnControl(WIND_DIRRECT_E,     PUD_UP);
    pullUpDnControl(WIND_DIRRECT_NE,    PUD_UP);
    pullUpDnControl(WIND_DIRRECT_N,     PUD_UP);
    pullUpDnControl(WIND_DIRRECT_NW,    PUD_UP);
    pullUpDnControl(WIND_DIRRECT_W,     PUD_UP);
    pullUpDnControl(WIND_DIRRECT_SW,    PUD_UP);
    pullUpDnControl(WIND_DIRRECT_S,     PUD_UP);
}
#endif
