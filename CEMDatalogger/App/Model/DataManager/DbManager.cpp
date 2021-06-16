/****************************************************************************

    Copyright (C) 2018 by LGE
    File: DbManager.cpp
    Create: 14
    Author: Minh Tan

 ****************************************************************************/

#include "DbManager.h"

DbManager* DbManager::m_instance = nullptr;

DbManager::DbManager(QObject *parent) : QObject(parent)
{
    createDatabase();
    initDb();
}

DbManager::~DbManager()
{
    QSqlDatabase::removeDatabase("QSQLITE");
}

DbManager *DbManager::getInstance()
{
    if(m_instance == nullptr) {
        DLOG("DBManager null");
        m_instance = new DbManager();
    }
    return m_instance;
}

bool DbManager::createDatabase()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        DLOG("Unable to load database, needs install SQLITE driver");
    }

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    bool success = false;
    database.setDatabaseName(PH_DB);
    if (database.open()) {
        DLOG("Database created/registered.");
        success = true;
    } else {
        DLOG("Error opening connection to the database: %s", database.lastError().text().toStdString().data());
    }
    database.close();
    return success;
}

void DbManager::initDb()
{
    if(isDbExists()) {
        QSqlDatabase database = QSqlDatabase::database();
        if (!database.tables().contains("HistoryData")) {
            createHistoryDataTable();
        }
        if (!database.tables().contains("MissingData")) {
            createMissingDataTable();
        }
    }
}

bool DbManager::isDbExists()
{
    return QFile::exists(PH_DB);
}

void DbManager::createHistoryDataTable()
{
    QSqlDatabase database = QSqlDatabase::database();
    const QString createSQL = "CREATE TABLE IF NOT EXISTS HistoryData("
                              "time DATETIME NOT NULL,"
                              "valO2 TEXT,"
                              "valCO TEXT,"
                              "valNO TEXT,"
                              "valNOX TEXT,"
                              "valSO2 TEXT,"
                              "valTEMP TEXT,"
                              "valOPP TEXT,"
                              "valDUSTPM TEXT,"
                              "valVEL TEXT,"
                              "valFLOW TEXT);";
    QSqlQuery query(database);
    if (query.exec(createSQL)) {
        DLOG("Table creation query execute successfully");
    } else {
        DLOG("Create table error: %s", database.lastError().text().toStdString().data());
    }
    database.close();
}

void DbManager::addHistoryDataRow(QString time, QString valO2, QString valCO, QString valNO, QString valNOX, QString valSO2, QString valTEMP, QString valOPP, QString valDUSTPM, QString valVEL, QString valFLOW)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("HistoryData")) {
        DLOG("Create record error: Accounts table does not exist.");
    } else {
        QSqlQuery query(database);
        query.prepare("INSERT INTO HistoryData(time, valO2, valCO, valNO, valNOX, valSO2, valTEMP, valOPP, valDUSTPM, valVEL, valFLOW) "
                      "VALUES (:time, :valO2, :valCO, :valNO, :valNOX, :valSO2, :valTEMP, :valOPP, :valDUSTPM, :valVEL, :valFLOW);");
        query.bindValue(":time", time);
        query.bindValue(":valO2", valO2);
        query.bindValue(":valCO", valCO);
        query.bindValue(":valNO", valNO);
        query.bindValue(":valNOX", valNOX);
        query.bindValue(":valSO2", valSO2);
        query.bindValue(":valTEMP", valTEMP);
        query.bindValue(":valOPP", valOPP);
        query.bindValue(":valDUSTPM", valDUSTPM);
        query.bindValue(":valVEL", valVEL);
        query.bindValue(":valFLOW", valFLOW);
        if (query.exec()) {
            DLOG("Insert done");
        } else {
            DLOG("Insert error: %s", database.lastError().text().toStdString().data());
        }
    }
    database.close();
}

QList<CemsDataRow> DbManager::getHistoryData(QString time)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("HistoryData")) {
        DLOG("Select record error: HistoryData table does not exist.");
    } else {
        QSqlQuery query(database);
        QString command = QString("SELECT * FROM HistoryData "
                                  "WHERE time "
                                  "BETWEEN '%1 00:00:00' "
                                  "AND '%2 23:59:59' "
                                  "ORDER BY datetime(time);").arg(time).arg(time);
        query.prepare(command);
        if (query.exec()) {
            //DLOG("SQL command: %s", query.executedQuery().toStdString().data());
            QList<CemsDataRow> list;
            while(query.next()) {
                CemsDataRow element;
                QSqlRecord record = query.record();
                element.time = record.value("time").toString();
                element.valO2 = record.value("valO2").toString();
                element.valCO = record.value("valCO").toString();
                element.valNO = record.value("valNO").toString();
                element.valNOX = record.value("valNOX").toString();
                element.valSO2 = record.value("valSO2").toString();
                element.valTEMP = record.value("valTEMP").toString();
                element.valOPP = record.value("valOPP").toString();
                element.valDUSTPM = record.value("valDUSTPM").toString();
                element.valVEL = record.value("valVEL").toString();
                element.valFLOW = record.value("valFLOW").toString();
                list.append(element);
            }
            database.close();
            return list;
        } else {
            DLOG("Select record error: %s", database.lastError().text().data());
        }
    }

    database.close();
    return QList<CemsDataRow>();
}

void DbManager::removeOldHistoryData(int day)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("HistoryData")) {
        DLOG("Create record error: Accounts table does not exist.");
    } else {
        QSqlQuery query(database);

        QString command = QString("DELETE FROM HistoryData WHERE time < datetime('now', '-%1 day');").arg(day);
        query.prepare(command);
        if (query.exec()) {
            DLOG("Exec delete command done");
        } else {
            DLOG("Exec delete command error: %s", database.lastError().text().data());
        }
    }
    database.close();
}

void DbManager::createMissingDataTable()
{
    QSqlDatabase database = QSqlDatabase::database();
    const QString createSQL = "CREATE TABLE IF NOT EXISTS MissingData("
                              "time DATETIME NOT NULL,"
                              "valO2 TEXT,"
                              "valCO TEXT,"
                              "valNO TEXT,"
                              "valNOX TEXT,"
                              "valSO2 TEXT,"
                              "valTEMP TEXT,"
                              "valOPP TEXT,"
                              "valDUSTPM TEXT,"
                              "valVEL TEXT,"
                              "valFLOW TEXT);";
    QSqlQuery query(database);
    if (query.exec(createSQL)) {
        DLOG("Table creation query execute successfully");
    } else {
        DLOG("Create table error: %s", database.lastError().text().data());
    }
    database.close();
}

void DbManager::addMissingDataRow(QString time, QString valO2, QString valCO, QString valNO, QString valNOX, QString valSO2, QString valTEMP, QString valOPP, QString valDUSTPM, QString valVEL, QString valFLOW)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("MissingData")) {
        DLOG("Create record error: MissingData table does not exist.");
    } else {
        QSqlQuery query(database);
        query.prepare("INSERT INTO MissingData(time, valO2, valCO, valNO, valNOX, valSO2, valTEMP, valOPP, valDUSTPM, valVEL, valFLOW) "
                      "VALUES (:time, :valO2, :valCO, :valNO, :valNOX, :valSO2, :valTEMP, :valOPP, :valDUSTPM, :valVEL, :valFLOW);");
        query.bindValue(":time", time);
        query.bindValue(":valO2", valO2);
        query.bindValue(":valCO", valCO);
        query.bindValue(":valNO", valNO);
        query.bindValue(":valNOX", valNOX);
        query.bindValue(":valSO2", valSO2);
        query.bindValue(":valTEMP", valTEMP);
        query.bindValue(":valOPP", valOPP);
        query.bindValue(":valDUSTPM", valDUSTPM);
        query.bindValue(":valVEL", valVEL);
        query.bindValue(":valFLOW", valFLOW);
        if (query.exec()) {
            DLOG("Insert done");
        } else {
            DLOG("Insert error: %s", database.lastError().text().data());
        }
    }
    database.close();
}

QList<CemsDataRow> DbManager::getMissingData()
{
    QList<CemsDataRow> list;
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("MissingData")) {
        DLOG("Select record error: MissingData table does not exist.");
    } else {
        QSqlQuery query(database);
        QString command = QString("SELECT * FROM MissingData;");
        query.prepare(command);
        if (query.exec()) {
            //DLOG("%s", query.executedQuery().toStdString().data());
            while(query.next()) {
                CemsDataRow element;
                QSqlRecord record = query.record();
                element.time = record.value("time").toString();
                element.valO2 = record.value("valO2").toString();
                element.valCO = record.value("valCO").toString();
                element.valNO = record.value("valNO").toString();
                element.valNOX = record.value("valNOX").toString();
                element.valSO2 = record.value("valSO2").toString();
                element.valTEMP = record.value("valTEMP").toString();
                element.valOPP = record.value("valOPP").toString();
                element.valDUSTPM = record.value("valDUSTPM").toString();
                element.valVEL = record.value("valVEL").toString();
                element.valFLOW = record.value("valFLOW").toString();
                list.append(element);
            }
            database.close();
        } else {
            DLOG("Select record error: %s", database.lastError().text().data());
        }
    }

    database.close();
    return list;
}

void DbManager::removeOldMissingData(int day)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("MissingData")) {
        DLOG("Create record error: MissingData table does not exist.");
    } else {
        QSqlQuery query(database);

        QString command = QString("DELETE FROM MissingData WHERE time < datetime('now', '-%1 day');").arg(day);
        query.prepare(command);
        if (query.exec()) {
            //DLOG("Exec delete command done");
        } else {
            DLOG("Exec delete command error: %s", database.lastError().text().data());
        }
    }
    database.close();
}

void DbManager::removeSentMissingData(QString time)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("MissingData")) {
        DLOG("Create record error: MissingData table does not exist.");
    } else {
        QSqlQuery query(database);

        QString command = QString("DELETE FROM MissingData WHERE time = '%1';").arg(time);
        query.prepare(command);
        if (query.exec()) {
            DLOG("Exec delete command done");
        } else {
            DLOG("Exec delete command error: %s", database.lastError().text().data());
        }
    }
    database.close();
}
