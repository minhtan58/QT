/****************************************************************************

    Copyright (C) 2018 by LGE
    File: SettingsDbManager.cpp
    Create: 20
    Author: Vuong Nguyen

 ****************************************************************************/

#include "SettingsDbManager.h"

bool SettingsDbManager::createAirAlarmTable()
{
    QSqlDatabase db;
    if(openDb(db)) {
        QSqlQuery query;
        query.prepare("CREATE TABLE AirAlarmTB(airType INT, airAlarmStatus INT, airAlarmMin TEXT, airAlarmMax TEXT);");
        if (query.exec()) {
            DLOG_THREAD << "Create the table 'AirAlarmTB' success";
            closeDb(db);
            return false;
        }
    }
    DLOG_THREAD << "Couldn't create the table 'AirAlarmTB': one might already exist.";
    closeDb(db);
    return false;
}

void SettingsDbManager::setAirAlarm(const int &type, const int &status, const QString &min, const QString &max)
{
    QSqlDatabase db;
    if(airExists(type)) {
        if(openDb(db)) {
            QSqlQuery query;
            query.prepare("INSERT INTO AirAlarmTB VALUES (:type, :status, :min, :max);");
            query.bindValue(":type", type);
            query.bindValue(":status", status);
            query.bindValue(":min", min);
            query.bindValue(":max", max);
            if (!query.exec()) {
                DLOG_THREAD << "Insert fail";
                closeDb(db);
            }
            DLOG_THREAD << "Insert successful";
            closeDb(db);
        }
    }
    else {
        if(openDb(db)) {
//            if (!query.exec()) {
//                DLOG_THREAD << "Insert fail";
//                closeDb(db);
//            }
//            DLOG_THREAD << "Insert successful";
//            closeDb(db);
        }
    }
}

AirAlarmStruct& SettingsDbManager::getAirAlarm(const int &type)
{

}

bool SettingsDbManager::airExists(const int &type)
{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT type FROM AirAlarmTB WHERE type = (:type)");
    checkQuery.bindValue(":type", type);

    if (checkQuery.exec())
        if (checkQuery.next())
            return true;
    return false;
}

bool SettingsDbManager::openDb(QSqlDatabase &db)
{
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        DLOG_THREAD << "Unable to load database, needs install SQLITE driver";
        return false;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(CEMS_SETTINGS_DB_FILENAME);
    if(db.open()) {
        DLOG_THREAD << "Connection db " << db.databaseName() << " OK";
        return true;
    }
    DLOG_THREAD << "Connection db " << db.databaseName() << " Fail!";
    return false;
}

bool SettingsDbManager::closeDb(QSqlDatabase &db)
{
    if(db.isOpen())
        db.close();
}
