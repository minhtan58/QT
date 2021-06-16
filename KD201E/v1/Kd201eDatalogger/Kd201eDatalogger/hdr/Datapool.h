#ifndef DATAPOOL_H
#define DATAPOOL_H

#include <QObject>
#include <QMap>
#include <QHash>
#include <QMutex>

#include "common.h"
#include "Kd201eEnum.h"

#define INITDATA(param) \
    m_datapool.insert((int)param, (QString)""); \
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

    void loadSettingsState();

signals:
    void dataChanged(int dpid);

public slots:

private:
    static Datapool *m_dataManager;
    QHash<int, QString> m_datapool;
    QHash<int, QString> m_dpName;
    QMutex mutex;

    void initData();
};

#endif // DATAPOOL_H
