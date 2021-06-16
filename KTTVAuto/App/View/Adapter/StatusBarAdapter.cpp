/****************************************************************************

    Copyright (C) 2018 by LGE
    File: StatusBarAdapter.cpp
    Create: 21
    Author: Vuong Nguyen

 ****************************************************************************/

#include "StatusBarAdapter.h"

StatusBarAdapter::StatusBarAdapter(QQuickItem *container, QObject *parent)
    : QObject(parent)
{
    m_statusBarContainer = container;
    m_statusBarView = qvariant_cast<QObject*>(m_statusBarContainer->property("item"));
}

void StatusBarAdapter::initAppData()
{
    m_statusBarView->setProperty("systemDate",     QVariant::fromValue(GETDPDATA(HMIEvents::DP_SYS_DATE)));
    m_statusBarView->setProperty("systemTime",     QVariant::fromValue(GETDPDATA(HMIEvents::DP_SYS_TIME)));
}

void StatusBarAdapter::updateAppData(int dpid)
{
    QString data = GETDPDATA(dpid);
    switch (dpid) {
    case HMIEvents::DP_SYS_DATE: {
        m_statusBarView->setProperty("systemDate", QVariant::fromValue(data));
        break;
    }
    case HMIEvents::DP_SYS_TIME:{
        m_statusBarView->setProperty("systemTime", QVariant::fromValue(data));
        break;
    }
    default:
        break;
    }
}
