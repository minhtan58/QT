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

    int interval = QString::fromStdString(kd201eSetting.m_readInterval).toInt();
    if (interval >= 1000 && interval <= 60*60*1000) {
        kd201e->start(interval);
        DLG << "kd201e started";
    }
    else {
        DLG << "KD201E can't start, interval = " << QString::number(interval);
    }
}

MainPageController::~MainPageController()
{
    delete kd201e;
}

void MainPageController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    DLG << "Main Rev: " + msgBody;
    QString updateMsg;

    if(msgBody.contains(MSG_UPDATE_STATUS)) {
        DLG << "Update";
        updateMsg = QString("msg_update,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14")
                .arg(QString::fromStdString(kd201eVariant.m_controller))    //1
                .arg(QString::fromStdString(kd201eVariant.m_serial))        //2
                .arg(QString::fromStdString(kd201eVariant.m_software))      //3
                .arg(QString::fromStdString(kd201eVariant.m_time))          //4
                .arg(QString::fromStdString(kd201eVariant.m_id01Val1))      //5
                .arg(QString::fromStdString(kd201eVariant.m_id01Val2))      //6
                .arg(QString::fromStdString(kd201eVariant.m_id02Val1))      //7
                .arg(QString::fromStdString(kd201eVariant.m_id02Val2))      //8
                .arg(QString::fromStdString(kd201eVariant.m_id03Val1))      //9
                .arg(QString::fromStdString(kd201eVariant.m_id03Val2))      //10
                .arg(QString::fromStdString(kd201eVariant.m_id04Val1))      //11
                .arg(QString::fromStdString(kd201eVariant.m_id04Val2))      //12
                .arg((kd201eCommon.m_isStationConnected ? "Connected" : "Disconnected"))    //13
                .arg((kd201eCommon.m_isFtpConnected ? "Connected" : "Disconnected"));       //14

        response.flush();
        response.write(QByteArray::fromStdString(updateMsg.toStdString()));
    }
    else if(msgBody.contains("GetInterval")) {
        DLG << "Request Read Interval";
        response.flush();
        response.write(QByteArray::fromStdString("ReadInterval"));
    }
    else if(msgBody.contains("GoSettingPage")) {
        DLG << "Request go to Settings Page";
        response.flush();
        response.write(QByteArray::fromStdString("req_reload"));
    }
    else {
        DLG << "Main Rev no case: " + msgBody;
    }

}

void MainPageController::sendHTML(HttpResponse &response)
{
    response.write(htmlPage.toUtf8());
}

void MainPageController::slt_restartTimer()
{
    kd201e->start(QString::fromStdString(kd201eSetting.m_readInterval).trimmed().toInt());
}
