/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: Delivery.h
    Create: 14/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef DELIVERY_H
#define DELIVERY_H

#include "Common.h"
#include "DataManager.h"

class Delivery : public QObject
{
    Q_OBJECT
public:
    explicit Delivery(QObject *parent = nullptr);
    static Delivery* getInstance();
    ~Delivery();
    Q_INVOKABLE QString getDPData(int dpid);
    Q_INVOKABLE void setDPData(int dpid, QString value);
    Q_INVOKABLE void log(QString msg);

    void sendEvent(QString objectName, int eventId, QString param);

signals:
    void hmiEvent(QString objectName, int eventId, QString param);
    void keyboardEvent(int keyType, QString keyValue);
    void dataTransfer(int eventId, void *data);

private:
    static Delivery *m_delivery;
};

#endif // DELIVERY_H
