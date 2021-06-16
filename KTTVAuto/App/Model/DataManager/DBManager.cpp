/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: SettingsDbManager.cpp
    Create: 20
    Author: Vuong Nguyen

 ****************************************************************************/

#include "DBManager.h"

DBManager* DBManager::m_instance = nullptr;

DBManager::DBManager()
{
    createDatabase();
    initDb();
}

DBManager::~DBManager()
{
    QSqlDatabase::removeDatabase("QSQLITE");
}

DBManager *DBManager::getInstance()
{
    if(m_instance == nullptr) {
        m_instance = new DBManager();
    }
    return m_instance;
}

bool DBManager::createDatabase()
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

void DBManager::initDb()
{
    if(isDbExists()) {
        QSqlDatabase database = QSqlDatabase::database();
        if (!database.tables().contains("Accounts")) {
            createAccountTable();
        }
        if (!database.tables().contains("LoginHistory")) {
            createLoginHistoryTable();
        }
        if (!database.tables().contains("Dataview")) {
            createDataviewTable();
        }
        addAccount(CST_ROOT_ID, CST_ROOT_USER, CST_ROOT_PASSWORD, ACC_PERMISSION_ROOT, "Nguyễn Đức Vượng", "Root");
        addAccount("QuangHv", "hoangquang", "123456", ACC_PERMISSION_ADMIN, "Hoàng Văn Quang", "Quản Trị Hệ Thống");
//        addAccount("guest", "guest", "123", ACC_PERMISSION_GUEST, "Guest", "Guest");
        addAccount("user1", "user1", "123456", ACC_PERMISSION_EMPLOYEES, "Quan Trắc Viên 1", "Quan Trắc Viên Khí Tượng");
        addAccount("user2", "user2", "123456", ACC_PERMISSION_EMPLOYEES, "Quan Trắc Viên 2", "Quan Trắc Viên Khí Tượng");
    }
}

void DBManager::createAccountTable()
{
    QSqlDatabase database = QSqlDatabase::database();
    const QString createSQL = "CREATE TABLE IF NOT EXISTS Accounts("
                              "employeeid TEXT NOT NULL,"
                              "username TEXT NOT NULL,"
                              "password TEXT NOT NULL,"
                              "permission INT NOT NULL,"
                              "fullname TEXT, "
                              "description TEXT);";
    QSqlQuery query(database);
    if (query.exec(createSQL)) {
        DLOG("Table creation query execute successfully");
    } else {
        DLOG("Create table error: %s", database.lastError().text().toStdString().data());
    }
    database.close();
}

bool DBManager::addAccount(const QString &employeeid, const QString &username, const QString &password, const int &permission, const QString &fullname, const QString &description)
{
    if(!isAccountExists(username)) {
        QSqlDatabase database = QSqlDatabase::database();
        if (!database.tables().contains("Accounts")) {
            DLOG("Create record error: Accounts table does not exist.");
        } else {
            QSqlQuery query(database);
            query.prepare("INSERT INTO Accounts(employeeid, username, password, permission, fullname, description) VALUES (:employeeid, :username, :password, :permission, :fullname, :description);");
            query.bindValue(":employeeid", employeeid);
            query.bindValue(":username", username);
            query.bindValue(":password", password);
            query.bindValue(":permission", permission);
            query.bindValue(":fullname", fullname);
            query.bindValue(":description", description);
            if (query.exec()) {
                DLOG("Account created");
                return true;
            } else {
                DLOG("Create account error: %s", database.lastError().text().toStdString().data());
            }
        }
        database.close();
    } /*else {
        DLOG("Account is exists!");
    }*/
    return false;
}

bool DBManager::changePassword(const QString &username, const QString &password)
{
    if(isAccountExists(username)) {
        QSqlDatabase database = QSqlDatabase::database();
        if (!database.tables().contains("Accounts")) {
            DLOG("Accounts table does not exist.");
        } else {
            QSqlQuery query(database);
            query.prepare("UPDATE Accounts SET password = :password WHERE username = :username;");
            query.bindValue(":username", username);
            query.bindValue(":password", password);
            if (query.exec()) {
                DLOG("Change password successful");
                return true;
            } else {
                DLOG("Change password record error: %s", database.lastError().text().toStdString().data());
            }
        }
        database.close();
    } /*else {
        DLOG("Can't change password for %s, account not exists!", username.toStdString().data());
    }*/
    return false;
}

bool DBManager::updateExistsAccount(const QString &employeeid, const QString &username, const QString &password, const int &permission, const QString &fullname, const QString &description)
{
    if(isAccountExists(username)) {
        QSqlDatabase database = QSqlDatabase::database();
        if (!database.tables().contains("Accounts")) {
            DLOG("Accounts table does not exist.");
        } else {
            QSqlQuery query(database);
            query.prepare("UPDATE Accounts "
                          "SET password = :_password, employeeid = :_employeeid, username = :_username, password = :_password, permission = :_permission, fullname = :_fullname, description = :_description "
                          "WHERE username = :_username;");
            query.bindValue(":_employeeid", employeeid);
            query.bindValue(":_username", username);
            query.bindValue(":_password", password);
            query.bindValue(":_permission", permission);
            query.bindValue(":_fullname", fullname);
            query.bindValue(":_description", description);
            if (query.exec()) {
                DLOG("Update account successful");
                return true;
            } else {
                DLOG("Update account error: %s", database.lastError().text().toStdString().data());
            }
        }
        database.close();
    } /*else {
        DLOG("Can't change password for %s, account not exists!", username.toStdString().data());
    }*/
    return false;
}

bool DBManager::updateExistsAccount(AccountInformation &accInf)
{
    return updateExistsAccount(accInf.id, accInf.username, accInf.password, accInf.permission, accInf.fullName, accInf.description);
}

bool DBManager::deleteAccount(const QString &username)
{
    if(isAccountExists(username)) {
        QSqlDatabase database = QSqlDatabase::database();
        if (!database.tables().contains("Accounts")) {
            DLOG("Accounts table does not exist.");
        } else {
            QSqlQuery query(database);
            query.prepare("DELETE FROM Accounts WHERE username = :_username;");
            query.bindValue(":_username", username);
            if (query.exec()) {
                DLOG("Delete account %s successful", username.toStdString().data());
                return true;
            } else {
                DLOG("Update account error: %s", database.lastError().text().toStdString().data());
            }
        }
        database.close();
    }
    return false;
}

AccountInformation DBManager::getAccount(const QString &username)
{
    AccountInformation accInf = {"", 0, "", "", "", ""};
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("Accounts")) {
        DLOG("Select record error: Accounts table does not exist.");
    } else {
        QSqlQuery query(database);
        query.prepare("SELECT * FROM Accounts WHERE username = (:username);");
        query.bindValue(":username", username);
        if (query.exec()) {
            while (query.next()) {
                QSqlRecord record = query.record();
                if(!record.value("employeeid").toString().isEmpty()) {
                    accInf.id = record.value("employeeid").toString();
                    accInf.username = record.value("username").toString();
                    accInf.password = record.value("password").toString();
                    accInf.permission = record.value("permission").toInt();
                    accInf.fullName = record.value("fullname").toString();
                    accInf.description = record.value("description").toString();
                    break;
                }
            }
        }
    }
    database.close();
    return accInf;
}

bool DBManager::isAccountExists(const QString &username)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("Accounts")) {
        DLOG("Select record error: Accounts table does not exist.");
    } else {
        QSqlQuery query(database);
        query.prepare("SELECT username FROM Accounts WHERE username = (:username);");
        query.bindValue(":username", username);
        if (query.exec()) {
            if(query.next()) {
//                DLOG("DB Contains account %s", username.toStdString().data());
                database.close();
                return true;
            }

        } else {
            DLOG("Select record error: %s", database.lastError().text().toStdString().data());
        }
    }
    database.close();
    return false;
}

QList<AccountInformation> DBManager::getAccountList(uint8_t currentPermission)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("Accounts")) {
        DLOG("Select record error: Accounts table does not exist.");
    } else {
        DLOG("Request get account with permission = %d", currentPermission);
        QSqlQuery query(database);
        query.prepare("SELECT * FROM Accounts WHERE permission <= (:currentPermission);");
        query.bindValue(":currentPermission", currentPermission);
        if (query.exec()) {
            QList<AccountInformation> list;
            while(query.next()) {
                AccountInformation element;
                QSqlRecord record = query.record();
                element.id = record.value("employeeid").toString();
                element.username = record.value("username").toString();
                element.password = record.value("password").toString();
                element.permission = record.value("permission").toInt();
                element.fullName = record.value("fullname").toString();
                element.description = record.value("description").toString();
                list.append(element);
            }
            return list;
        } else {
            DLOG("Select record error: %s", database.lastError().text().toStdString().data());
        }
    }
//    return NULL;
    database.close();
}

void DBManager::createLoginHistoryTable()
{
    QSqlDatabase database = QSqlDatabase::database();
    const QString createSQL = "CREATE TABLE IF NOT EXISTS LoginHistory("
                              "employeeid INT NOT NULL, "
                              "login DATETIME, "
                              "logout DATETIME);";
    QSqlQuery query(database);
    if (query.exec(createSQL)) {
        DLOG("Table creation query execute successfully");
    } else {
        DLOG("Create table error: %s", database.lastError().text().toStdString().data());
    }
    database.close();
}

bool DBManager::addHistoryRow(QString employeeid, QString login, QString logout)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("LoginHistory")) {
        DLOG("Create record error: LoginHistory table does not exist.");
    } else {
        QSqlQuery query(database);
        query.prepare("INSERT INTO LoginHistory(employeeid, login, logout) VALUES (:employeeid, :login, :logout);");
        query.bindValue(":employeeid", employeeid);
        query.bindValue(":login", login);
        query.bindValue(":logout", logout);
        if (query.exec()) {
            DLOG("LoginHistory insert successful!");
            return true;
        } else {
            DLOG("LoginHistory insert error: %s", database.lastError().text().toStdString().data());
        }
    }
    database.close();
    return false;
}

bool DBManager::updateHistoryRow(QString employeeid, QString login, QString logout)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("LoginHistory")) {
        DLOG("LoginHistory table does not exist.");
    } else {
        QSqlQuery query(database);
        query.prepare("UPDATE LoginHistory SET logout = :logout WHERE employeeid = :employeeid AND login = :login;");
        query.bindValue(":employeeid", employeeid);
        query.bindValue(":login", login);
        query.bindValue(":logout", logout);
        if (query.exec()) {
            DLOG("Change logout successful");
            return true;
        } else {
            DLOG("Change logout record error: %s", database.lastError().text().toStdString().data());
        }
    }
    database.close();
    return false;
}

QList<LoginHistory> DBManager::getLoginHistory(QString dateStart, QString dateEnd)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("Accounts") || !database.tables().contains("LoginHistory")) {
        DLOG("Select record error: Accounts table does not exist.");
    } else {
        QSqlQuery query(database);
        QString command = QString("SELECT Accounts.employeeid,fullname,login,logout FROM Accounts,LoginHistory "
                                  "WHERE login BETWEEN '%1 00:00:00' AND '%2 23:59:59' AND Accounts.employeeid = LoginHistory.employeeid "
                                  "ORDER BY datetime(login);").arg(dateStart).arg(dateEnd);
        query.prepare(command);
        if (query.exec()) {
            QList<LoginHistory> listLogin;
            while(query.next()) {
                LoginHistory loginHistory;
                QSqlRecord record = query.record();
                loginHistory.id = record.value("employeeid").toString();
                loginHistory.fullname = record.value("fullname").toString();
                loginHistory.logindate = record.value("login").toString();
                loginHistory.logoutdate = record.value("logout").toString();
                listLogin.append(loginHistory);
            }
            return listLogin;
        } else {
            DLOG("Select record error: %s", database.lastError().text().toStdString().data());
        }
    }
//    return NULL;
    database.close();
}

void DBManager::createDataviewTable()
{
    QSqlDatabase database = QSqlDatabase::database();
    const QString createSQL = "CREATE TABLE IF NOT EXISTS Dataview("
                              "date DATETIME NOT NULL, "
                              "ff TEXT, "
                              "dd TEXT, "
                              "khiap TEXT, "
                              "rain1h TEXT, "
                              "rain24h TEXT);";
    QSqlQuery query(database);
    if (query.exec(createSQL)) {
        DLOG("Table creation query execute successfully");
    } else {
        DLOG("Create table error: %s", database.lastError().text().toStdString().data());
    }
    database.close();
}

bool DBManager::addDataviewRow(DataviewRow &row)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("Dataview")) {
        DLOG("Create record error: Dataview table does not exist.");
    } else {
        QSqlQuery query(database);
        query.prepare("INSERT INTO Dataview(date, ff, dd, khiap, rain1h, rain24h) VALUES (:date, :ff, :dd, :khiap, :rain1h, :rain24h);");
        query.bindValue(":date", row.date);
        query.bindValue(":ff", row.ff);
        query.bindValue(":dd", row.dd);
        query.bindValue(":khiap", row.khiap);
        query.bindValue(":rain1h", row.rain1h);
        query.bindValue(":rain24h", row.rain24h);
        if (query.exec()) {
            DLOG("Dataview insert successful!");
            return true;
        } else {
            DLOG("Dataview insert error: %s", database.lastError().text().toStdString().data());
        }
    }
    database.close();
    return false;
}

QList<DataviewRow> DBManager::getDataviewList(QString dateStart, QString dateEnd)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("Dataview")) {
        DLOG("Select record error: Dataview table does not exist.");
    } else {
        QSqlQuery query(database);
        QString command = QString("SELECT * FROM Dataview "
                                  "WHERE date BETWEEN '%1 00:00:00' AND '%2 23:59:59' "
                                  "ORDER BY datetime(date);").arg(dateStart).arg(dateEnd);
        query.prepare(command);
        if (query.exec()) {
            QList<DataviewRow> list;
            while(query.next()) {
                DataviewRow element;
                QSqlRecord record = query.record();
                element.date = record.value("date").toString();
                element.ff = record.value("ff").toString();
                element.dd = record.value("dd").toString();
                element.khiap = record.value("khiap").toString();
                element.rain1h = record.value("rain1h").toString();
                element.rain24h = record.value("rain24h").toString();
                list.append(element);
            }
            return list;
        } else {
            DLOG("Select record error: %s", database.lastError().text().toStdString().data());
        }
    }
    database.close();
}

bool DBManager::isDbExists()
{
    return QFile::exists(PH_DB);
}
