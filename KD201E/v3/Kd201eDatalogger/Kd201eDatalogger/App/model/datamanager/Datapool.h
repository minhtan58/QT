#ifndef DATAPOOL_H
#define DATAPOOL_H

#include <QObject>
#include <QMap>
#include <QHash>
#include <QMutex>

#include "common.h"
#include "KD201EEnum.h"
#include "SettingsLoader.h"

#define INITDATA(param) \
    m_datapool.insert((int)param,(QString)""); \
    m_dpName.insert((int)param, ((QString)#param).mid(12))

class Datapool : public QObject
{
    Q_OBJECT

public:
    explicit Datapool(QObject *parent = nullptr);
    static Datapool* getInstance();

    QString getData(int dpId);
    void setData(int dpid, QString value);
    QString getDataName(int dpId);

    void updateSettingsState();

    void setHistoryList(QList<DataRow> historyDatalist);
    QList<DataRow> getHistoryList();

signals:
    void dataChanged(int dpid, QString data);

public slots:
    void requestGetHistoryList(QString searchTime);

private:
    static Datapool *m_dataManager;
    QHash<int, QString> m_datapool;
    QHash<int, QString> m_dpName;
    QList<DataRow> m_historyDatalist;
    QMutex mutex;

    void initData();
};

#endif // DATAPOOL_H
