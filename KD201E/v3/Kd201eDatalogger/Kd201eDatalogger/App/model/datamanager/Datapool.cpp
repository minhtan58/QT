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
            emit dataChanged(dpid, value);
            DLOG("%s: %s", m_dpName[dpid].toStdString().data(), value.toStdString().data());
            return;
        }
    }
    else
        DLG_THR << "DPID: " << dpid << "Incorrect";
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
    INITDATA(KD201EEnum::DP_VARIABLES_CONTROLLER);
    INITDATA(KD201EEnum::DP_VARIABLES_SERIAL);
    INITDATA(KD201EEnum::DP_VARIABLES_SOFTWARE);
    INITDATA(KD201EEnum::DP_VARIABLES_TIME);
    INITDATA(KD201EEnum::DP_VARIABLES_PH);
    INITDATA(KD201EEnum::DP_VARIABLES_OC);
    INITDATA(KD201EEnum::DP_VARIABLES_TSS);
    INITDATA(KD201EEnum::DP_VARIABLES_FLOW);
    INITDATA(KD201EEnum::DP_VARIABLES_COD);

    INITDATA(KD201EEnum::DP_SETTINGS_PROVINCE_CODE);
    INITDATA(KD201EEnum::DP_SETTINGS_COMPANY_NAME);
    INITDATA(KD201EEnum::DP_SETTINGS_COMPANY_CODE);
    INITDATA(KD201EEnum::DP_SETTINGS_STATION_NAME);
    INITDATA(KD201EEnum::DP_SETTINGS_STATION_CODE);
    INITDATA(KD201EEnum::DP_SETTINGS_STATION_TYPE);
    INITDATA(KD201EEnum::DP_SETTINGS_HTML_SOURCE);
    INITDATA(KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL);
    INITDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_IP);
    INITDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PORT);
    INITDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_USER);
    INITDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PASSWD);
    INITDATA(KD201EEnum::DP_SETTINGS_TIME_USINGHTML);

    INITDATA(KD201EEnum::DP_COMMON_HTML_CONNETED);
    INITDATA(KD201EEnum::DP_COMMON_FTPSERVER_CONNETED);
    INITDATA(KD201EEnum::DP_COMMON_SETTINGS_STATE);
}

void Datapool::updateSettingsState()
{
    uint16_t state = 0b0000000000000000;
    QString tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_PROVINCE_CODE);
    if(!tempData.isEmpty())
        state |= STATE_VALID_PROVINCE_CODE;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_NAME);
    if(!tempData.isEmpty())
        state |= STATE_VALID_COMPANY_NAME;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_CODE);
    if(!tempData.isEmpty())
        state |= STATE_VALID_COMPANY_CODE;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_NAME);
    if(!tempData.isEmpty())
        state |= STATE_VALID_STATION_NAME;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_CODE);
    if(!tempData.isEmpty())
        state |= STATE_VALID_STATION_CODE;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_TYPE);
    if(!tempData.isEmpty())
        state |= STATE_VALID_STATION_TYPE;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_SOURCE);
    if(!tempData.isEmpty())
        state |= STATE_VALID_HTML_SOURCE;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL);
    if(!tempData.isEmpty())
        state |= STATE_VALID_HTML_READ_INTERVAL;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_IP);
    if(!tempData.isEmpty())
        state |= STATE_VALID_FTPSERVER_IP;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PORT);
    if(!tempData.isEmpty())
        state |= STATE_VALID_FTPSERVER_PORT;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_USER);
    if(!tempData.isEmpty())
        state |= STATE_VALID_FTPSERVER_USER;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PASSWD);
    if(!tempData.isEmpty())
        state |= STATE_VALID_FTPSERVER_PASSWD;

    tempData = GETDPDATA(KD201EEnum::DP_SETTINGS_TIME_USINGHTML);
    if(!tempData.isEmpty())
        state |= STATE_VALID_TIME_USINGHTML;

    SETDPDATA(KD201EEnum::DP_COMMON_SETTINGS_STATE, QString::number(state));
    DLOG("Settings state: %s", QString("%1").arg(state, 0, 2).toStdString().data());
}

void Datapool::setHistoryList(QList<DataRow> historyDatalist)
{
    mutex.lock();
    m_historyDatalist.clear();
    m_historyDatalist.append(historyDatalist);
    mutex.unlock();
}

QList<DataRow> Datapool::getHistoryList()
{
    return m_historyDatalist;
}

void Datapool::requestGetHistoryList(QString searchTime)
{
    DLOG("Request get history data with time %s", searchTime.toStdString().data());
    QList<DataRow> list;
    list = DbManager::getInstance()->getHistoryData(searchTime);
    DLOG("List size %d", list.size());
    setHistoryList(list);
}
