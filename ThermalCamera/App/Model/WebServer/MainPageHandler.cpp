#include "MainPageHandler.h"
#include "common.h"
#include "DPID.h"
#include "Defines.h"
#include "DataManager.h"

MainPageHandler::MainPageHandler(QObject *parent)
    :HttpRequestHandler(parent)
{
    QFile page(MAIN_PAGE);
    if (!page.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream in(&page);
    in.setCodec("UTF-8");
    htmlPage = in.readAll().replace("\n", "");
}

void MainPageHandler::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    QString updateMsg;
    if(msgBody.contains("update")) {
//        /* dummy code start */
//        int dummyTemp = QDateTime::currentDateTime().toString("zzz").toInt();
//        SETDP(DPID::DP_THERMAL_TEMPERATURE, QString::number(dummyTemp));
//        if(dummyTemp > GETDP(DPID::DP_SETTINGS_THRESOLD_MAXTEMP).toInt()
//                || dummyTemp < GETDP(DPID::DP_SETTINGS_THRESOLD_MINTEMP).toInt()) {
//            SETDP(DPID::DP_THERMAL_TEMPERATURE_ALARM_NOTIFY, "1");
//        } else {
//            SETDP(DPID::DP_THERMAL_TEMPERATURE_ALARM_NOTIFY, "0");
//        }
//        /* end dummy */

        updateMsg = QString("#maxtemp,%1,%2")
                .arg(GETDP(DPID::DP_THERMAL_TEMPERATURE))
                .arg(GETDP(DPID::DP_THERMAL_TEMPERATURE_ALARM_NOTIFY));
        response.flush();
        response.write(updateMsg.toStdString().data());
        DLOG("Send: %s", updateMsg.toStdString().data());
    } else if(msgBody.contains("GetInterval")) {
        DLOG("Request Read Interval");
        response.flush();
        response.write(QByteArray("ReadInterval"));
    } else if(msgBody.contains("GoSettingPage")) {
        DLOG("Request go to Settings Page");
        response.flush();
        response.write(QByteArray("req_reload"));
    } else {
        DLOG("Not support request %s", msgBody.toStdString().data());
    }

}

void MainPageHandler::sendHTML(HttpResponse &response)
{
    DLOG("");
    response.write(htmlPage.toUtf8());
}
