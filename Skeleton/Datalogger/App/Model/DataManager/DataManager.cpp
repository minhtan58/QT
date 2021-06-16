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
    DbManager::getInstance();
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
    }
    return "";
}

void DataManager::setData(int dpid, QString value)
{
    if(m_datapool.contains(dpid)) {
        if (getData(dpid) != value) {
            mutex.lock();
            m_datapool[dpid] = value;
            mutex.unlock();
            emit dataChanged(dpid);
//            DLOG(" %s : %s", getDataName(dpid).toStdString().data(), value.toStdString().data());
            return;
        }
    } else {
        DLOG("DPID: %d Incorrect", dpid);
    }
}

QString DataManager::getDataName(int dpId)
{
    if(m_dpName.contains(dpId)) {
        return m_dpName.value(dpId);
    }
    return "";
}

void DataManager::setHistoryDataList(const QList<CemsDataRow> &historyDataList)
{
    m_historyDataList = historyDataList;
}

QList<CemsDataRow> DataManager::getHistoryDataList() const
{
    return m_historyDataList;
}

void DataManager::resetHistoryDataList()
{
    if(!m_historyDataList.isEmpty()) {
        m_historyDataList.clear();
    }
}

void DataManager::setWorkingDataRow(QStringList &data)
{
    m_workingDataRow = data;
}

QStringList DataManager::getWorkingDataRow()
{
    return m_workingDataRow;
}

void DataManager::resetWorkingDataRow()
{
    if(m_workingDataRow.isEmpty()) {
        m_workingDataRow.clear();
    }
}

QList<CemsDataRow> DataManager::getMissingDataList() const
{
    return m_missingDataList;
}

void DataManager::setMissingDataList(const QList<CemsDataRow> &missingDataList)
{
    m_missingDataList = missingDataList;
}

void DataManager::resetMissingDataList()
{
    if(!m_missingDataList.isEmpty()) {
        m_missingDataList.clear();
    }
}

void DataManager::initData()
{
    INITDATA(CEMSEnum::DP_SYS_TIME);
    INITDATA(CEMSEnum::DP_SYS_DATE);
    INITDATA(CEMSEnum::DP_SYS_TIME_HOUR);
    INITDATA(CEMSEnum::DP_SYS_TIME_MINUTES);
    INITDATA(CEMSEnum::DP_SYS_DATE_YEAR);
    INITDATA(CEMSEnum::DP_SYS_DATE_MONTH);
    INITDATA(CEMSEnum::DP_SYS_DATE_DAY);

    INITDATA(CEMSEnum::DP_GENERAL_STATION_ID);
    INITDATA(CEMSEnum::DP_GENERAL_STATION_NAME);
    INITDATA(CEMSEnum::DP_GENERAL_RADIUS);
    INITDATA(CEMSEnum::DP_SYS_SETTINGS_TIME_AUTOMATIC_UPDATE);

    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_INTERVAL);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_TEST_CONNECTION);

    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_IP);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PORT);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_USER);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PASSWORD);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_INTERVAL);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_TEST_CONNECTION);

    INITDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME);
    INITDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE);
    INITDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_INTERVAL);
    INITDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_TEST_CONNECTION);
    INITDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_LIST_AVAIABLE_PORTNAME);

    INITDATA(CEMSEnum::DP_AMP_AIR_O2);
    INITDATA(CEMSEnum::DP_AMP_AIR_CO);
    INITDATA(CEMSEnum::DP_AMP_AIR_NO);
    INITDATA(CEMSEnum::DP_AMP_AIR_SO2);
    INITDATA(CEMSEnum::DP_AMP_TEMP);
    INITDATA(CEMSEnum::DP_AMP_OPP);
    INITDATA(CEMSEnum::DP_AMP_DUST_PM);
    INITDATA(CEMSEnum::DP_AMP_VEL);

    INITDATA(CEMSEnum::DP_PPM_AIR_O2);
    INITDATA(CEMSEnum::DP_PPM_AIR_CO);
    INITDATA(CEMSEnum::DP_PPM_AIR_NO);
    INITDATA(CEMSEnum::DP_PPM_AIR_NOX);
    INITDATA(CEMSEnum::DP_PPM_AIR_SO2);

    INITDATA(CEMSEnum::DP_AIR_O2);
    INITDATA(CEMSEnum::DP_AIR_CO);
    INITDATA(CEMSEnum::DP_AIR_NO);
    INITDATA(CEMSEnum::DP_AIR_NOX);
    INITDATA(CEMSEnum::DP_AIR_SO2);
    INITDATA(CEMSEnum::DP_TEMP);
    INITDATA(CEMSEnum::DP_OPP);
    INITDATA(CEMSEnum::DP_DUST_PM);
    INITDATA(CEMSEnum::DP_VEL);
    INITDATA(CEMSEnum::DP_FLOW);

    //SETTINGS
    INITDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE);
    INITDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_CO);
    INITDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NO);
    INITDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NOX);
    INITDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_SO2);

    //ALARM
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MAX);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_CO_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_CO_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_CO_MAX);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_NO_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_NO_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_NO_MAX);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_NOX_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_NOX_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_NOX_MAX);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_SO2_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_SO2_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_SO2_MAX);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_TEMP_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_TEMP_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_TEMP_MAX);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_OPP_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_OPP_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_OPP_MAX);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_MAX);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_VEL_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_VEL_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_VEL_MAX);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_FLOW_STATUS);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_FLOW_MIN);
    INITDATA(CEMSEnum::DP_SETTINGS_ALARM_FLOW_MAX);

    INITDATA(CEMSEnum::DP_STATUS_ALARM_O2);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_CO);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_NO);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_NOX);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_SO2);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_TEMP);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_OPP);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_DUST_PM);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_VEL);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_FLOW);
    INITDATA(CEMSEnum::DP_STATUS_ALARM_ON_COUNT);

    INITDATA(CEMSEnum::DP_SEARCH_TIME_HISTORY_DATA);
}
