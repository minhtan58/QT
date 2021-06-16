/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: ModelHandler.h
    Create: 07/03/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef MODELHANDLER_H
#define MODELHANDLER_H

#include <QObject>

#include "Common.h"
#include "TimeSystemHandler.h"
#include "SettingsHandler.h"
#include "CommonHandler.h"
#include "DbHandler.h"
#include "GPSHandler.h"
#include "DataTransferHandler.h"
#include "SensorHandler.h"

class ModelHandler : public QObject
{
    Q_OBJECT
public:
    explicit ModelHandler(QObject *parent = 0);
    ~ModelHandler();
    void start();

private:
    TimeSystemHandlerThread *m_timeSystemHandlerThread = nullptr;
    SettingsHandlerThread *m_settingsHandlerThread = nullptr;
    CommonHandlerThread *m_commonHandlerThread = nullptr;
    DbHandlerThread *m_dbHandlerThread = nullptr;
    GPSHandlerThread *m_gpsHandlerThread = nullptr;
    DataTransferHandlerThread *m_dataTransferHandlerThread = nullptr;
    SensorHandlerThread *m_sensorHandlerThread = nullptr;
};

#endif // MODELHANDLER_H
