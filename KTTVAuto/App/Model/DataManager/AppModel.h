/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: AppModel.h
    Create: 13/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include <QMap>
#include <QHash>
#include <QMutex>

#include "DBManager.h"
#include "ScreenList.h"

#define INSERTSCREEN(param) m_screenMap.insert((int)param, #param)
#define INSERTEVENT(param) m_eventMap.insert((int)param, ((QString)#param).mid(11))

#define DECLARE(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME##Set NOTIFY NAME##Changed)   \
    private: \
        TYPE m_##NAME;   \
    Q_SIGNALS:    \
        void NAME##Changed(); \
    public: \
        void NAME##Set(const TYPE &VAL) {   \
            if(VAL != m_##NAME) {    \
                mutex.lock();   \
                m_##NAME = VAL;  \
                mutex.unlock(); \
                emit NAME##Changed();    \
            }\
        }   \
        TYPE NAME() const { \
            return m_##NAME; \
        }

class AppModel : public QObject
{
    Q_OBJECT

public:
    explicit AppModel(QObject *parent = nullptr);
    static AppModel* getInstance();

    /* data for list view DB -> MODEL -> FEEDER */
    void setLoginHistoryList(const QList<LoginHistory> &loginHistoryList);
    QList<LoginHistory> getLoginHistoryList() const;
    void resetLoginHistory();

    void setAccountList(const QList<AccountInformation> &list);
    QList<AccountInformation> getAccountList() const;
    void resetAccountList();

    void setDataviewList(const QList<DataviewRow> &list);
    QList<DataviewRow> getDataviewList() const;
    void resetDataviewList();

    QString getServer1IP();
    QString getServer1Port();
    QString generateWorkMainText();
    QString generateWorkMainEcodeText();
    QString generateWorkSimpleText();

    Q_INVOKABLE bool hasPermissionRoot();
    Q_INVOKABLE bool hasPermissionOperate();
    Q_INVOKABLE bool hasPermissionSettingStation();
    Q_INVOKABLE bool hasPermissionSettingAccount();
    Q_INVOKABLE bool isWorkingScreen();

    QString screenName(int screenId);
    QString eventName(int eventId);

private:
    void initNameMap();
    void initScreenNameMap();
    void initEventNameMap();

private:
    static AppModel *m_appModel;
    QMutex mutex;

    QHash<int, QString> m_eventMap;
    QHash<int, QString> m_screenMap;

    //--------------DB variables-------------//
    QList<LoginHistory> m_loginHistoryList;
    DECLARE(QString, dbFormatCurrentTime)
    DECLARE(QString, dbUserLoginTime)

    QList<AccountInformation> m_accountList;
    QList<DataviewRow> m_dataviewList;

    //------------device & common------------//
    DECLARE(int, currentScreenId)
    DECLARE(QString, systemTime)
    DECLARE(QString, systemDate)
    DECLARE(bool, isSystemTimeAutoUpdate)
    DECLARE(int, systemHour)
    DECLARE(int, systemMinute)
    DECLARE(int, systemSecond)
    DECLARE(QString, systemDayName)
    DECLARE(int, systemDay)
    DECLARE(int, systemMonth)
    DECLARE(int, systemYear)

    /* Setting device */
    DECLARE(QString, deviceName)
    DECLARE(QString, deviceCode)
    DECLARE(QString, deviceLocation)
    DECLARE(int, deviceType)

    /* Setting User */
    DECLARE(bool, isLogin)
    DECLARE(QString, userCode)
    DECLARE(QString, userFullName)
    DECLARE(QString, userAccount)
    DECLARE(QString, userPassword)
    DECLARE(uint8_t, userPermission)
    DECLARE(QString, userDescription)

    /* Setting sensor */
    DECLARE(QString, sensorPortName)                //
    DECLARE(QString, sensorBaudrate)                    //

    /* Setting telemetry */
    DECLARE(int, telemetryGeneralSendType)          // kiểu truyền
    DECLARE(int, telemetryGeneralControlType)       // điều khiển
    DECLARE(QString, telemetryGeneralSMSNotify)     // sms notify number
    DECLARE(int, telemetryGeneralSendInterval)      // khoảng truyền

    DECLARE(int, telemetryInternetNetworkType)      // nhà mạng
    DECLARE(int, telemetryInternetProtocolType)     // kiểu truyền
    DECLARE(QString, telemetryInternetServer1)      // server1 ip:port
    DECLARE(QString, telemetryInternetServer2)      // server2 ip:port

    DECLARE(int, historyHomePage)
    DECLARE(QString, gpsPortName)
    DECLARE(QString, gpsBaudrate)
    DECLARE(QString, simPortName)
    DECLARE(QString, simBaudrate)

    DECLARE(QString, historySearchDateStart)
    DECLARE(QString, historySearchDateEnd)

    DECLARE(QString, dataviewSearchDateStart)
    DECLARE(QString, dataviewSearchDateEnd)

    //----------------position----------------//
    DECLARE(bool, isConnectedGPS)
    DECLARE(QString, gpsTime)
    DECLARE(QString, gpsDate)
    DECLARE(QString, gpsLatitude)
    DECLARE(QString, gpsLongtitude)
    DECLARE(QString, gpsServerIP1)
    DECLARE(QString, gpsServerPort1)
    DECLARE(QString, gpsServerIP2)
    DECLARE(QString, gpsServerPort2)

    //----------------position----------------//
    DECLARE(bool, isConnectedSIM)
    DECLARE(bool, isConnectedSensor)

    //----------------work variables----------------//
    DECLARE(QString, work_station_matram)
    DECLARE(QString, work_station_quantracvien)
    DECLARE(QString, work_station_ngay)
    DECLARE(QString, work_station_obs)
    DECLARE(QString, work_weather_kyhieu)
    DECLARE(QString, work_weather_batdau)
    DECLARE(QString, work_weather_ketthuc)
    DECLARE(QString, work_weather_ecode_hientuong1)
    DECLARE(QString, work_weather_ecode_hientuong2)
    DECLARE(QString, work_weather_ecode_hientuong3)
    DECLARE(QString, work_view_tieudiem)
    DECLARE(QString, work_view_khoangcach)
    DECLARE(QString, work_view_maso)
    DECLARE(QString, work_view_ecode_tamnhin)
    DECLARE(QString, work_cloud_tongquan)
    DECLARE(QString, work_cloud_mayduoi)
    DECLARE(QString, work_cloud_docao)
    DECLARE(QString, work_cloud_ecode_nhom1)
    DECLARE(QString, work_cloud_ecode_nhom3lop1)
    DECLARE(QString, work_cloud_ecode_nhom3lop3)
    DECLARE(QString, work_cloud_ecode_nhom3lop5)
    DECLARE(QString, work_cloud_ecode_nhom3lop7)
    DECLARE(QString, work_thb_nhietdo)
    DECLARE(QString, work_thb_doam)
    DECLARE(QString, work_thb_khiap)
    DECLARE(QString, work_thb_ecode_nhietdo)
    DECLARE(QString, work_thb_ecode_doam)
    DECLARE(QString, work_thb_ecode_khiap)
    DECLARE(QString, work_thermometer_nhietdokho)
    DECLARE(QString, work_thermometer_tgnmatruou)
    DECLARE(QString, work_thermometer_tgxmathg)
    DECLARE(QString, work_thermometer_ecode_nhietdokho)
    DECLARE(QString, work_thermometer_ecode_tgnmatruou)
    DECLARE(QString, work_thermometer_ecode_tgxmathg)
    DECLARE(QString, work_gauge_nhietkephu)
    DECLARE(QString, work_gauge_apkesodoc)
    DECLARE(QString, work_gauge_apkehieuchinh)
    DECLARE(QString, work_gauge_apkemattram)
    DECLARE(QString, work_gauge_bienthien3h)
    DECLARE(QString, work_gauge_mbhieuchinh)
    DECLARE(QString, work_gauge_mbdahieuchinh)
    DECLARE(QString, work_gauge_apky)
    DECLARE(QString, work_gauge_p24h)
    DECLARE(QString, work_gauge_ecode_nhietkephu)
    DECLARE(QString, work_gauge_ecode_apkesodoc)
    DECLARE(QString, work_gauge_ecode_apkehc)
    DECLARE(QString, work_gauge_ecode_apkemattram)
    DECLARE(QString, work_gauge_ecode_bienthien3h)
    DECLARE(QString, work_gauge_ecode_mbhieuchinh)
    DECLARE(QString, work_gauge_ecode_mbdahieuchinh)
    DECLARE(QString, work_gauge_ecode_apky)
    DECLARE(QString, work_gauge_ecode_p24h)
    DECLARE(QString, work_wind_ff)
    DECLARE(QString, work_wind_dd)
    DECLARE(QString, work_wind_dacdiem)
    DECLARE(QString, work_wind_ecode_ff)
    DECLARE(QString, work_wind_ecode_dd)
    DECLARE(QString, work_wind_ecode_dacdiem)

    DECLARE(QString, work_rain_1h)
    DECLARE(QString, work_rain_24h)
    DECLARE(QString, work_rain_ecode_1h)
    DECLARE(QString, work_rain_ecode_24h)

    DECLARE(QString, workMainText)
    DECLARE(QString, workSimpleText)

    /* account table selection */
    DECLARE(QString, selectedAccountUserCode)
    DECLARE(QString, selectedAccountUserFullName)
    DECLARE(QString, selectedAccountUserAccount)
    DECLARE(QString, selectedAccountUserPassword)
    DECLARE(int, selectedAccountUserPermission)
    DECLARE(QString, selectedAccountUserDescription)

    DECLARE(int, dataSendAutomaticRequestInterval)
    DECLARE(QString, dataSlope)


    /* work thuy van */
    DECLARE(QString, work_thuyvan_rain_1h)
    DECLARE(QString, work_thuyvan_rain_24h)
    DECLARE(QString, work_thuyvan_mucnuoc)
    DECLARE(QString, work_thuyvan_rain_ecode_1h)
    DECLARE(QString, work_thuyvan_rain_ecode_24h)
    DECLARE(QString, work_thuyvan_ecode_mucnuoc)
    DECLARE(QString, work_thuyvan_send_text)

    /* work hai van */
    DECLARE(QString, work_haivan_wind_ff)
    DECLARE(QString, work_haivan_wind_dd)
    DECLARE(QString, work_haivan_mucnuoc)
    DECLARE(QString, work_haivan_nhietmuoi)
    DECLARE(QString, work_haivan_song)
    DECLARE(QString, work_haivan_wind_ecode_ff)
    DECLARE(QString, work_haivan_wind_ecode_dd)
    DECLARE(QString, work_haivan_ecode_mucnuoc)
    DECLARE(QString, work_haivan_ecode_nhietmuoi)
    DECLARE(QString, work_haivan_ecode_song)
    DECLARE(QString, work_haivan_send_text)
};

#endif // APPMODEL_H
