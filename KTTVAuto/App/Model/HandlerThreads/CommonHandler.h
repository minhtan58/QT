#ifndef COMMONHANDLER_H
#define COMMONHANDLER_H

#include <QObject>
#include <QThread>

#include "Common.h"
#include "AppModel.h"
#include "hmievents.h"
#include "UIBridge.h"
#include "SIM800C.h"

class CommonHandler : public QObject
{
    Q_OBJECT
public:
    explicit CommonHandler(QObject *parent = nullptr);

public slots:
    void eventHandler(QString objectName, int eventId, QString param);
};

//thread define
class CommonHandlerThread : public QThread
{
    Q_OBJECT
public:
    CommonHandlerThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() {
        DLOG("Starting...");
        CommonHandler handler;
        connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), &handler, SLOT(eventHandler(QString,int,QString)));
        exec();
    }
};

#endif // COMMONHANDLER_H
