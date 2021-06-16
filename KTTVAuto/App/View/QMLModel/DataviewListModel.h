/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: DataviewListModel.h
    Create: 09
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef DATAVIEWLISTMODEL_H
#define DATAVIEWLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "Defines.h"
#include "Constants.h"
#include "HMIEvents.h"
#include "AppModel.h"
#include "UIBridge.h"

class DataviewListElement
{
public:
    DataviewListElement(QString date, QString ff, QString dd, QString khiap, QString rain1h, QString rain24h) {
        m_date = date;
        m_ff = ff;
        m_dd = dd;
        m_khiap = khiap;
        m_rain1h = rain1h;
        m_rain24h = rain24h;
    }

    DECLARE_VAR(QString, date)
    DECLARE_VAR(QString, ff)
    DECLARE_VAR(QString, dd)
    DECLARE_VAR(QString, khiap)
    DECLARE_VAR(QString, rain1h)
    DECLARE_VAR(QString, rain24h)
};

class DataviewListFeeder : public QThread
{
    Q_OBJECT
public:
    explicit DataviewListFeeder(QList<DataviewListElement*> *listModel, QObject *parent = nullptr)
        : QThread(parent)
        , m_listModel(listModel)
    {}

signals:
    void updateFetchDataStatus(int status);

protected:
    void run();

private:
    QList<DataviewListElement*> *m_listModel = nullptr;
};

class DataviewListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LoginHistoryEnum {
        DATE = Qt::UserRole + 1,
        FF,
        DD,
        KHIAP,
        RAIN1H,
        RAIN24H
    };

    explicit DataviewListModel(QObject *parent = nullptr);
    ~DataviewListModel();

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
    QList<DataviewListElement*> *m_listElement;
    DataviewListFeeder *m_feeder;
    int m_dataviewType = TYPE_KHITUONG;
};

#endif // DATAVIEWLISTMODEL_H
