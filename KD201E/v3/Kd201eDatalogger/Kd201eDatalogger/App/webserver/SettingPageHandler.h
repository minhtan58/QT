#ifndef SETTINGPAGEHANDLER
#define SETTINGPAGEHANDLER

#include "httprequesthandler.h"
#include "common.h"
#include "Datapool.h"
#include "SettingsLoader.h"

class SettingPageHandler : public HttpRequestHandler
{
    Q_OBJECT
private:
    QString htmlPage;
public:
    SettingPageHandler(QObject* parent=0);
    ~SettingPageHandler();
    void service(HttpRequest& request, HttpResponse& response);
    void sendHTML(HttpResponse& response);
    void receiveData();

    void saveSetting(QString settingValue);
};

#endif // SETTINGPAGEHANDLER

