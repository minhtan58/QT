#include <QTime>
#include <QDebug>
#include "DataViewPageHandler.h"
#include "DBManager.h"
#include "KD201E.h"

DataViewPageHandler::DataViewPageHandler(QObject *parent)
    : HttpRequestHandler(parent)
{
    connect(this, SIGNAL(requestSearch(QString)), Datapool::getInstance(), SLOT(requestGetHistoryList(QString)), Qt::UniqueConnection);
    m_searchTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    emit requestSearch(m_searchTime);
}

DataViewPageHandler::~DataViewPageHandler()
{}

void DataViewPageHandler::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    DLOG("Dataview Rev: %s", msgBody.toStdString().data());
    if(msgBody.contains("search|")) {
        QString searchTime = msgBody.replace("search|", "");
        if(searchTime.isEmpty()) {
            return;
        } else {
            m_searchTime = searchTime;
            emit requestSearch(m_searchTime);
        }
        QThread::msleep(500);
        response.write("refresh");
        response.flush();
    } else if(msgBody.contains("download|")) {
    } else {}

}

void DataViewPageHandler::sendHTML(HttpResponse &response)
{
    DLOG("Send page");
    QList<DataRow> list;
    QString headPage =
            "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>"
            "<html xmlns='http://www.w3.org/1999/xhtml'>"
            "<head>"
                "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>"
                "<meta http-equiv='cache-control' content='no-cache'>"
                "<meta name='viewport' content='width=device-width'>"
                "<title>Data View</title>"
                    "<style type='text/css'>"
                            "body {font-family: Tahoma, Verdana, Arial, sans-serif; font-size: 0.8em;}"
                            ".CaptionRow {font-weight:bold; background: #EFF3EB;}"
                            ".OddRow {background: #EFF3EB;}"
                            ".capitals {font-variant: small-caps;}"
                    "</style>"
            "</head>"

            "<script type='text/javascript'>"
                "var xhttpRequest;"
                "var MSG_SEARCH = 'search|';"
                "var MSG_DOWNLOAD = 'download|';"
                "xhttpRequest = new XMLHttpRequest();"

                "function sendMsgToHost(msg) {"
                    "xhttpRequest.open('POST', '', true);"
                    "xhttpRequest.onreadystatechange = callBack;"
                    "xhttpRequest.send(msg);"
                "}"

                "function callBack() {"
                    "if (this.readyState == 4 && this.status == 200) {"
                        "var response = this.responseText;"
                        "if(response.includes('refresh')) {"
                            "location.reload();"
                        "} else {"
                            "downloadFile(filename);"
                        "}"
                    "}"
                    "else {}"
                "}"

                "function downloadFile(fileName) {"
                    "var downloadLink = document.getElementById('link');"
                    "downloadLink.href = fileName;"
                    "downloadLink.click();"
                "}"

            "</script>"

            "<body><h1 class='capitals'>History Data View</h1>"

            "<h2>Logger Storage Data</h2>"

            "<a id='link' download hidden></a>"
            "<input type='date' id='txtSearch' value='%1'>"
            "<button onclick='sendMsgToHost(MSG_SEARCH + txtSearch.value)'>View</button>"

            "<table border='0' cellspacing='2%' cellpadding='3%'>"
                    "<colgroup>"
                    "<col class='SensorID'>"
                    "<col class='SensorState'>"
                    "<col class='SensorModel'>"
                    "<col class='SensorSerNo'>"
                    "<col class='SensorName'>"
                    "<col class='MainValue'>"
                    "<col class='MainValUnit'>"
                    "<col class='MainValPara'>"
                    "<col class='SubValue'>"
                    "<col class='SubValUnit'>"
                    "<col class='SensorInfo'>"
                    "</colgroup>"
                    "<thead>"
                    "<tr class='CaptionRow'>"
                            "<td>Time</td>"
                            "<td>Status</td>"
                            "<td>pH</td>"
                            "<td colspan='2'>Temperature</td>"
                            "<td colspan='2'>TSS</td>"
                            "<td colspan='2'>FLOW</td>"
                            "<td colspan='2'>COD</td>"
//                            "<td>Export</td>"
                    "</tr>"
                    "</thead>"
                    "<tbody>";
    QString tailPage =
            "</tbody></table>"
            "</body></html>";

    list = Datapool::getInstance()->getHistoryList();
    DLOG("ListSize: %d, search time: %s", list.size(), m_searchTime.toStdString().data());
    QString line;
    QString page = headPage.arg(m_searchTime);
    for (int idx = 0; idx < list.size(); ++idx) {
        line = constline
                .arg(idx%2 ? "OddRow" : "EvenRow")
                .arg(list.at(idx).time)
                .arg(list.at(idx).isSent)
                .arg(list.at(idx).varPH)
                .arg(list.at(idx).varOC)
                .arg(list.at(idx).varTSS)
                .arg(list.at(idx).varFLOW)
                .arg(list.at(idx).varCOD);
        page.append(line);
    }
    page.append(tailPage);
    response.write(page.toUtf8());
}
