/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: ModelHandler.cpp
    Create: 07/03/2018
    Author: Minh Tan

 ****************************************************************************/

#include "ModelHandler.h"

ModelHandler::ModelHandler(QObject *parent)
    : QObject(parent)
{
    DLOG("Create");
    m_timeSystemHandler = new TimeSystemHandlerThread(this);
    m_settingsHandler = new SettingsHandlerThread(this);
    m_networkMainServerHandler = new NetworkMainServerHandlerThread(this);
    m_serialPortHandler = new SerialPortHandlerThread(this);
    m_commonHandlerThread = new CommonHandlerThread(this);
    m_dbHandlerThread = new DbHandlerThread(this);
}

ModelHandler::~ModelHandler()
{
    m_timeSystemHandler->quit();
    m_settingsHandler->quit();
    m_networkMainServerHandler->quit();
    m_serialPortHandler->quit();
    m_commonHandlerThread->quit();
    m_dbHandlerThread->quit();
}

void ModelHandler::start()
{
    m_timeSystemHandler->start();
    m_settingsHandler->start();
    m_networkMainServerHandler->start();
    m_serialPortHandler->start();
    m_commonHandlerThread->start();
    m_dbHandlerThread->start();
}
