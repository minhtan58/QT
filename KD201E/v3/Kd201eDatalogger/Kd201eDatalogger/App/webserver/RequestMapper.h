#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include <QSettings>
#include "httprequesthandler.h"
#include "httpsessionstore.h"
#include "MainPageHandler.h"
#include "SettingPageHandler.h"
#include "DataViewPageHandler.h"
#include "Datapool.h"

class RequestMapper : public HttpRequestHandler
{
    Q_OBJECT
public:
    explicit RequestMapper(QObject* parent = nullptr);
    static HttpSessionStore* sessionStore;
    ~RequestMapper();
    void service(HttpRequest& request, HttpResponse& response);

private:
    MainPageHandler *m_mainPage = nullptr;
    SettingPageHandler *m_settingPage = nullptr;
    DataViewPageHandler *m_dataviewPage = nullptr;
};

#endif // REQUESTMAPPER_H
