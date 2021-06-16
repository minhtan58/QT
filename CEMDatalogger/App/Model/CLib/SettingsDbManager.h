/****************************************************************************

    Copyright (C) 2018 by LGE
    File: SettingsDbManager.h
    Create: 20
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef SETTINGSDBMANAGER_H
#define SETTINGSDBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "common.h"

#define DB_PATH "dbSettings.db"

typedef struct {
    int type;
    int status;
    QString min;
    QString max;
} AirAlarmStruct;

class SettingsDbManager
{
public:
    enum DbAirType{
        DB_AIR_ALARM_O2,
        DB_AIR_ALARM_CO,
        DB_AIR_ALARM_NO,
        DB_AIR_ALARM_NOX,
        DB_AIR_ALARM_SO2,
        DB_AIR_ALARM_TEMP,
        DB_AIR_ALARM_OPP,
        DB_AIR_ALARM_DUSTPM,
        DB_AIR_ALARM_VEL,
        DB_AIR_ALARM_FLOW
    };

    static bool createAirAlarmTable();
    static void setAirAlarm(const int &type, const int &status, const QString &min, const QString &max);
    static AirAlarmStruct &getAirAlarm(const int &type);
    static bool airExists(const int &type);

private:
    static bool openDb(QSqlDatabase &db);
    static bool closeDb(QSqlDatabase &db);
};

#endif // SETTINGSDBMANAGER_H
