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

#include "Common.h"
#include "CEMSEnum.h"
#include "DbManager.h"

#define INITDATA(param) \
    m_datapool.insert((int)param, (QString)""); \
    m_dpName.insert((int)param, ((QString)#param).mid(10))

class DataManager : public QObject
{
    Q_OBJECT

public:
    explicit DataManager(QObject *parent = nullptr);
    static DataManager* getInstance();

    QString getData(int dpId);
    void setData(int dpid, QString value);
    QString getDataName(int dpId);

    //List data
    void setHistoryDataList(const QList<CemsDataRow> &historyDataList);
    QList<CemsDataRow> getHistoryDataList() const;
    void resetHistoryDataList();

    //
    void setWorkingDataRow(QStringList &data);
    QStringList getWorkingDataRow();
    void resetWorkingDataRow();

    QList<CemsDataRow> getMissingDataList() const;
    void setMissingDataList(const QList<CemsDataRow> &missingDataList);
    void resetMissingDataList();

signals:
    void dataChanged(int dpid);
    void event(QString objectName, int eventId, QString param);

public slots:

private:
    static DataManager *m_dataManager;
    QHash<int, QString> m_datapool;
    QHash<int, QString> m_dpName;
    QMutex mutex;

    QList<CemsDataRow> m_historyDataList;

    //
    QStringList m_workingDataRow;
    QList<CemsDataRow> m_missingDataList;

    void initData();
};

#endif // DATAMANAGER_H
