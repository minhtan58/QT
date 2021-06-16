#include "common.h"
#include "mainpagecontroller.h"

MainPageController::MainPageController(QObject *parent)
    :HttpRequestHandler(parent)
{
    QFile page(PATH_WEB_DATALOGGER);
    if (!page.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream in(&page);
    in.setCodec("UTF-8");
    htmlPage = in.readAll();
}

void MainPageController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    DLOG("Main Rev: %s", msgBody.toStdString().data());
}

void MainPageController::sendHTML(HttpResponse &response)
{
    response.write(htmlPage.toUtf8());
}
