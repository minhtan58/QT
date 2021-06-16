/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: AppModel.cpp
    Create: 13/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#include "AppModel.h"

AppModel* AppModel::m_appModel = nullptr;

AppModel::AppModel(QObject *parent)
    : QObject(parent)
    , m_historyHomePage(0)
    , m_isLogin(false)
    , m_userPermission(0b00000000)
    , m_deviceType(0)
    , m_sensorPortName("")
    , m_sensorBaudrate("9600")
    , m_telemetryGeneralSendType(TELEMETRY_TYPE_INTERNET)
    , m_telemetryGeneralControlType(TELEMETRY_CONTROL_TYPE_USER)
    , m_telemetryGeneralSMSNotify("")
    , m_telemetryGeneralSendInterval(0)
    , m_telemetryInternetServer1(QString("%1:%2").arg(DEFAULT_SIM_SERVER_IP).arg(DEFAULT_SIM_SERVER_PORT))
    , m_gpsLatitude("21.0168172")
    , m_gpsLongtitude("105.7977905")
    , m_gpsTime("12:24")
    , m_gpsDate("25/07/2018")
    , m_dataSendAutomaticRequestInterval(1000)
    , m_simPortName("")
    , m_dataSlope(QString::number(0.1))
    , m_isConnectedSIM(false)
    , m_isConnectedSensor(false)

    , m_work_station_matram("")
    , m_work_station_quantracvien("")
    , m_work_station_ngay("")
    , m_work_station_obs("")
    , m_work_weather_kyhieu("")
    , m_work_weather_batdau("")
    , m_work_weather_ketthuc("")
    , m_work_weather_ecode_hientuong1("")
    , m_work_weather_ecode_hientuong2("")
    , m_work_weather_ecode_hientuong3("")
    , m_work_view_tieudiem("")
    , m_work_view_khoangcach("")
    , m_work_view_maso("")
    , m_work_view_ecode_tamnhin("")
    , m_work_cloud_tongquan("")
    , m_work_cloud_mayduoi("")
    , m_work_cloud_docao("")
    , m_work_cloud_ecode_nhom1("")
    , m_work_cloud_ecode_nhom3lop1("")
    , m_work_cloud_ecode_nhom3lop3("")
    , m_work_cloud_ecode_nhom3lop5("")
    , m_work_cloud_ecode_nhom3lop7("")
    , m_work_thb_nhietdo("")
    , m_work_thb_doam("")
    , m_work_thb_khiap("")
    , m_work_thb_ecode_nhietdo("")
    , m_work_thb_ecode_doam("")
    , m_work_thb_ecode_khiap("")
    , m_work_thermometer_nhietdokho("")
    , m_work_thermometer_tgnmatruou("")
    , m_work_thermometer_tgxmathg("")
    , m_work_thermometer_ecode_nhietdokho("")
    , m_work_thermometer_ecode_tgnmatruou("")
    , m_work_thermometer_ecode_tgxmathg("")
    , m_work_gauge_nhietkephu("")
    , m_work_gauge_apkesodoc("")
    , m_work_gauge_apkehieuchinh("")
    , m_work_gauge_apkemattram("")
    , m_work_gauge_bienthien3h("")
    , m_work_gauge_mbhieuchinh("")
    , m_work_gauge_mbdahieuchinh("")
    , m_work_gauge_apky("")
    , m_work_gauge_p24h("")
    , m_work_gauge_ecode_nhietkephu("")
    , m_work_gauge_ecode_apkesodoc("")
    , m_work_gauge_ecode_apkehc("")
    , m_work_gauge_ecode_apkemattram("")
    , m_work_gauge_ecode_bienthien3h("")
    , m_work_gauge_ecode_mbhieuchinh("")
    , m_work_gauge_ecode_mbdahieuchinh("")
    , m_work_gauge_ecode_apky("")
    , m_work_gauge_ecode_p24h("")
    , m_work_wind_ff("")
    , m_work_wind_dd("N")
    , m_work_wind_dacdiem("")
    , m_work_wind_ecode_ff("")
    , m_work_wind_ecode_dd("")
    , m_work_wind_ecode_dacdiem("")

    , m_work_rain_1h("0")
    , m_work_rain_24h("0")
    , m_work_rain_ecode_1h("")
    , m_work_rain_ecode_24h("")

    , m_workMainText("")
    , m_workSimpleText("")
{
    initNameMap();
}

AppModel *AppModel::getInstance()
{
    if(m_appModel == nullptr)
        m_appModel = new AppModel();
    return m_appModel;
}

void AppModel::setLoginHistoryList(const QList<LoginHistory> &loginHistoryList)
{
    m_loginHistoryList = loginHistoryList;
}

QList<LoginHistory> AppModel::getLoginHistoryList() const
{
    return m_loginHistoryList;
}

void AppModel::resetLoginHistory()
{
    if(!m_loginHistoryList.empty())
        m_loginHistoryList.clear();
}

void AppModel::setAccountList(const QList<AccountInformation> &list)
{
    m_accountList = list;
}

QList<AccountInformation> AppModel::getAccountList() const
{
    return m_accountList;
}

void AppModel::resetAccountList()
{
    m_accountList.clear();
}

void AppModel::setDataviewList(const QList<DataviewRow> &list)
{
    m_dataviewList = list;
}

QList<DataviewRow> AppModel::getDataviewList() const
{
    return m_dataviewList;
}

void AppModel::resetDataviewList()
{
    m_dataviewList.clear();
}

QString AppModel::getServer1IP()
{
    QString server1 = MODEL->telemetryInternetServer1();
    int idx = server1.indexOf(":");
    if(idx < 0)
        return "";
    return server1.mid(0, idx);
}

QString AppModel::getServer1Port()
{
    QString server1 = MODEL->telemetryInternetServer1();
    int idx = server1.indexOf(":");
    if(idx < 0 && idx < server1.length())
        return "";
    return server1.mid(idx + 1, server1.length() - 1);
}

QString AppModel::generateWorkMainText()
{
    QString grpGeneral = QString("[kieu,dulieutho]"
                                 "[matram,%1]"
                                 "[quantracvien,%2]"
                                 "[thoigian,%3]")
            .arg(MODEL->deviceCode())
            .arg(MODEL->userCode())
            .arg(MODEL->dbFormatCurrentTime());

    QString grpWeather = QString("[thoitiet_kyhieu,%1]"
                                 "[thoitiet_batdau,%2]"
                                 "[thoitiet_ketthuc,%3]")
            .arg(MODEL->work_weather_kyhieu())
            .arg(MODEL->work_weather_batdau())
            .arg(MODEL->work_weather_ketthuc());

    QString grpView = QString("[tamnhin_tieudiem,%1]"
                              "[tamnhin_khoangcach,%2]"
                              "[tamnhin_maso,%3]")
            .arg(MODEL->work_view_tieudiem())
            .arg(MODEL->work_view_khoangcach())
            .arg(MODEL->work_view_maso());

    QString grpCloud = QString("[may_tongquan,%1]"
                               "[may_mayduoi,%2]"
                               "[may_docao,%3]")
            .arg(MODEL->work_cloud_tongquan())
            .arg(MODEL->work_cloud_mayduoi())
            .arg(MODEL->work_cloud_docao());

    QString grpBase = QString("[nhietdo,%1]"
                              "[doam,%2]"
                              "[khiap,%3]")
            .arg(MODEL->work_thb_nhietdo())
            .arg(MODEL->work_thb_doam())
            .arg(MODEL->work_thb_khiap());

    QString grpThermometer = QString("[nhietke_nhietdokho,%1]"
                                     "[nhietke_tgnmatruou,%2]"
                                     "[nhietke_tgxmathg,%3]")
            .arg(MODEL->work_thermometer_nhietdokho())
            .arg(MODEL->work_thermometer_tgnmatruou())
            .arg(MODEL->work_thermometer_tgxmathg());

    QString grpGauge = QString("[khiapke_nhietkephu,%1]"
                               "[khiapke_apkesodoc,%2]"
                               "[khiapke_apkehieuchinh,%3]"
                               "[khiapke_apkemattram,%4]"
                               "[khiapke_bienthien3h,%5]"
                               "[khiapke_mbhieuchinh,%6]"
                               "[khiapke_mbdahieuchinh,%7]"
                               "[khiapke_apky,%8]"
                               "[khiapke_p24h,%9]")
            .arg(MODEL->work_gauge_nhietkephu())
            .arg(MODEL->work_gauge_apkesodoc())
            .arg(MODEL->work_gauge_apkehieuchinh())
            .arg(MODEL->work_gauge_apkemattram())
            .arg(MODEL->work_gauge_bienthien3h())
            .arg(MODEL->work_gauge_mbhieuchinh())
            .arg(MODEL->work_gauge_mbdahieuchinh())
            .arg(MODEL->work_gauge_apky())
            .arg(MODEL->work_gauge_p24h());

    QString grpWind = QString("[gio_ff,%1]"
                              "[gio_dd,%2]"
                              "[gio_dacdiem,%3]")
            .arg(MODEL->work_wind_ff())
            .arg(MODEL->work_wind_dd())
            .arg(MODEL->work_wind_dacdiem());

    QString grpRain = QString("[mua_1h,%1]"
                              "[mua_24h,%2]")
            .arg(MODEL->work_rain_1h())
            .arg(MODEL->work_rain_24h());

    QString message = QString("$%1%2%3%4%5%6%7%8%9\r\n")
            .arg(grpGeneral)
            .arg(grpWeather)
            .arg(grpView)
            .arg(grpCloud)
            .arg(grpBase)
            .arg(grpThermometer)
            .arg(grpGauge)
            .arg(grpWind)
            .arg(grpRain);
    return message;
}

QString AppModel::generateWorkMainEcodeText()
{
    QString message = QString("$[loai,madien]"
                              "[matram,%1]"
                              "[quantracvien,%2]"
                              "[thoigian,%3]"
                              "[thoitiet_hientuong1,%4]"
                              "[thoitiet_hientuong2,%5]"
                              "[thoitiet_hientuong3,%6]"
                              "[tamnhin_tamnhin,%7]"
                              "[may_nhom1,%8]"
                              "[may_nhom3lop1,%9]"
                              "[may_nhom3lop3,%10]"
                              "[may_nhom3lop5,%11]"
                              "[may_nhom3lop7,%12]"
                              "[nhietdo,%13]"
                              "[doam,%14]"
                              "[khiap,%15]"
                              "[nhietke_nhietdokho,%16]"
                              "[nhietke_tgnmatruou,%17]"
                              "[nhietke_tgxmathg,%18]"
                              "[khiapke_nhietkephu,%19]"
                              "[khiapke_apkesodoc,%20]"
                              "[khiapke_apkehc,%21]"
                              "[khiapke_apkemattram,%22]"
                              "[khiapke_bienthien3h,%23]"
                              "[khiapke_mbhieuchinh,%24]"
                              "[khiapke_mbdahieuchinh,%25]"
                              "[khiapke_apky,%26]"
                              "[khiapke_p24h,%27]"
                              "[gio_ff,%28]"
                              "[gio_dd,%29]"
                              "[gio_dacdiem,%30]\r\n")
            .arg(MODEL->deviceCode())
            .arg(MODEL->userCode())
            .arg(MODEL->dbFormatCurrentTime())

            .arg(MODEL->work_weather_ecode_hientuong1())
            .arg(MODEL->work_weather_ecode_hientuong2())
            .arg(MODEL->work_weather_ecode_hientuong3())

            .arg(MODEL->work_view_ecode_tamnhin())

            .arg(MODEL->work_cloud_ecode_nhom1())
            .arg(MODEL->work_cloud_ecode_nhom3lop1())
            .arg(MODEL->work_cloud_ecode_nhom3lop3())
            .arg(MODEL->work_cloud_ecode_nhom3lop5())
            .arg(MODEL->work_cloud_ecode_nhom3lop7())

            .arg(MODEL->work_thb_ecode_nhietdo())
            .arg(MODEL->work_thb_ecode_doam())
            .arg(MODEL->work_thb_ecode_khiap())

            .arg(MODEL->work_thermometer_ecode_nhietdokho())
            .arg(MODEL->work_thermometer_ecode_tgnmatruou())
            .arg(MODEL->work_thermometer_ecode_tgxmathg())

            .arg(MODEL->work_gauge_ecode_nhietkephu())
            .arg(MODEL->work_gauge_ecode_apkesodoc())
            .arg(MODEL->work_gauge_ecode_apkehc())
            .arg(MODEL->work_gauge_ecode_apkemattram())
            .arg(MODEL->work_gauge_ecode_bienthien3h())
            .arg(MODEL->work_gauge_ecode_mbhieuchinh())
            .arg(MODEL->work_gauge_ecode_mbdahieuchinh())
            .arg(MODEL->work_gauge_ecode_apky())
            .arg(MODEL->work_gauge_ecode_p24h())

            .arg(MODEL->work_wind_ecode_ff())
            .arg(MODEL->work_wind_ecode_dd())
            .arg(MODEL->work_wind_ecode_dacdiem());
    return message;
}

QString AppModel::generateWorkSimpleText()
{
    return QString("$[kieu,dulieu][matram,%1][quantracvien,%2][thoigian,%3][noidung,%4]\r\n")
            .arg(MODEL->deviceCode())
            .arg(MODEL->userCode())
            .arg(MODEL->dbFormatCurrentTime())
            .arg(MODEL->workSimpleText());
}

bool AppModel::hasPermissionRoot()
{
    return m_userPermission & PERMISSION_ROOT;
}

bool AppModel::hasPermissionSettingAccount()
{
    return m_userPermission & PERMISSION_SETTING_ACCOUNT;
}

bool AppModel::hasPermissionSettingStation()
{
    return m_userPermission & PERMISSION_SETTING_STATION;
}

bool AppModel::hasPermissionOperate()
{
    return m_userPermission & PERMISSION_OPERATOR;
}

bool AppModel::isWorkingScreen()
{
    return (m_currentScreenId == SCR_WORK_MAIN) || (m_currentScreenId == SCR_WORK_SIMPLE);
}

QString AppModel::screenName(int screenId)
{
    if(m_screenMap.contains(screenId))
        return m_screenMap[screenId];
    return QString::number(screenId);
}

QString AppModel::eventName(int eventId)
{
    if(m_eventMap.contains(eventId))
        return m_eventMap[eventId];
    return QString::number(eventId);
}

void AppModel::initNameMap()
{
    initScreenNameMap();
    initEventNameMap();
}

void AppModel::initScreenNameMap()
{
    INSERTSCREEN(SCR_HOME);
    INSERTSCREEN(SCR_SETTINGS);
    INSERTSCREEN(SCR_SETTINGS_OVERVIEW);
    INSERTSCREEN(SCR_SETTINGS_DEVELOPMENT);
    INSERTSCREEN(SCR_SETTINGS_DEVICES);
    INSERTSCREEN(SCR_SETTINGS_USER);
    INSERTSCREEN(SCR_SETTINGS_SENSOR);
    INSERTSCREEN(SCR_SETTINGS_TELEMETRY);
    INSERTSCREEN(SCR_SETTINGS_POSITION);
    INSERTSCREEN(SCR_SETTINGS_ELECTRICAL_CODES);
    INSERTSCREEN(SCR_SETTINGS_DATA);
    INSERTSCREEN(SCR_SETTINGS_ALERT);
    INSERTSCREEN(SCR_WORK_MAIN);
    INSERTSCREEN(SCR_WORK_SIMPLE);
    INSERTSCREEN(SCR_END);
    INSERTSCREEN(PRT_TOPBAR);
    INSERTSCREEN(PRT_STATUSBAR);
    INSERTSCREEN(PRT_KEYBOARD);
    INSERTSCREEN(PRT_KEYBOARD_NUMBER_ONLY);
    INSERTSCREEN(QN_COMMON);
    INSERTSCREEN(POPUP_LOGIN);
    INSERTSCREEN(POPUP_REQUEST_LOGIN);
    INSERTSCREEN(POPUP_LOGOUT);
    INSERTSCREEN(SPLASH_SCREEN);
    INSERTSCREEN(POPUP_REQUEST_DELETE_ACCOUNT);
    INSERTSCREEN(POPUP_CHANGE_PASSWORD);
    INSERTSCREEN(POPUP_CREATE_ACCOUNT);
}

void AppModel::initEventNameMap()
{
    INSERTEVENT(HMIEvents::HMI_BUTTON_HOME);
    INSERTEVENT(HMIEvents::HMI_BUTTON_BACK);
    INSERTEVENT(HMIEvents::HMI_HOME_SETTING);
    INSERTEVENT(HMIEvents::HMI_HOME_WORK_MAIN);
    INSERTEVENT(HMIEvents::HMI_BUTTON_SAVE_SETTINGS_GENERAL);
    INSERTEVENT(HMIEvents::HMI_BUTTON_RELOAD_CONFIGURATION_FILE);
    INSERTEVENT(HMIEvents::HMI_BUTTON_DEVELOPER_SAVE_SCREENSHOT);
    INSERTEVENT(HMIEvents::HMI_BUTTON_WORK_MAIN_SEND);
    INSERTEVENT(HMIEvents::HMI_BUTTON_REQUEST_LOGIN);
    INSERTEVENT(HMIEvents::HMI_BUTTON_REQUEST_LOGOUT);
    INSERTEVENT(HMIEvents::HMI_BUTTON_REQUEST_LOGIN_TO_CONTINUE);
    INSERTEVENT(HMIEvents::HMI_BUTTON_WORK_SIMPLE_SEND);
    INSERTEVENT(HMIEvents::HMI_BUTTON_WORK_SWITCH_MODE);
    INSERTEVENT(HMIEvents::HMI_BUTTON_GENERATE_WORK_MAIN_TEXT);
    INSERTEVENT(HMIEvents::HMI_KEYBOARD_DELETE);
    INSERTEVENT(HMIEvents::HMI_KEYBOARD_SAVE);
    INSERTEVENT(HMIEvents::HMI_TAB_SELECT);
    INSERTEVENT(HMIEvents::HMI_TEXTINPUT_FOCUS_CHANGED);
    INSERTEVENT(HMIEvents::HMI_TEXTINPUT_DONE_DEVICE_CODE);
    INSERTEVENT(HMIEvents::HMI_TEXTINPUT_DONE_DEVICE_NAME);
    INSERTEVENT(HMIEvents::HMI_TEXTINPUT_DONE_DEVICE_LOCATION);
    INSERTEVENT(HMIEvents::HMI_TEXTINPUT_DONE_TELEMETRY_GENERAL_SMSNOTIFY);
    INSERTEVENT(HMIEvents::HMI_TEXTINPUT_DONE_TELEMETRY_INTERNET_SERVER1);
    INSERTEVENT(HMIEvents::HMI_TEXTINPUT_DONE_TELEMETRY_INTERNET_SERVER2);
    INSERTEVENT(HMIEvents::HMI_REQUEST_SHOW_COMMON_QN);
    INSERTEVENT(HMIEvents::HMI_REQUEST_HIDE_POPUP);
    INSERTEVENT(HMIEvents::HMI_REQUEST_HIDE_QN);
    INSERTEVENT(HMIEvents::HMI_SWITCH_UPDATE_TIME_AUTOMATIC);
    INSERTEVENT(HMIEvents::HMI_COMBOBOX_TELEMETRY_SENDTYPE_CHANGED);
    INSERTEVENT(HMIEvents::HMI_COMBOBOX_TELEMETRY_CONTROLTYPE_CHANGED);
    INSERTEVENT(HMIEvents::HMI_COMBOBOX_TELEMETRY_NETWORKTYPE_CHANGED);
    INSERTEVENT(HMIEvents::HMI_COMBOBOX_TELEMETRY_PROTOCOLTYPE_CHANGED);
    INSERTEVENT(HMIEvents::HMI_SPINBOX_TELEMETRY_GENERAL_SENDINTERVAL);
    INSERTEVENT(HMIEvents::HMI_REQUEST_GET_CURRENT_USER_LOGIN_INFORMATION);
    INSERTEVENT(HMIEvents::HMI_REQUEST_GET_LOGIN_HISTORY);
    INSERTEVENT(HMIEvents::HMI_REQUEST_DELETE_LOGIN_LIST);
    INSERTEVENT(HMIEvents::HMI_REQUEST_SHOW_LOGIN);
    INSERTEVENT(HMIEvents::HMI_REQUEST_ADD_DELAY_EVENT);
    INSERTEVENT(HMIEvents::HMI_REQUEST_GET_ACCOUNT_LIST);
    INSERTEVENT(HMIEvents::HMI_REQUEST_DELETE_ACCOUNT_LIST);
    INSERTEVENT(HMIEvents::HMI_RESPONSE_LOAD_SETTINGS_INI_FINISHED);
    INSERTEVENT(HMIEvents::DB_RESPONSE_GET_LOGIN_HISTORY_FINISHED);
    INSERTEVENT(HMIEvents::DB_RESPONSE_GET_ACCOUNT_LIST_FINISHED);
    INSERTEVENT(HMIEvents::DB_RESPONSE_LOGIN_FINISHED);
    INSERTEVENT(HMIEvents::HMI_REQUEST_DB_SAVE_CHANGE_ACCOUNT);
    INSERTEVENT(HMIEvents::HMI_REQUEST_SHOW_DELETE_ACCOUNT_CONFIRM_POPUP);
    INSERTEVENT(HMIEvents::HMI_REQUEST_DB_DELETE_ACCOUNT);
    INSERTEVENT(HMIEvents::HMI_REQUEST_DB_CHANGE_PASSWORD);
    INSERTEVENT(HMIEvents::HMI_REQUEST_SHOW_CHANGE_PASSWORD_POPUP);
    INSERTEVENT(HMIEvents::HMI_REQUEST_SHOW_CREATE_ACCOUNT_POPUP);
    INSERTEVENT(HMIEvents::HMI_REQUEST_DB_CREATE_NEW_ACCOUNT);
    INSERTEVENT(HMIEvents::DB_RESPONSE_GET_DATAVIEW_LIST_FINISHED);
    INSERTEVENT(HMIEvents::HMI_HOME_DATAVIEW);
    INSERTEVENT(HMIEvents::HMI_REQUEST_GET_DATAVIEW_LIST);
    INSERTEVENT(HMIEvents::HMI_COMBOBOX_DEVICETYPE_CHANGED);
    INSERTEVENT(HMIEvents::HMI_BUTTON_WORK_THUYVAN_SEND);
    INSERTEVENT(HMIEvents::HMI_BUTTON_WORK_HAIVAN_SEND);
}
