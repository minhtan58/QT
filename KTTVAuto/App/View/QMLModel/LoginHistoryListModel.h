/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: LoginHistoryListModel.h
    Create: 09
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef LOGINHISTORYLISTMODEL_H
#define LOGINHISTORYLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "Defines.h"
#include "Constants.h"
#include "HMIEvents.h"
#include "AppModel.h"
#include "UIBridge.h"

class LoginHistoryListElement
{
public:
    LoginHistoryListElement(QString employeeid, QString fullname, QString login, QString logout) {
        m_employeeid = employeeid;
        m_fullname = fullname;
        m_login = login;
        m_logout = logout;
    }

    DECLARE_VAR(QString, employeeid)
    DECLARE_VAR(QString, fullname)
    DECLARE_VAR(QString, login)
    DECLARE_VAR(QString, logout)
};

class LoginHistoryListFeeder : public QThread
{
    Q_OBJECT
public:
    explicit LoginHistoryListFeeder(QList<LoginHistoryListElement*> *listModel, QObject *parent = nullptr)
        : QThread(parent)
        , m_listModel(listModel)
    {}

signals:
    void updateFetchDataStatus(int status);

protected:
    void run();

private:
    QList<LoginHistoryListElement*> *m_listModel = nullptr;
};

class LoginHistoryListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LoginHistoryEnum {
        EMPLOYEEID = Qt::UserRole + 1,
        FULLNAME,
        LOGIN,
        LOGOUT
    };

    explicit LoginHistoryListModel(QObject *parent = nullptr);
    ~LoginHistoryListModel();

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
    QList<LoginHistoryListElement*> *m_listElement;
    LoginHistoryListFeeder *m_feeder;
};

#endif // LOGINHISTORYLISTMODEL_H
