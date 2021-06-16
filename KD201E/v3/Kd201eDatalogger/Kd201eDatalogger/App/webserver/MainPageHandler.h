#ifndef MAINPAGEHANDLER
#define MAINPAGEHANDLER

#include "httprequesthandler.h"
#include "common.h"
#include "Datapool.h"

class MainPageHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    MainPageHandler(QObject* parent = nullptr);
    void service(HttpRequest& request, HttpResponse& response);
    void sendHTML(HttpResponse &response);

private:
    QString htmlPage;

};

#endif // MAINPAGEHANDLER

