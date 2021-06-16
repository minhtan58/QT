/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: DataManager.h
    Create: 13/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QMap>
#include <QHash>
#include <QList>
#include <QMutex>

#include "Defines.h"
#include "DPID.h"

#define INSERT(param) \
    m_datapool.insert((int)param, (QString)""); \
    m_dpName.insert((int)param, ((QString)#param).mid(6))

class DataManager : public QObject
{
    Q_OBJECT

public:
    explicit DataManager(QObject *parent = nullptr);
    static DataManager* getInstance();

    QString getData(int dpId);
    void setData(int dpid, QString value);
    QString getDataName(int dpId);

    void setBlockingTemp(bool isBlocking);
    bool isBlockingTemp();

signals:
    void dataChanged(int dpid, QString value);
    void event(QString objectName, int eventId, QString param);

public slots:

private:
    static DataManager *m_dataManager;
    QHash<int, QString> m_datapool;
    QHash<int, QString> m_dpName;

    bool m_isBlockingTemp;

    void initData();
};

#endif // DATAMANAGER_H
