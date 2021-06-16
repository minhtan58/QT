/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: UIBridge.cpp
    Create: 14/12/2017
    Author: Minh Tan

 ****************************************************************************/

#include "UIBridge.h"

UIBridge* UIBridge::m_uiBridge = nullptr;

UIBridge::UIBridge(QObject *parent)
    : QObject(parent)
{}

UIBridge *UIBridge::getInstance()
{
    if(m_uiBridge == nullptr)
        m_uiBridge = new UIBridge();
    return m_uiBridge;
}

UIBridge::~UIBridge()
{}

QString UIBridge::getDPData(int dpid)
{
    return DataManager::getInstance()->getData(dpid);
}

void UIBridge::setDPData(int dpid, QVariant value)
{
    DataManager::getInstance()->setData(dpid, value.toString());
}

void UIBridge::log(QString msg)
{
    DLOG("%s", msg.toStdString().data());
}

void UIBridge::sendEvent(QString objectName, int eventId, QString param)
{
    emit hmiEvent(objectName, eventId, param);
}
