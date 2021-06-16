/****************************************************************************

    Copyright (C) 2018 by LGE
    File: DbManager.cpp
    Create: 14
    Author: Vuong Nguyen

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
                              "isSent INTERGER,"
                              "time DATETIME NOT NULL,"
                              "varPH TEXT,"
                              "varOC TEXT,"
                              "varTSS TEXT,"
                              "varFLOW TEXT,"
                              "varCOD TEXT);";
    QSqlQuery query(database);
    if (query.exec(createSQL)) {
        DLOG("Table creation query execute successfully");
    } else {
        DLOG("Create table error: %s", database.lastError().text().toStdString().data());
    }
    database.close();
}

void DbManager::addHistoryDataRow(int isSent, QString time, QString varPH, QString varOC, QString varTSS, QString varFLOW, QString varCOD)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("HistoryData")) {
        DLOG("Create record error: Accounts table does not exist.");
    } else {
        QSqlQuery query(database);
        query.prepare("INSERT INTO HistoryData(isSent, time, varPH, varOC, varTSS, varFLOW, varCOD) "
                      "VALUES (:isSent, :time, :varPH, :varOC, :varTSS, :varFLOW, :varCOD);");
        query.bindValue(":isSent", isSent);
        query.bindValue(":time", time);
        query.bindValue(":varPH", varPH);
        query.bindValue(":varOC", varOC);
        query.bindValue(":varTSS", varTSS);
        query.bindValue(":varFLOW", varFLOW);
        query.bindValue(":varCOD", varCOD);
        if (query.exec()) {
            DLOG("Insert done");
        } else {
            DLOG("Insert error: %s", database.lastError().text().toStdString().data());
        }
    }
    database.close();
}

void DbManager::addHistoryDataRow(DataRow row)
{
    addHistoryDataRow(row.isSent, row.time, row.varPH, row.varOC, row.varTSS, row.varFLOW, row.varCOD);
}

QList<DataRow> DbManager::getHistoryData(QString time)
{
    DLOG("getHistoryData with time %s", time.toStdString().data());
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
            QList<DataRow> list;
            while(query.next()) {
                DataRow element;
                QSqlRecord record = query.record();
                element.isSent = record.value("isSent").toInt();
                element.time = record.value("time").toString();
                element.varPH = record.value("varPH").toString();
                element.varOC = record.value("varOC").toString();
                element.varTSS = record.value("varTSS").toString();
                element.varFLOW = record.value("varFLOW").toString();
                element.varCOD = record.value("varCOD").toString();
                list.append(element);
            }
            database.close();
            return list;
        } else {
            DLOG("Select record error: %s", database.lastError().text().data());
        }
    }

    database.close();
    return QList<DataRow>();
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

void DbManager::updateHistoryDataRow(DataRow row)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("HistoryData")) {
        DLOG("HistoryData table does not exist.");
    } else {
        QSqlQuery query(database);
        query.prepare("UPDATE HistoryData SET isSent = :isSent WHERE time = :time;");
        query.bindValue(":isSent", row.isSent);
        query.bindValue(":time", row.time);
        if (query.exec()) {
            DLOG("Change send status successful");
        } else {
            DLOG("Change send status record error: %s", database.lastError().text().toStdString().data());
        }
    }
    database.close();
}

QList<DataRow> DbManager::getMissingData()
{
    QList<DataRow> list;
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("HistoryData")) {
        DLOG("Select record error: HistoryData table does not exist.");
    } else {
        QSqlQuery query(database);
        QString command = QString("SELECT * FROM HistoryData WHERE isSent = 0;");
        query.prepare(command);
        if (query.exec()) {
            //DLOG("%s", query.executedQuery().toStdString().data());
            while(query.next()) {
                DataRow element;
                QSqlRecord record = query.record();
                element.isSent = record.value("isSent").toInt();
                element.time = record.value("time").toString();
                element.varPH = record.value("varPH").toString();
                element.varOC = record.value("varOC").toString();
                element.varTSS = record.value("varTSS").toString();
                element.varFLOW = record.value("varFLOW").toString();
                element.varCOD = record.value("varCOD").toString();
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

QList<DataRow> DbManager::invokeGetHistoryData(QString time)
{
    QList<DataRow> list;
    QMetaObject::invokeMethod(this, "getHistoryData", Qt::DirectConnection,
                              Q_RETURN_ARG(QList<DataRow>, list),
                              Q_ARG(QString, time));
    return list;
}
