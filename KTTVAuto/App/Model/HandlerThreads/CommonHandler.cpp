#include "CommonHandler.h"
#include <QElapsedTimer>

CommonHandler::CommonHandler(QObject *parent) : QObject(parent)
{}

void CommonHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case HMIEvents::HMI_BUTTON_GENERATE_WORK_MAIN_TEXT: {
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

        MODEL->workMainTextSet(message);
        break;
    }
    default:
        break;
    }
}
