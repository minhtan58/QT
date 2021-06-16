#include "TopBarAdapter.h"

TopBarAdapter::TopBarAdapter(QQuickItem *container, QObject *parent)
    : QObject(parent)
{
    m_topbarContainer = container;
    m_topBarView = qvariant_cast<QObject*>(m_topbarContainer->property("item"));
}

void TopBarAdapter::initAppData()
{
    m_topBarView->setProperty("stationId",      QVariant::fromValue(GETDPDATA(CEMSEnum::DP_GENERAL_STATION_ID)));
    m_topBarView->setProperty("stationName",    QVariant::fromValue(GETDPDATA(CEMSEnum::DP_GENERAL_STATION_NAME)));
    m_topBarView->setProperty("systemDate",     QVariant::fromValue(GETDPDATA(CEMSEnum::DP_SYS_DATE)));
    m_topBarView->setProperty("systemTime",     QVariant::fromValue(GETDPDATA(CEMSEnum::DP_SYS_TIME)));
}

void TopBarAdapter::updateAppData(int dpid)
{
    QString data = GETDPDATA(dpid);
    switch (dpid) {
    case CEMSEnum::DP_SYS_DATE: {
        m_topBarView->setProperty("systemDate", QVariant::fromValue(data));
        break;
    }
    case CEMSEnum::DP_SYS_TIME:{
        m_topBarView->setProperty("systemTime", QVariant::fromValue(data));
        break;
    }
    case CEMSEnum::DP_GENERAL_STATION_NAME: {
        m_topBarView->setProperty("stationName", QVariant::fromValue(data));
        break;
    }
    case CEMSEnum::DP_STATUS_ALARM_ON_COUNT: {
        m_topBarView->setProperty("alarmCount", QVariant::fromValue(data));
        break;
    }
    default:
        break;
    }
}
