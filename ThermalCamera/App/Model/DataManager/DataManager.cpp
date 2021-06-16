/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: DataManager.cpp
    Create: 13/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#include "DataManager.h"

DataManager* DataManager::m_dataManager = nullptr;

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    initData();
    m_isBlockingTemp = false;
}

DataManager *DataManager::getInstance()
{
    if(m_dataManager == nullptr) {
        m_dataManager = new DataManager();
    }
    return m_dataManager;
}

QString DataManager::getData(int dpId)
{
    if(m_datapool.contains(dpId)) {
        return m_datapool.value(dpId);
    } else {
        DLOG("DP not include %d", dpId);
        return "";
    }

}

void DataManager::setData(int dpid, QString value)
{
    if(m_datapool.contains(dpid)) {
        if (getData(dpid) != value) {
            QMutex mutex;
            mutex.lock();
            m_datapool[dpid] = value;
            mutex.unlock();
            emit dataChanged(dpid, value);
//            DLOG(" %s : %s", getDataName(dpid).toStdString().data(), value.toStdString().data());
            return;
        }
    } else {
        DLOG("DPID: %d incorrect", dpid);
    }
}

QString DataManager::getDataName(int dpId)
{
    if(m_dpName.contains(dpId)) {
        return m_dpName.value(dpId);
    }
    return "";
}

void DataManager::setBlockingTemp(bool isBlocking)
{
    m_isBlockingTemp = isBlocking;
}

bool DataManager::isBlockingTemp()
{
    return m_isBlockingTemp;
}

void DataManager::initData()
{
    INSERT(DPID::DP_THERMAL_TEMPERATURE);
    INSERT(DPID::DP_THERMAL_TEMPERATURE_ALARM_NOTIFY);
    INSERT(DPID::DP_SETTINGS_DEVICEID);
    INSERT(DPID::DP_SETTINGS_DEVICENAME);
    INSERT(DPID::DP_SETTINGS_DEVICETYPE);
    INSERT(DPID::DP_SETTINGS_THRESOLD_MAXTEMP);
    INSERT(DPID::DP_SETTINGS_THRESOLD_MINTEMP);
    INSERT(DPID::DP_SETTINGS_VERIFYTIME);
    INSERT(DPID::DP_SETTINGS_SERVERIP);
    INSERT(DPID::DP_SETTINGS_SERVERPORT);
    INSERT(DPID::DP_STATUS_SERVER_CONNECTED);
    INSERT(DPID::DP_SYSTEM_CPU_TEMPERATURE);
}
