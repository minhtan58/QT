/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: ModelHandler.cpp
    Create: 07/03/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#include "ModelHandler.h"

ModelHandler::ModelHandler(QObject *parent)
    : QObject(parent)
{
    DLOG("Create");
#ifdef __linux__
    m_thermalCameraHandlerThread = new ThermalCameraHandlerThread(this);
//    m_normalCameraHandlerThread = new NormalCameraHandlerThread(this);
    m_gpioHandlerThread = new GPIOHandlerThread(this);
    m_monitoringHandlerThread = new MonitoringHandlerThread(this);
#endif
    m_fdServerHandlerThread = new FDServerHandlerThread(this);
    m_temperatureAlarmHandlerThread = new TemperatureAlarmHandlerThread(this);
}

ModelHandler::~ModelHandler()
{
#ifdef __linux__
    m_thermalCameraHandlerThread->quit();
//    m_normalCameraHandlerThread->quit();
    m_gpioHandlerThread->quit();
    m_monitoringHandlerThread->quit();
#endif
    m_fdServerHandlerThread->quit();
    m_temperatureAlarmHandlerThread->quit();
}

void ModelHandler::start()
{
#ifdef __linux__
    m_thermalCameraHandlerThread->start();
//    m_normalCameraHandlerThread->start();
    m_gpioHandlerThread->start();
    m_monitoringHandlerThread->start();
#endif
    m_fdServerHandlerThread->start();
    m_temperatureAlarmHandlerThread->start();
}
