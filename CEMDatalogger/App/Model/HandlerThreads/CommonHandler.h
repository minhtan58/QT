#ifndef COMMONHANDLER_H
#define COMMONHANDLER_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "Common.h"
#include "DataManager.h"
#include "CEMSEnum.h"

class CommonHandler : public QObject
{
    Q_OBJECT
public:
    explicit CommonHandler(QObject *parent = nullptr);

public slots:
    void eventHandler(QString objectName, int eventId, QString param);
    void updateAppData(int dpid);
};

//thread define
class CommonHandlerThread : public QThread
{
    Q_OBJECT
public:
    CommonHandlerThread(QObject *parent = nullptr)
        : QThread(parent)
    {}

protected:
    void run() {
        DLOG("Start");
        CommonHandler handler;
        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        connect(DataManager::getInstance(), SIGNAL(dataChanged(int)), &handler, SLOT(updateAppData(int)));
        exec();
    }
};

#endif // COMMONHANDLER_H
