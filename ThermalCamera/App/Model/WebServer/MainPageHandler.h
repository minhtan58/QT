#ifndef MAINPAGEHANDLER
#define MAINPAGEHANDLER

#include "httprequesthandler.h"

#define MAIN_PAGE   ":/resources/web/main.html"

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

