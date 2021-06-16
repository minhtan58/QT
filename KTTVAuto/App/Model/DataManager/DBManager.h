/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: DBManager.h
    Create: 20
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
#include <QFile>

#include "common.h"
#include "Constants.h"

#define DB_PATH "dbSettings.db"
#define PERMISSION_OPERATOR         0b00000001
#define PERMISSION_SETTING_STATION  0b00000010
#define PERMISSION_SETTING_ACCOUNT  0b00000100
#define PERMISSION_ROOT             0b00001000

typedef struct {
    QString id;
    int permission;
    QString username;
    QString password;
    QString fullName;
    QString description;
} AccountInformation;

typedef struct {
    QString id;
    QString fullname;
    QString logindate;
    QString logoutdate;
} LoginHistory;

typedef struct {
    QString date;
    QString ff;
    QString dd;
    QString khiap;
    QString rain1h;
    QString rain24h;
} DataviewRow;

class DBManager
{
public:
    DBManager();
    ~DBManager();

    /*
     * |-----4-----|---------3--------|--------2--------|-----1-----|
     * |    root   | setting accounts | setting station |  operator |
    */
    enum StandardAcountPermission {
        ACC_PERMISSION_ROOT         = 0b00001111,   //15
        ACC_PERMISSION_ADMIN        = 0b00000111,   //7
        ACC_PERMISSION_EMPLOYEES    = 0b00000011,   //3
    };

    bool createDatabase();
    void initDb();
    bool isDbExists();

    /**********************Account Table*********************/
    void createAccountTable();
    bool addAccount(const QString &employeeid, const QString &username, const QString &password, const int &permission, const QString &fullname, const QString &description);
    bool changePassword(const QString &username, const QString &password);
    bool updateExistsAccount(const QString &employeeid, const QString &username, const QString &password, const int &permission, const QString &fullname, const QString &description);
    bool updateExistsAccount(AccountInformation &accInf);
    bool deleteAccount(const QString &username);
    AccountInformation getAccount(const QString &username);
    bool isAccountExists(const QString &username);
    QList<AccountInformation> getAccountList(uint8_t currentPermission);
    /********************************************************/

    /*******************Login History Table******************/
    void createLoginHistoryTable();
    bool addHistoryRow(QString employeeid, QString login, QString logout);
    bool updateHistoryRow(QString employeeid, QString login, QString logout);
    QList<LoginHistory> getLoginHistory(QString dateStart, QString dateEnd);
    /********************************************************/

    /*********************Dataview Table*********************/
    void createDataviewTable();
    bool addDataviewRow(DataviewRow &row);
    QList<DataviewRow> getDataviewList(QString dateStart, QString dateEnd);
    /********************************************************/

    static DBManager *getInstance();

private:
    static DBManager *m_instance;
};

#endif // DBMANAGER_H
