/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: Delivery.cpp
    Create: 14/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#include "Delivery.h"

Delivery* Delivery::m_delivery = nullptr;

Delivery::Delivery(QObject *parent)
    : QObject(parent)
{}

Delivery *Delivery::getInstance()
{
    if(m_delivery == nullptr)
        m_delivery = new Delivery();
    return m_delivery;
}

Delivery::~Delivery()
{}

QString Delivery::getDPData(int dpid)
{
    return DataManager::getInstance()->getData(dpid);
}

void Delivery::setDPData(int dpid, QVariant value)
{
    DataManager::getInstance()->setData(dpid, value.toString());
}

void Delivery::log(QString msg)
{
    DLOG("%s", msg.toStdString().data());
}

void Delivery::sendEvent(QString objectName, int eventId, QString param)
{
    emit hmiEvent(objectName, eventId, param);
}
