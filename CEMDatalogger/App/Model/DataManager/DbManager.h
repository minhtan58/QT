/****************************************************************************

    Copyright (C) 2018 by LGE
    File: DbManager.h
    Create: 14
    Author: Minh Tan

 ****************************************************************************/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlError>
#include "Defines.h"
#include "common.h"

#define DB_PATH "dbSettings.db"

#define HISTORY_DAY         180
#define MISSING_STORE_DAY   30

class DbManager : public QObject
{
    Q_OBJECT
public:
    explicit DbManager(QObject *parent = nullptr);
    ~DbManager();
    static DbManager *getInstance();

    bool createDatabase();
    void initDb();
    bool isDbExists();
    void createHistoryDataTable();
    void addHistoryDataRow(QString time,
                           QString valO2,
                           QString valCO,
                           QString valNO,
                           QString valNOX,
                           QString valSO2,
                           QString valTEMP,
                           QString valOPP,
                           QString valDUSTPM,
                           QString valVEL,
                           QString valFLOW);
    QList<CemsDataRow> getHistoryData(QString time);
    void removeOldHistoryData(int day);

    //network missing
    void createMissingDataTable();
    void addMissingDataRow(QString time,
                           QString valO2,
                           QString valCO,
                           QString valNO,
                           QString valNOX,
                           QString valSO2,
                           QString valTEMP,
                           QString valOPP,
                           QString valDUSTPM,
                           QString valVEL,
                           QString valFLOW);
    QList<CemsDataRow> getMissingData();
    void removeOldMissingData(int day);
    void removeSentMissingData(QString time);

private:
    static DbManager *m_instance;
};

#endif // DBMANAGER_H
