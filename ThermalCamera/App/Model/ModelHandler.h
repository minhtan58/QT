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
#include "Defines.h"

#ifdef __linux__
#include "ThermalCameraHandler.h"
#include "NormalCameraHandler.h"
#include "GPIOHandler.h"
#include "MonitoringHandler.h"
#endif
#include "FDServerHandler.h"
#include "TemperatureAlarmHandler.h"

class ModelHandler : public QObject
{
    Q_OBJECT
public:
    explicit ModelHandler(QObject *parent = nullptr);
    ~ModelHandler();
    void start();

#ifdef __linux__
private:
    ThermalCameraHandlerThread *m_thermalCameraHandlerThread = nullptr;
    NormalCameraHandlerThread *m_normalCameraHandlerThread = nullptr;
    GPIOHandlerThread *m_gpioHandlerThread = nullptr;
    MonitoringHandlerThread *m_monitoringHandlerThread = nullptr;
#endif
    FDServerHandlerThread *m_fdServerHandlerThread = nullptr;
    TemperatureAlarmHandlerThread *m_temperatureAlarmHandlerThread = nullptr;
};

#endif // MODELHANDLER_H
