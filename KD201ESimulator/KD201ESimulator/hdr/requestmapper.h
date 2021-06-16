#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include <QSettings>

#include "httprequesthandler.h"
#include "httpsessionstore.h"
#include "mainpagecontroller.h"

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
public:
    RequestMapper(QObject* parent = nullptr);
    ~RequestMapper();
    void service(HttpRequest& request, HttpResponse& response);
    static HttpSessionStore* sessionStore;

private:
    MainPageController *mainPageController = nullptr;
};

#endif // REQUESTMAPPER_H
