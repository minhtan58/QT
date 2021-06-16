#ifndef MAINPAGECONTROLLER
#define MAINPAGECONTROLLER

#include "httprequesthandler.h"
#include "common.h"
#include "KD201E.h"

class MainPageController : public HttpRequestHandler {
    Q_OBJECT
public:
    MainPageController(QObject* parent=0);
    ~MainPageController();
    void service(HttpRequest& request, HttpResponse& response);
    void sendHTML(HttpResponse &response);

private:
    KD201E *kd201e;
    QString htmlPage;

public slots:
    void slt_restartTimer();

};

#endif // MAINPAGECONTROLLER

