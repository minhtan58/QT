/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: ModelHandler.h
    Create: 07/03/2018
    Author: Minh Tan

 ****************************************************************************/

#ifndef MODELHANDLER_H
#define MODELHANDLER_H

#include <QObject>

#include "Common.h"
#include "NetworkMainServerHandler.h"
#include "TimeSystemHandler.h"
#include "SettingsHandler.h"
#include "SerialPortHandler.h"
#include "CommonHandler.h"
#include "DbHandler.h"

class ModelHandler : public QObject
{
    Q_OBJECT
public:
    explicit ModelHandler(QObject *parent = 0);
    ~ModelHandler();
    void start();

private:
    TimeSystemHandlerThread *m_timeSystemHandler = nullptr;
    SettingsHandlerThread *m_settingsHandler = nullptr;
    NetworkMainServerHandlerThread *m_networkMainServerHandler = nullptr;
    SerialPortHandlerThread *m_serialPortHandler = nullptr;
    CommonHandlerThread *m_commonHandlerThread = nullptr;
    DbHandlerThread *m_dbHandlerThread = nullptr;
};

#endif // MODELHANDLER_H
