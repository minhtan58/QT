#ifndef DATAVIEWPAGEHANDLER
#define DATAVIEWPAGEHANDLER

#include "httprequesthandler.h"
#include "common.h"

class DataViewPageHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    DataViewPageHandler(QObject* parent=0);
    ~DataViewPageHandler();
    void service(HttpRequest& request, HttpResponse& response);
    void sendHTML(HttpResponse& response);

signals:
    void requestSearch(QString searchTime);

private:
    QString htmlPage;
    QString m_searchTime;

    const QString constline = QString("<tr class='%1'>"                  //1-odd or even
                                 "<td>%2</td>"                      //2-time
                                 "<td>%3</td>"                      //3-send status
                                 "<td>%4</td>"                      //4-pH
                                 "<td>%5</td>"                      //5-oC
                                 "<td>°C</td>"                      //
                                 "<td>%6</td>"                      //6-TSS
                                 "<td>mg/L</td>"                    //
                                 "<td>%7</td>"                      //7-Flow
                                 "<td>m3/h</td>"                    //
                                 "<td>%8</td>"                      //8-COD
                                 "<td>mg/L</td>"                    //
                                 "</tr>");

    /* to do in next version download button *//*
    const QString constline = QString("<tr class='%1'>"                  //1-odd or even
                                 "<td>%2</td>"                      //2-time
                                 "<td>%3</td>"                      //3-send status
                                 "<td>%4</td>"                      //4-pH
                                 "<td>%5</td>"                      //5-oC
                                 "<td>°C</td>"                      //
                                 "<td>%6</td>"                      //6-TSS
                                 "<td>mg/L</td>"                    //
                                 "<td>%7</td>"                      //7-Flow
                                 "<td>m3/h</td>"                    //
                                 "<td>%8</td>"                      //8-COD
                                 "<td>mg/L</td>"                    //
                                 "<td><button onclick='sendMsgToHost(MSG_DOWNLOAD + txtSearch.value)'>Download</button></td>" //9-event
                                 "</tr>");
    */
};

#endif // DATAVIEWPAGEHANDLER

