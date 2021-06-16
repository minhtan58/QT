#ifndef SETTINGPAGE
#define SETTINGPAGE

#include "httprequesthandler.h"
#include "common.h"

class SettingPage : public HttpRequestHandler {
    Q_OBJECT

private:
    QString htmlPage;
public:
    SettingPage(QObject* parent=0);
    ~SettingPage();
    void service(HttpRequest& request, HttpResponse& response);
    void sendHTML(HttpResponse& response);
    void receiveData();

    void saveSetting(QString settingValue);

signals:
    void sgn_requestRestartReadTimer();
};

#endif // SETTINGPAGE

