#ifndef MAINPAGECONTROLLER
#define MAINPAGECONTROLLER

#include "httprequesthandler.h"

class MainPageController : public HttpRequestHandler {
    Q_OBJECT
public:
    MainPageController(QObject* parent = nullptr);
    void service(HttpRequest& request, HttpResponse& response);
    void sendHTML(HttpResponse &response);

private:
    QString htmlPage;
};

#endif // MAINPAGECONTROLLER

