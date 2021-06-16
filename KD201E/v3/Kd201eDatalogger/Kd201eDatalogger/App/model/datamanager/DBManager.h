/****************************************************************************

    Copyright (C) 2018 by LGE
    File: DbManager.h
    Create: 14
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlError>
#include <QMutex>
#include "common.h"

#ifdef __WIN32
#define PH_DB                       "D://KD201E/kd201e.db"
#elif __linux__
#define PH_DB                       "/usr/KD201E/kd201e.db"
#endif

#define HISTORY_DAY         180
#define MISSING_STORE_DAY   30

typedef struct
{
    int isSent;
    QString time;
    QString varPH;
    QString varOC;
    QString varTSS;
    QString varFLOW;
    QString varCOD;
} DataRow;

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

    /* History data table */
    void createHistoryDataTable();
    void addHistoryDataRow(int isSent,
                           QString time,
                           QString varPH,
                           QString varOC,
                           QString varTSS,
                           QString varFLOW,
                           QString varCOD);
    void addHistoryDataRow(DataRow row);
    Q_INVOKABLE QList<DataRow> getHistoryData(QString time);
    void removeOldHistoryData(int day);
    void updateHistoryDataRow(DataRow row);
    QList<DataRow> getMissingData();

    /* Invoke method */
    QList<DataRow> invokeGetHistoryData(QString time);

public slots:


private:
    static DbManager *m_instance;
};

#endif // DBMANAGER_H
