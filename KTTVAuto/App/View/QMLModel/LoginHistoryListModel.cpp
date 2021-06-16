/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: LoginHistoryListModel.cpp
    Create: 09
    Author: Vuong Nguyen

 ****************************************************************************/

#include "LoginHistoryListModel.h"

LoginHistoryListModel::LoginHistoryListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_listElement = new QList<LoginHistoryListElement*>();
    m_feeder  = new LoginHistoryListFeeder(m_listElement, this);
    connect(m_feeder, SIGNAL(updateFetchDataStatus(int)), this, SLOT(updateFetchDataStatus(int)));
    connect(this, SIGNAL(terminateFetchData()), m_feeder, SLOT(quit()));
    fetchData();
}

LoginHistoryListModel::~LoginHistoryListModel()
{
    DLOG("~LoginHistoryListModel");
    if(m_listElement) {
        qDeleteAll(*m_listElement);
        m_listElement->clear();
        delete m_listElement;
        m_listElement = nullptr;
    }
}

int LoginHistoryListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_listElement->size();
}

QVariant LoginHistoryListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 ||
            index.row() >= m_listElement->size()){
        return QVariant();
    }
    const LoginHistoryListElement *dobj = m_listElement->at(index.row());

    switch (role) {
    case EMPLOYEEID:
        return QVariant::fromValue(dobj->employeeid());
    case FULLNAME:
        return QVariant::fromValue(dobj->fullname());
    case LOGIN:
        return QVariant::fromValue(dobj->login());
    case LOGOUT:
        return QVariant::fromValue(dobj->logout());
    default:
        return QVariant();
    }
}
QHash<int, QByteArray> LoginHistoryListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EMPLOYEEID] = "employeeid";
    roles[FULLNAME] = "fullname";
    roles[LOGIN] = "login";
    roles[LOGOUT] = "logout";
    return roles;
}

void LoginHistoryListModel::update()
{
    beginResetModel();
    endResetModel();
}

void LoginHistoryListModel::fetchData()
{
    m_feeder->start();
}

void LoginHistoryListModel::updateFetchDataStatus(int status)
{
    switch (status) {
    case FETCH_IDLE:
    case FETCH_STARTING:
        DLOG("Fetch Starting");
        emit fetchDataStarting();
        break;
    case FETCH_FINISHED:
        DLOG("Fetch Finished, list size: %d", m_listElement->size());
        update();
        emit fetchDataFinished();
        break;
    default:
        break;
    }
}

void LoginHistoryListFeeder::run() {
    DLOG("Fetch data for LoginHistoryListModel");
    if(MODEL->historySearchDateStart().isEmpty() || MODEL->historySearchDateEnd().isEmpty())
        return;

    emit updateFetchDataStatus(FETCH_STARTING);
    if(m_listModel && m_listModel->size()) {
        qDeleteAll(*m_listModel);
        m_listModel->clear();
    }
    QList<LoginHistory> list = MODEL->getLoginHistoryList();
    for(int i = 0; i < list.size(); ++i) {
        m_listModel->append(new LoginHistoryListElement(list.at(i).id,
                                                        list.at(i).fullname,
                                                        list.at(i).logindate,
                                                        list.at(i).logoutdate));
    }
    emit updateFetchDataStatus(FETCH_FINISHED);
}
