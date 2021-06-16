/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: UIBridge.cpp
    Create: 14/12/2017
    Author: Vuong Nguyen

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
{
    MCR_DEL_PTR(m_uiBridge);
}

void UIBridge::log(QString msg)
{
    DLOG("%s", msg.toStdString().data());
}

void UIBridge::sendEvent(QString objectName, int eventId, QString param)
{
    emit hmiEvent(objectName, eventId, param);
}

void UIBridge::setDelayEvent(QString objectName, int eventId, QString param)
{
    m_delayEvent = new EventElement{objectName, eventId, param};
}

void UIBridge::resetDelayEvent()
{
    if(m_delayEvent != nullptr) {
        delete m_delayEvent;
        m_delayEvent = nullptr;
    }
}

void UIBridge::emitDelayEvent()
{
    if(m_delayEvent != nullptr) {
        emit hmiEvent(m_delayEvent->objectName, m_delayEvent->eventId, m_delayEvent->param);
        delete m_delayEvent;
        m_delayEvent = nullptr;
    }
}
