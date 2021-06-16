/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: DataviewListModel.cpp
    Create: 09
    Author: Vuong Nguyen

 ****************************************************************************/

#include "DataviewListModel.h"

DataviewListModel::DataviewListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_listElement = new QList<DataviewListElement*>();
    m_feeder  = new DataviewListFeeder(m_listElement, this);
    connect(m_feeder, SIGNAL(updateFetchDataStatus(int)), this, SLOT(updateFetchDataStatus(int)));
    connect(this, SIGNAL(terminateFetchData()), m_feeder, SLOT(quit()));
    fetchData();
}

DataviewListModel::~DataviewListModel()
{
    DLOG("~LoginHistoryListModel");
    if(m_listElement) {
        qDeleteAll(*m_listElement);
        m_listElement->clear();
        delete m_listElement;
        m_listElement = nullptr;
    }
}

int DataviewListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_listElement->size();
}

QVariant DataviewListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 ||
            index.row() >= m_listElement->size()){
        return QVariant();
    }
    const DataviewListElement *dobj = m_listElement->at(index.row());

    switch (role) {
    case DATE:
        return QVariant::fromValue(dobj->date());
    case FF:
        return QVariant::fromValue(dobj->ff());
    case DD:
        return QVariant::fromValue(dobj->dd());
    case KHIAP:
        return QVariant::fromValue(dobj->khiap());
    case RAIN1H:
        return QVariant::fromValue(dobj->rain1h());
    case RAIN24H:
        return QVariant::fromValue(dobj->rain24h());
    default:
        return QVariant();
    }
}
QHash<int, QByteArray> DataviewListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DATE] = "date";
    roles[FF] = "ff";
    roles[DD] = "dd";
    roles[KHIAP] = "khiap";
    roles[RAIN1H] = "rain1h";
    roles[RAIN24H] = "rain24h";
    return roles;
}

void DataviewListModel::update()
{
    beginResetModel();
    endResetModel();
}

void DataviewListModel::fetchData()
{
    m_feeder->start();
}

void DataviewListModel::updateFetchDataStatus(int status)
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

void DataviewListFeeder::run() {
    DLOG("Fetch data for DataviewListModel");
    if(MODEL->dataviewSearchDateStart().isEmpty() || MODEL->dataviewSearchDateEnd().isEmpty())
        return;

    emit updateFetchDataStatus(FETCH_STARTING);
    if(m_listModel && m_listModel->size()) {
        qDeleteAll(*m_listModel);
        m_listModel->clear();
    }
    QList<DataviewRow> list = MODEL->getDataviewList();
    for(int i = 0; i < list.size(); ++i) {
        m_listModel->append(new DataviewListElement(list.at(i).date,
                                                    list.at(i).ff,
                                                    list.at(i).dd,
                                                    list.at(i).khiap,
                                                    list.at(i).rain1h,
                                                    list.at(i).rain24h));
    }
    emit updateFetchDataStatus(FETCH_FINISHED);
}
