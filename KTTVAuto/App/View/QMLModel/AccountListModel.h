/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: LoginHistoryListModel.h
    Create: 09
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef ACCOUNTLISTMODEL_H
#define ACCOUNTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "Defines.h"
#include "Constants.h"
#include "HMIEvents.h"
#include "AppModel.h"
#include "UIBridge.h"

class AccountListElement
{
public:
    AccountListElement(QString employeeid, int permission, QString username, QString password, QString fullname, QString description) {
        m_employeeid = employeeid;
        m_permission = permission;
        m_username = username;
        m_password = password;
        m_fullname = fullname;
        m_description = description;
    }

    DECLARE_VAR(QString, employeeid)
    DECLARE_VAR(int, permission)
    DECLARE_VAR(QString, username)
    DECLARE_VAR(QString, password)
    DECLARE_VAR(QString, fullname)
    DECLARE_VAR(QString, description)

};

class AccountListFeeder : public QThread
{
    Q_OBJECT
public:
    explicit AccountListFeeder(QList<AccountListElement*> *listModel, QObject *parent = nullptr)
        : QThread(parent)
        , m_listModel(listModel)
    {}

signals:
    void updateFetchDataStatus(int status);

protected:
    void run();

private:
    QList<AccountListElement*> *m_listModel = nullptr;
};

class AccountListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AccountEnum {
        EMPLOYEEID = Qt::UserRole + 1,
        PERMISSION,
        USERNAME,
        PASSWORD,
        FULLNAME,
        DESCRIPTION,
    };

    explicit AccountListModel(QObject *parent = nullptr);
    ~AccountListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;
    void update();

public slots:
    void updateFetchDataStatus(int status);
    void fetchData();

signals:
    void fetchDataStarting();
    void fetchDataFinished();
    void terminateFetchData();

private:
    QList<AccountListElement*> *m_listElement;
    AccountListFeeder *m_feeder;
};

#endif // ACCOUNTLISTMODEL_H
