#include "MainPageHandler.h"

MainPageHandler::MainPageHandler(QObject *parent)
    :HttpRequestHandler(parent)
{
    QFile page(PATH_WEB_DATALOGGER);
    if (!page.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream in(&page);
    in.setCodec("UTF-8");
    htmlPage = in.readAll().replace("\n", "");
}

void MainPageHandler::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    QString updateMsg;
    if(msgBody.contains(MSG_UPDATE_STATUS)) {
        DLG_THR << "Update";
        updateMsg = QString("msg_update,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11")
                .arg(GETDPDATA(KD201EEnum::DP_VARIABLES_CONTROLLER))
                .arg(GETDPDATA(KD201EEnum::DP_VARIABLES_SERIAL))
                .arg(GETDPDATA(KD201EEnum::DP_VARIABLES_SOFTWARE))
                .arg(GETDPDATA(KD201EEnum::DP_VARIABLES_TIME))
                .arg(GETDPDATA(KD201EEnum::DP_VARIABLES_PH))
                .arg(GETDPDATA(KD201EEnum::DP_VARIABLES_OC))
                .arg(GETDPDATA(KD201EEnum::DP_VARIABLES_TSS))
                .arg(GETDPDATA(KD201EEnum::DP_VARIABLES_FLOW))
                .arg(GETDPDATA(KD201EEnum::DP_VARIABLES_COD))
                .arg(GETDPDATA(KD201EEnum::DP_COMMON_HTML_CONNETED).toInt())
                .arg(GETDPDATA(KD201EEnum::DP_COMMON_FTPSERVER_CONNETED).toInt());       //11
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
    response.write(htmlPage.toUtf8());
}
