#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include <QSettings>

#include "httprequesthandler.h"
#include "httpsessionstore.h"
#include "mainpagecontroller.h"
#include "settingpage.h"

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
public:
    RequestMapper(QObject* parent=0);
    ~RequestMapper();
    void service(HttpRequest& request, HttpResponse& response);
    static HttpSessionStore* sessionStore;

private:
    MainPageController *mainPageController;
    SettingPage *settingPage;

    QTimer *m_timerAutoUpdateIniFile;
    bool isFoundSettingFile;

public slots:
    void slt_autoUpdateSettingFromIniFile();
};

#endif // REQUESTMAPPER_H
