#include "requestmapper.h"

HttpSessionStore* RequestMapper::sessionStore=0;

RequestMapper::RequestMapper(QObject* parent)
    : HttpRequestHandler(parent)
{
    Datapool::getInstance()->updateSettingsState();
    m_mainPage = new MainPageHandler(this);
    m_settingPage = new SettingPageHandler(this);
    m_dataviewPage = new DataViewPageHandler(this);
}

RequestMapper::~RequestMapper()
{
    delete sessionStore;
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    QByteArray msgBody = request.getBody();

    if (path == "/" && isExistsIniSettingFile()) {
        if(msgBody.isEmpty()) {
            m_mainPage->sendHTML(response);
        } else {
            m_mainPage->service(request, response);
        }
    } else if ((path=="/" && !isExistsIniSettingFile())
               ||((path=="/history" && !isExistsIniSettingFile()))
               || (path == "/settings")) {
        if(msgBody.isEmpty()) {
            m_settingPage->sendHTML(response);
        } else {
            m_settingPage->service(request, response);
        }
    } else if(path=="/history" && isExistsIniSettingFile()) {
        if(msgBody.isEmpty()) {
            m_dataviewPage->sendHTML(response);
        } else {
            m_dataviewPage->service(request, response);
        }
    } else {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.");
    }
}
