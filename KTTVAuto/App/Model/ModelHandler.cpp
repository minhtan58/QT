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
    DLOG("Create Model Handler");
    m_timeSystemHandlerThread = new TimeSystemHandlerThread(this);
    m_dataTransferHandlerThread = new DataTransferHandlerThread(this);
    m_settingsHandlerThread = new SettingsHandlerThread(this);
    m_commonHandlerThread = new CommonHandlerThread(this);
    m_dbHandlerThread = new DbHandlerThread(this);
    m_gpsHandlerThread = new GPSHandlerThread(this);
    m_sensorHandlerThread = new SensorHandlerThread(this);

    /* Load settings first */
    m_settingsHandlerThread->start();
}

ModelHandler::~ModelHandler()
{
    m_timeSystemHandlerThread->quit();
    m_settingsHandlerThread->quit();
    m_commonHandlerThread->quit();
    m_dbHandlerThread->quit();
    m_gpsHandlerThread->quit();
    m_dataTransferHandlerThread->quit();
    m_sensorHandlerThread->quit();

//    DLOG("SystemHandlerThread %s",  m_timeSystemHandlerThread->isRunning() ? "still running" : "stopped");
//    DLOG("SettingsHandlerThread %s", m_settingsHandlerThread->isRunning() ? "still running" : "stopped");
//    DLOG("CommonHandlerThread %s", m_commonHandlerThread->isRunning() ? "still running" : "stopped");
//    DLOG("DbHandlerThread %s", m_dbHandlerThread->isRunning() ? "still running" : "stopped");
//    DLOG("GpsHandlerThread %s", m_gpsHandlerThread->isRunning() ? "still running" : "stopped");
//    DLOG("DataTransferHandlerThread %s", m_dataTransferHandlerThread->isRunning() ? "still running" : "stopped");
}

void ModelHandler::start()
{
    m_timeSystemHandlerThread->start();
    m_commonHandlerThread->start();
    m_dbHandlerThread->start();
//    m_gpsHandlerThread->start();
    m_dataTransferHandlerThread->start();
    m_sensorHandlerThread->start();
}
