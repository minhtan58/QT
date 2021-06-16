#include "ScreenAdapter.h"

ScreenAdapter::ScreenAdapter(QQmlApplicationEngine *qmlAppEngine, QObject *parent)
    : QObject(parent)
    , m_qmlAppEngine(qmlAppEngine)
    , m_screenId(-1)
{
    m_qmlAppEngine->rootContext()->setContextProperty("listHistory", nullptr);
    m_appContainer = m_qmlAppEngine->rootObjects().at(0)->findChild<QQuickItem*>("appContainer");
    connect(UIBridge::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), this, SLOT(eventHandler(QString,int,QString)));
}

ScreenAdapter::~ScreenAdapter()
{}

void ScreenAdapter::createScreen()
{
    DLOG("load screen starting");
    m_appContainer->setProperty("source", screenList.value(m_screenId));
    m_screenView = qvariant_cast<QObject*>(m_appContainer->property("item"));
    initAppData();
    DLOG("load screen %d finished", m_screenId);
}

int ScreenAdapter::getCurrentScreen()
{
    return m_screenId;
}

void ScreenAdapter::initAppData()
{
    switch (m_screenId) {
    case SCR_DATAVIEW: {
        int idx, modeViewTmp;
        QStringList listDataviewName;
        listDataviewName << "viewO2"
                         << "viewCO"
                         << "viewNO"
                         << "viewNOX"
                         << "viewSO2"
                         << "viewTEMP"
                         << "viewOPP"
                         << "viewDUSTPM"
                         << "viewVEL"
                         << "viewFLOW";

        QStringList listModeView;
        listModeView << "modeViewCO"
                     << "modeViewNO"
                     << "modeViewNOX"
                     << "modeViewSO2";

        for (idx = 1; idx < 5; ++idx) {
            modeViewTmp = GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_CO + (idx - 1)).toUInt();
            SETPROPERTY("scr_dataview", listModeView.at(idx - 1).toStdString().c_str(), GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_CO + (idx - 1)));
            SETPROPERTY(listDataviewName.at(idx).toStdString().c_str(), "textValue", GETDPDATA(modeViewTmp == CEMS_SETTINGS_VIEW_STD ? (CEMSEnum::DP_AIR_CO + idx - 1) : (CEMSEnum::DP_PPM_AIR_CO + idx - 1)));
        }

        SETPROPERTY("viewO2", "textValue", GETDPDATA(CEMSEnum::DP_AIR_O2));
        for (idx = 5; idx < 10; ++idx) {
            SETPROPERTY(listDataviewName.at(idx).toStdString().c_str(), "textValue", GETDPDATA(CEMSEnum::DP_TEMP + (idx - 5)));
        }

        for (idx = 0; idx < 10; ++idx) {
            SETPROPERTY(listDataviewName.at(idx).toStdString().c_str(), "isAlarmOn", GETDPDATA(CEMSEnum::DP_STATUS_ALARM_O2 + idx));
        }
        break;
    }
    case SCR_SETTINGS_OVERVIEW: {
        QString sPortName = GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME);
        QString sBaudrate = GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE);
        if(sPortName.isEmpty() || sBaudrate.isEmpty()) {
            SETPROPERTY("settings_overview_serialport_information", "text", "--------------------");
        }
        else {
            QString serialInfo = QString("%1,%2,8,N,1").arg(sPortName).arg(sBaudrate);
            SETPROPERTY("settings_overview_serialport_information", "text", serialInfo);
        }
        SETPROPERTY("settings_overview_serialport_status", "isConnected", GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS).toUInt() == 1);

        QString nIP = GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP);
        QString nPort = GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT);
        if(nIP.isEmpty() || nPort.isEmpty()) {
            SETPROPERTY("settings_overview_server_address", "text", "--------------------");
        }
        else {
            QString serverInfo = QString("%1:%2").arg(nIP).arg(nPort);
            SETPROPERTY("settings_overview_server_address", "text", serverInfo);
        }
        SETPROPERTY("settings_overview_server_status", "isConnected", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_STATUS).toUInt() == 1);

        QString fIP = GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_IP);
        QString fPort = GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PORT);
        if(fIP.isEmpty() || fPort.isEmpty()) {
            SETPROPERTY("settings_overview_ftp_address", "text", "--------------------");
        }
        else {
            QString ftpInfo = QString("%1:%2").arg(fIP).arg(fPort);
            SETPROPERTY("settings_overview_ftp_address", "text", ftpInfo);
        }
        SETPROPERTY("settings_overview_ftp_status", "isConnected", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_STATUS).toUInt() == 1);

        SETPROPERTY("settings_overview_server_interval", "text", createIntervalDisplay(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_INTERVAL).toInt()));
        SETPROPERTY("settings_overview_ftp_interval", "text", createIntervalDisplay(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_INTERVAL).toInt()));
        break;
    }
    case SCR_SETTINGS_GENERAL: {
        SETPROPERTY("settings_general_station_id", "text", GETDPDATA(CEMSEnum::DP_GENERAL_STATION_ID));
        SETPROPERTY("settings_general_station_name", "text", GETDPDATA(CEMSEnum::DP_GENERAL_STATION_NAME));
        SETPROPERTY("settings_general_r", "text", GETDPDATA(CEMSEnum::DP_GENERAL_RADIUS));
        SETPROPERTY("scr_settings_general", "isAutoUpdateTime", GETDPDATA(CEMSEnum::DP_SYS_SETTINGS_TIME_AUTOMATIC_UPDATE));

        QStringList listTime;
        listTime << "spinHour"
                 << "spinMinute"
                 << "spinDay"
                 << "spinMonth"
                 << "spinYear";

        for (int idx = CEMSEnum::DP_SYS_TIME_HOUR; idx <= CEMSEnum::DP_SYS_DATE_YEAR; ++idx) {
            SETPROPERTY(listTime.at(idx - CEMSEnum::DP_SYS_TIME_HOUR).toStdString().c_str(), "currentValue", GETDPDATA(idx));
        }
        break;
    }
    case SCR_SETTINGS_NETWORK: {
        SETPROPERTY("settings_network_server_ip", "text", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP));
        SETPROPERTY("settings_network_server_port", "text", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT));
        SETPROPERTY("settings_network_server_interval", "currentValue", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_INTERVAL).toInt() / 60000);
        SETPROPERTY("settings_network_ftp_ip", "text", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_IP));
        SETPROPERTY("settings_network_ftp_port", "text", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PORT));
        SETPROPERTY("settings_network_ftp_user", "text", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_USER));
        SETPROPERTY("settings_network_ftp_password", "text", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PASSWORD));
        SETPROPERTY("settings_network_ftp_interval", "currentValue", GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_INTERVAL).toInt() / 60000);
        break;
    }
    case SCR_SETTINGS_SERIALPORT: {
        SETPROPERTY("settings_serialport_portname", "currentValue", GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME));
        SETPROPERTY("settings_serialport_baudrate", "currentValue", GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE));
        SETPROPERTY("scr_settings_serial_port", "listSerialPort", GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_LIST_AVAIABLE_PORTNAME));
        if(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS) == "1") {
            SETPROPERTY("scr_settings_serial_port", "currentSerialPort", GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME));
        }
        else
            SETPROPERTY("scr_settings_serial_port", "currentSerialPort", "");
        break;
    }

    case SCR_SETTINGS_ALARM: {
        QStringList listViewAlarm;
        listViewAlarm << "air_status_O2"
                      << "air_min_O2"
                      << "air_max_O2"
                      << "air_status_CO"
                      << "air_min_CO"
                      << "air_max_CO"
                      << "air_status_NO"
                      << "air_min_NO"
                      << "air_max_NO"
                      << "air_status_NOX"
                      << "air_min_NOX"
                      << "air_max_NOX"
                      << "air_status_SO2"
                      << "air_min_SO2"
                      << "air_max_SO2"
                      << "air_status_TEMP"
                      << "air_min_TEMP"
                      << "air_max_TEMP"
                      << "air_status_OPP"
                      << "air_min_OPP"
                      << "air_max_OPP"
                      << "air_status_DUST_PM"
                      << "air_min_DUST_PM"
                      << "air_max_DUST_PM"
                      << "air_status_VEL"
                      << "air_min_VEL"
                      << "air_max_VEL"
                      << "air_status_FLOW"
                      << "air_min_FLOW"
                      << "air_max_FLOW";

        for (int idx = 0; idx < listViewAlarm.size(); ++idx) {
            SETPROPERTY("scr_settings_alarm", listViewAlarm.at(idx).toStdString().c_str(), GETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_STATUS + idx));
        }
        break;
    }
    case SCR_HISTORY_DATAVIEW: {
        SETPROPERTY("dateSelected", "datetime", GETDPDATA(CEMSEnum::DP_SEARCH_TIME_HISTORY_DATA));
        break;
    }
    default:
        break;
    }
}

void ScreenAdapter::setScreenId(int screenId)
{
    m_screenId = screenId;
}

void ScreenAdapter::updateAppData(int dpid)
{
    QString data = GETDPDATA(dpid);
    int modeViewTmp;
    switch (dpid) {
    //-------------------------DATAVIEW SCREEN-------------------------
    case CEMSEnum::DP_AIR_O2: {
        SETPROPERTY("viewO2", "textValue", data);
        break;
    }
    case CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_CO:
    case CEMSEnum::DP_AIR_CO:
    case CEMSEnum::DP_PPM_AIR_CO: {
        if(m_screenId == SCR_DATAVIEW) {
            modeViewTmp = GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_CO).toInt();
            SETPROPERTY("scr_dataview", "modeViewCO", GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_CO));
            SETPROPERTY("viewCO", "textValue", GETDPDATA(modeViewTmp == CEMS_SETTINGS_VIEW_STD ? CEMSEnum::DP_AIR_CO : CEMSEnum::DP_PPM_AIR_CO));
        }
        break;
    }
    case CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NO:
    case CEMSEnum::DP_AIR_NO:
    case CEMSEnum::DP_PPM_AIR_NO: {
        if(m_screenId == SCR_DATAVIEW) {
            modeViewTmp = GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NO).toInt();
            SETPROPERTY("scr_dataview", "modeViewNO", GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NO));
            SETPROPERTY("viewNO", "textValue", GETDPDATA(modeViewTmp == CEMS_SETTINGS_VIEW_STD ? CEMSEnum::DP_AIR_NO : CEMSEnum::DP_PPM_AIR_NO));
        }
        break;
    }
    case CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NOX:
    case CEMSEnum::DP_AIR_NOX:
    case CEMSEnum::DP_PPM_AIR_NOX: {
        if(m_screenId == SCR_DATAVIEW) {
            modeViewTmp = GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NOX).toInt();
            SETPROPERTY("scr_dataview", "modeViewNOX", GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NOX));
            SETPROPERTY("viewNOX", "textValue", GETDPDATA(modeViewTmp == CEMS_SETTINGS_VIEW_STD ? CEMSEnum::DP_AIR_NOX : CEMSEnum::DP_PPM_AIR_NOX));
        }
        break;
    }
    case CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_SO2:
    case CEMSEnum::DP_AIR_SO2:
    case CEMSEnum::DP_PPM_AIR_SO2: {
        if(m_screenId == SCR_DATAVIEW) {
            modeViewTmp = GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_SO2).toInt();
            SETPROPERTY("scr_dataview", "modeViewSO2", GETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_SO2));
            SETPROPERTY("viewSO2", "textValue", GETDPDATA(modeViewTmp == CEMS_SETTINGS_VIEW_STD ? CEMSEnum::DP_AIR_SO2 : CEMSEnum::DP_PPM_AIR_SO2));
        }
        break;
    }
    case CEMSEnum::DP_TEMP: {
        if(m_screenId == SCR_DATAVIEW) {
            SETPROPERTY("viewTEMP", "textValue", data);
        }
        break;
    }
    case CEMSEnum::DP_OPP: {
        if(m_screenId == SCR_DATAVIEW) {
            SETPROPERTY("viewOPP", "textValue", data);
        }
        break;
    }
    case CEMSEnum::DP_DUST_PM: {
        if(m_screenId == SCR_DATAVIEW) {
            SETPROPERTY("viewDUSTPM", "textValue", data);
        }
        break;
    }
    case CEMSEnum::DP_VEL:{
        if(m_screenId == SCR_DATAVIEW) {
            SETPROPERTY("viewVEL", "textValue", data);
        }
        break;
    }
    case CEMSEnum::DP_FLOW: {
        if(m_screenId == SCR_DATAVIEW) {
            SETPROPERTY("viewFLOW", "textValue", data);
        }
        break;
    }
    case CEMSEnum::DP_STATUS_ALARM_O2:
    case CEMSEnum::DP_STATUS_ALARM_CO:
    case CEMSEnum::DP_STATUS_ALARM_NO:
    case CEMSEnum::DP_STATUS_ALARM_NOX:
    case CEMSEnum::DP_STATUS_ALARM_SO2:
    case CEMSEnum::DP_STATUS_ALARM_TEMP:
    case CEMSEnum::DP_STATUS_ALARM_OPP:
    case CEMSEnum::DP_STATUS_ALARM_DUST_PM:
    case CEMSEnum::DP_STATUS_ALARM_VEL:
    case CEMSEnum::DP_STATUS_ALARM_FLOW: {
        QStringList listDataviewName;
        listDataviewName << "viewO2"
                         << "viewCO"
                         << "viewNO"
                         << "viewNOX"
                         << "viewSO2"
                         << "viewTEMP"
                         << "viewOPP"
                         << "viewDUSTPM"
                         << "viewVEL"
                         << "viewFLOW";
        SETPROPERTY(listDataviewName.at(dpid - CEMSEnum::DP_STATUS_ALARM_O2).toStdString().c_str(), "isAlarmOn", data);
        break;
    }
    //----------------------------------------------------------------

    //-------------------------GENERAL SCREEN-------------------------

    case CEMSEnum::DP_GENERAL_STATION_ID: {
        SETPROPERTY("settings_general_station_id", "text", data);
        break;
    }
    case CEMSEnum::DP_GENERAL_STATION_NAME: {
        SETPROPERTY("settings_general_station_name", "text", data);
        break;
    }
    case CEMSEnum::DP_GENERAL_RADIUS: {
        SETPROPERTY("settings_general_r", "text", data);
        break;
    }
    case CEMSEnum::DP_SYS_SETTINGS_TIME_AUTOMATIC_UPDATE: {
        SETPROPERTY("scr_settings_general", "isAutoUpdateTime", data);
        break;
    }
    //----------------------------------------------------------------

    //-------------------------NETWORK SCREEN-------------------------
    case CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP: {
        if(m_screenId == SCR_SETTINGS_NETWORK) {
            SETPROPERTY("settings_network_server_ip", "text", data);
        }
        else if (m_screenId == SCR_SETTINGS_OVERVIEW) {
            QString serverInfo = QString("%1:%2")
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP))
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT));
            SETPROPERTY("settings_overview_server_address", "text", serverInfo);
        }

        break;
    }
    case CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT: {
        if(m_screenId == SCR_SETTINGS_NETWORK) {
            SETPROPERTY("settings_network_server_port", "text", data);
        }
        else if (m_screenId == SCR_SETTINGS_OVERVIEW) {
            QString serverInfo = QString("%1:%2")
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_IP))
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_PORT));
            SETPROPERTY("settings_overview_server_address", "text", serverInfo);
        }
        break;
    }
    case CEMSEnum::DP_SETTINGS_NETWORK_SERVER_INTERVAL: {
        if(m_screenId == SCR_SETTINGS_NETWORK)
            SETPROPERTY("settings_network_server_interval", "currentValue", data.toInt() / 60000);
        break;
    }
    case CEMSEnum::DP_SETTINGS_NETWORK_FTP_IP: {
        if(m_screenId == SCR_SETTINGS_NETWORK) {
            SETPROPERTY("settings_network_ftp_ip", "text", data);
        }
        else if (m_screenId == SCR_SETTINGS_OVERVIEW) {
            QString ftpInfo = QString("%1:%2")
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_IP))
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PORT));
            SETPROPERTY("settings_overview_ftp_address", "text", ftpInfo);
        }

        break;
    }
    case CEMSEnum::DP_SETTINGS_NETWORK_FTP_PORT: {
        if(m_screenId == SCR_SETTINGS_NETWORK) {
            SETPROPERTY("settings_network_ftp_port", "text", data);
        }
        else if (m_screenId == SCR_SETTINGS_OVERVIEW) {
            QString ftpInfo = QString("%1:%2")
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_IP))
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_FTP_PORT));
            SETPROPERTY("settings_overview_ftp_address", "text", ftpInfo);
        }
        break;
    }
    case CEMSEnum::DP_SETTINGS_NETWORK_FTP_USER: {
        if(m_screenId == SCR_SETTINGS_NETWORK)
            SETPROPERTY("settings_network_ftp_user", "text", data);
        break;
    }
    case CEMSEnum::DP_SETTINGS_NETWORK_FTP_PASSWORD: {
        if(m_screenId == SCR_SETTINGS_NETWORK)
            SETPROPERTY("settings_network_ftp_password", "text", data);
        break;
    }
    case CEMSEnum::DP_SETTINGS_NETWORK_FTP_INTERVAL: {
        if(m_screenId == SCR_SETTINGS_NETWORK)
            SETPROPERTY("settings_network_ftp_interval", "currentValue", data.toInt() / 60000);
        break;
    }
    //----------------------------------------------------------------

    //-----------------------SERIALPORT SCREEN------------------------
    case CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME: {
        if(m_screenId == SCR_SETTINGS_SERIALPORT) {
            SETPROPERTY("settings_serialport_portname", "currentValue", data);
        }
        else if (m_screenId == SCR_SETTINGS_OVERVIEW) {
            QString serialInfo = QString("%1,%2,8,N,1")
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME))
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE));
            SETPROPERTY("settings_overview_serialport_information", "text", serialInfo);
        }
        break;
    }
    case CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE: {
        if(m_screenId == SCR_SETTINGS_SERIALPORT) {
            SETPROPERTY("settings_serialport_baudrate", "currentValue", data);
        }
        else if (m_screenId == SCR_SETTINGS_OVERVIEW) {
            QString serialInfo = QString("%1,%2,8,N,1")
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME))
                    .arg(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE));
            SETPROPERTY("settings_overview_serialport_information", "text", serialInfo);
        }
        break;
    }
    case CEMSEnum::DP_SETTINGS_SERIALPORT_LIST_AVAIABLE_PORTNAME: {
        SETPROPERTY("scr_settings_serial_port", "listSerialPort", GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_LIST_AVAIABLE_PORTNAME));
        break;
    }
    case CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS: {
        if(m_screenId == SCR_SETTINGS_OVERVIEW)
            SETPROPERTY("settings_overview_serialport_status", "isConnected", data.toUInt() == 1);
        break;
    }
    case CEMSEnum::DP_SETTINGS_NETWORK_SERVER_STATUS: {
        if(m_screenId == SCR_SETTINGS_OVERVIEW)
            SETPROPERTY("settings_overview_server_status", "isConnected", data.toUInt() == 1)
        break;
    }
    //----------------------------------------------------------------

    //---------------------------ALARM SCREEN-------------------------
    case CEMSEnum::DP_SETTINGS_ALARM_O2_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_O2_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_O2_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_CO_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_CO_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_CO_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_NO_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_NO_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_NO_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_NOX_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_NOX_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_NOX_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_SO2_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_SO2_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_SO2_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_TEMP_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_TEMP_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_TEMP_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_OPP_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_OPP_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_OPP_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_VEL_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_VEL_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_VEL_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_FLOW_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_FLOW_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_FLOW_MAX: {
        QStringList listAlarmName;
        listAlarmName << "air_status_O2"
                      << "air_min_O2"
                      << "air_max_O2"
                      << "air_status_CO"
                      << "air_min_CO"
                      << "air_max_CO"
                      << "air_status_NO"
                      << "air_min_NO"
                      << "air_max_NO"
                      << "air_status_NOX"
                      << "air_min_NOX"
                      << "air_max_NOX"
                      << "air_status_SO2"
                      << "air_min_SO2"
                      << "air_max_SO2"
                      << "air_status_TEMP"
                      << "air_min_TEMP"
                      << "air_max_TEMP"
                      << "air_status_OPP"
                      << "air_min_OPP"
                      << "air_max_OPP"
                      << "air_status_DUST_PM"
                      << "air_min_DUST_PM"
                      << "air_max_DUST_PM"
                      << "air_status_VEL"
                      << "air_min_VEL"
                      << "air_max_VEL"
                      << "air_status_FLOW"
                      << "air_min_FLOW"
                      << "air_max_FLOW";
        SETPROPERTY("scr_settings_alarm", listAlarmName.at(dpid - CEMSEnum::DP_SETTINGS_ALARM_O2_STATUS).toStdString().c_str(), data);
        break;
    }
    case CEMSEnum::DP_SEARCH_TIME_HISTORY_DATA: {
        SETPROPERTY("dateSelected", "datetime", GETDPDATA(CEMSEnum::DP_SEARCH_TIME_HISTORY_DATA));
        break;
    }
    case CEMSEnum::DP_SYS_DATE_DAY: {
        SETDPDATA(CEMSEnum::DP_SEARCH_TIME_HISTORY_DATA,
                  QString("%1-%2-%3")
                  .arg(GETDPDATA(CEMSEnum::DP_SYS_DATE_YEAR))
                  .arg(GETDPDATA(CEMSEnum::DP_SYS_DATE_MONTH))
                  .arg(GETDPDATA(CEMSEnum::DP_SYS_DATE_DAY)));
        break;
    }
    default:
        break;
    }
}

void ScreenAdapter::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case CEMSEnum::HMI_LIST_REQUEST_GET_HISTORY_DATA: {
        SETDPDATA(CEMSEnum::DP_SEARCH_TIME_HISTORY_DATA, param);
        if(m_listHistory) {
            m_listHistory->~HistoryDataListModel();
            m_qmlAppEngine->rootContext()->setContextProperty("listHistory", nullptr);
        }
        break;
    }
    case CEMSEnum::DB_RESPONSE_GET_HISTORY_DATA_FINISHED: {
        m_listHistory = new HistoryDataListModel(this);
        m_listHistory->fetchData();
        m_qmlAppEngine->rootContext()->setContextProperty("listHistory", m_listHistory);
        emit m_listHistory->updateFetchDataStatus(FETCH_FINISHED);
        break;
    }
    default:
        break;
    }
}

QString ScreenAdapter::createIntervalDisplay(int msec)
{
    int sec = msec/1000;
    int hour, minute, second;
    hour = sec/3600;
    minute = (sec - hour*3600)/60;
    second = sec%60;
    return QString("%1:%2:%3").arg(hour, 2, 10, QLatin1Char('0')).arg(minute, 2, 10, QLatin1Char('0')).arg(second, 2, 10, QLatin1Char('0'));
}

