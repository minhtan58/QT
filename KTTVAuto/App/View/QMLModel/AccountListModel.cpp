/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: LoginHistoryListModel.cpp
    Create: 09
    Author: Vuong Nguyen

 ****************************************************************************/

#include "AccountListModel.h"

AccountListModel::AccountListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_listElement = new QList<AccountListElement*>();
    m_feeder  = new AccountListFeeder(m_listElement, this);
    connect(m_feeder, SIGNAL(updateFetchDataStatus(int)), this, SLOT(updateFetchDataStatus(int)));
    connect(this, SIGNAL(terminateFetchData()), m_feeder, SLOT(quit()));
    fetchData();
}

AccountListModel::~AccountListModel()
{
    DLOG("~AccountListModel");
    if(m_listElement) {
        qDeleteAll(*m_listElement);
        m_listElement->clear();
        delete m_listElement;
        m_listElement = nullptr;
    }
}

int AccountListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_listElement->size();
}

QVariant AccountListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 ||
            index.row() >= m_listElement->size()){
        return QVariant();
    }
    const AccountListElement *dobj = m_listElement->at(index.row());

    switch (role) {
    case EMPLOYEEID:
        return QVariant::fromValue(dobj->employeeid());
    case PERMISSION:
        return QVariant::fromValue(dobj->permission());
    case USERNAME:
        return QVariant::fromValue(dobj->username());
    case PASSWORD:
        return QVariant::fromValue(dobj->password());
    case FULLNAME:
        return QVariant::fromValue(dobj->fullname());
    case DESCRIPTION:
        return QVariant::fromValue(dobj->description());
    default:
        return QVariant();
    }
}
QHash<int, QByteArray> AccountListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EMPLOYEEID] = "employeeid";
    roles[PERMISSION] = "permission";
    roles[USERNAME] = "username";
    roles[PASSWORD] = "password";
    roles[FULLNAME] = "fullname";
    roles[DESCRIPTION] = "description";
    return roles;
}

void AccountListModel::update()
{
    beginResetModel();
    endResetModel();
}

void AccountListModel::fetchData()
{
    m_feeder->start();
}

void AccountListModel::updateFetchDataStatus(int status)
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

void AccountListFeeder::run() {
    DLOG("Fetch data for AccountListModel");

    emit updateFetchDataStatus(FETCH_STARTING);
    if(m_listModel && m_listModel->size()) {
        qDeleteAll(*m_listModel);
        m_listModel->clear();
    }
    QList<AccountInformation> list = MODEL->getAccountList();
    for(int i = 0; i < list.size(); ++i) {
        m_listModel->append(new AccountListElement(list.at(i).id,
                                                   list.at(i).permission,
                                                   list.at(i).username,
                                                   list.at(i).password,
                                                   list.at(i).fullName,
                                                   list.at(i).description));
    }
    emit updateFetchDataStatus(FETCH_FINISHED);
}
