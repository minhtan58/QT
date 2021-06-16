#ifndef MONITORINGHANDLER_H
#define MONITORINGHANDLER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QTcpSocket>

#include "Delivery.h"
#include "Common.h"
#include "DataManager.h"
#include "Defines.h"

class MonitoringHandler : public QObject
{
    Q_OBJECT
public:
    explicit MonitoringHandler(QObject *parent = nullptr);

public slots:
    void handleEvent(QString objectName, int eventId, QString params);
    void requestResetSpi();
    void unBlockingTemp();

private:
    QTimer *m_timResetSpi = nullptr;
    QTimer *m_timBlockTemp = nullptr;
};

//thread define
class MonitoringHandlerThread : public QThread
{
    Q_OBJECT
public:
    MonitoringHandlerThread(QObject *parent = nullptr)
        : QThread(parent)
    {}

protected:
    void run() {
        DLOG("Start");
        MonitoringHandler handler;
        exec();
    }
};

#endif // MONITORINGHANDLER_H
