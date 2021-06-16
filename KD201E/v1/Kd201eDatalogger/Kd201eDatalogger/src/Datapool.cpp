#include "Datapool.h"

Datapool* Datapool::m_dataManager = nullptr;

Datapool::Datapool(QObject *parent)
    : QObject(parent)
{
    initData();
}

Datapool *Datapool::getInstance()
{
    if(m_dataManager == nullptr)
        m_dataManager = new Datapool();
    return m_dataManager;
}

QString Datapool::getData(int dpId)
{
    if(m_datapool.contains(dpId)) {
        mutex.lock();
        QString dpValue = m_datapool.value(dpId);
        mutex.unlock();
        return dpValue;
    }
    return "";
}

void Datapool::setData(int dpid, QString value)
{
    if(m_datapool.contains(dpid)) {
        if (getData(dpid) != value) {
            mutex.lock();
            m_datapool[dpid] = value;
            mutex.unlock();
            emit dataChanged(dpid);
            DLOG("%s : %s", getDataName(dpid).toStdString().data(), value.toStdString().data());
            return;
        }
    }
    else
        DLOG("DPID: %d incorrect", dpid);
}

QString Datapool::getDataName(int dpId)
{
    if(m_dpName.contains(dpId)) {
        mutex.lock();
        QString dpValue = m_dpName.value(dpId);
        mutex.unlock();
        return dpValue;
    }
    return "";
}

void Datapool::initData()
{
    INITDATA(Kd201eEnum::DP_VARIABLES_CONTROLLER);
    INITDATA(Kd201eEnum::DP_VARIABLES_SERIAL);
    INITDATA(Kd201eEnum::DP_VARIABLES_SOFTWARE);
    INITDATA(Kd201eEnum::DP_VARIABLES_TIME);
    INITDATA(Kd201eEnum::DP_VARIABLES_PH);
    INITDATA(Kd201eEnum::DP_VARIABLES_OC);
    INITDATA(Kd201eEnum::DP_VARIABLES_TSS);
    INITDATA(Kd201eEnum::DP_VARIABLES_FLOW);
    INITDATA(Kd201eEnum::DP_VARIABLES_COD);
    INITDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME);
    INITDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME);
    INITDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE);
    INITDATA(Kd201eEnum::DP_SETTINGS_STATIONLINK);
    INITDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL);
    INITDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP);
    INITDATA(Kd201eEnum::DP_SETTINGS_FTP_USER);
    INITDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW);
    INITDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML);
    INITDATA(Kd201eEnum::DP_COMMON_IS_STATION_CONNETED);
    INITDATA(Kd201eEnum::DP_COMMON_IS_FTP_CONNETED);
    INITDATA(Kd201eEnum::DP_COMMON_SETTINGS_STATE);
    INITDATA(Kd201eEnum::DP_COMMON_CURRENT_WORKINGFILE);
}

void Datapool::loadSettingsState()
{
    uint8_t state = 0b00000000;
    QString tempData = GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME);
    if(!tempData.isEmpty())
        state |= STATE_VALID_STATION_NAME;

    tempData = GETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME);
    if(!tempData.isEmpty())
        state |= STATE_VALID_COMPANY_NAME;

    tempData = GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE);
    if(!tempData.isEmpty())
        state |= STATE_VALID_STATION_TYPE;

    tempData = GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONLINK);
    if(!tempData.isEmpty())
        state |= STATE_VALID_STATION_LINK;

    tempData = GETDPDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL);
    if(!tempData.isEmpty())
        if(tempData.toInt() >= 1000)
            state |= STATE_VALID_INTERVAL;

    tempData = GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP);
    if(!tempData.isEmpty())
        state |= STATE_VALID_FTP_SERVER;

    tempData = GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_USER);
    if(!tempData.isEmpty())
        state |= STATE_VALID_FTP_USER;

    tempData = GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW);
    if(!tempData.isEmpty())
        state |= STATE_VALID_FTP_PASSWD;

    SETDPDATA(Kd201eEnum::DP_COMMON_SETTINGS_STATE, QString::number(state));
}
