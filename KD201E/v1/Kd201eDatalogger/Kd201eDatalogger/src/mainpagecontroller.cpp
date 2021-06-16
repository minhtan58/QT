#include <QTime>
#include <QDebug>
#include "mainpagecontroller.h"

MainPageController::MainPageController(QObject *parent)
    :HttpRequestHandler(parent)
{
    QFile page(PATH_WEB_DATALOGGER);
    if (!page.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream in(&page);
    in.setCodec("UTF-8");
    htmlPage = in.readAll().replace(QString("\n"), QString(""));
    kd201e = new KD201E();

    int interval = GETDPDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL).toUInt();
    if (interval >= 1000 && interval <= 60*60*1000) {
        kd201e->start(interval);
        DLOG("kd201e started");
    }
    else {
        DLOG("KD201E can't start, interval = %d", interval);
    }
}

MainPageController::~MainPageController()
{
    if(kd201e) {
        delete kd201e;
        kd201e = nullptr;
    }
}

void MainPageController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    DLOG("Main Rev: %s", msgBody.toStdString().data());
    QString updateMsg;

    if(msgBody.contains(MSG_UPDATE_STATUS)) {
        DLOG("Update");
        updateMsg = QString("msg_update,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11")
                .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_CONTROLLER))
                .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_SERIAL))
                .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_SOFTWARE))
                .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_TIME))
                .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_PH))
                .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_OC))
                .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_TSS))
                .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_FLOW))
                .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_COD))
                .arg(GETDPDATA(Kd201eEnum::DP_COMMON_IS_STATION_CONNETED).toInt() == 1 ? "Connected" : "Disconnected")
                .arg(GETDPDATA(Kd201eEnum::DP_COMMON_IS_FTP_CONNETED).toInt() == 1 ? "Connected" : "Disconnected");       //11

        response.flush();
        response.write(QByteArray::fromStdString(updateMsg.toStdString()));
    }
    else if(msgBody.contains("GetInterval")) {
        DLOG("Request Read Interval");
        response.flush();
        response.write(QByteArray::fromStdString("ReadInterval"));
    }
    else if(msgBody.contains("GoSettingPage")) {
        DLOG("Request go to Settings Page");
        response.flush();
        response.write(QByteArray::fromStdString("req_reload"));
    }
    else {
        DLOG("Main Rev no case: %s", msgBody.toStdString().data());
    }

}

void MainPageController::sendHTML(HttpResponse &response)
{
    response.write(htmlPage.toUtf8());
}

void MainPageController::slt_restartTimer()
{
    kd201e->start(GETDPDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL).toInt());
}
