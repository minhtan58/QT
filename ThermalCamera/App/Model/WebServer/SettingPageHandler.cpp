#include "Common.h"
#include "Defines.h"
#include "SettingPageHandler.h"
#include "SettingsLoader.h"
#include "DataManager.h"

SettingPageHandler::SettingPageHandler(QObject *parent)
    :HttpRequestHandler(parent)
{
    QFile page(SETTING_PAGE);
    if (!page.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream in(&page);
    in.setCodec("UTF-8");
    htmlPage = in.readAll().replace(QString("\n"), QString(""));
}

SettingPageHandler::~SettingPageHandler()
{}

void SettingPageHandler::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    DLOG("Setting Rev: %s", msgBody.toStdString().data());

    if(msgBody.contains("SaveSetting")) {
        DLOG("Saved All");
        saveSetting(msgBody);
        response.flush();
        response.write(QByteArray::fromStdString("req_reload"));
    } else if(msgBody.contains("getCurrentSetting")) {
        QString updateCurrentValue = QString("CurrentSettings,%1,%2,%3,%4,%5,%6,%7,%8")
                .arg(GETDP(DPID::DP_SETTINGS_DEVICEID))
                .arg(GETDP(DPID::DP_SETTINGS_DEVICENAME))
                .arg(GETDP(DPID::DP_SETTINGS_DEVICETYPE))
                .arg(GETDP(DPID::DP_SETTINGS_THRESOLD_MAXTEMP))
                .arg(GETDP(DPID::DP_SETTINGS_THRESOLD_MINTEMP))
                .arg(GETDP(DPID::DP_SETTINGS_VERIFYTIME))
                .arg(GETDP(DPID::DP_SETTINGS_SERVERIP))
                .arg(GETDP(DPID::DP_SETTINGS_SERVERPORT));
        response.flush();
        response.write(updateCurrentValue.toUtf8());
        DLOG("Send: %s", updateCurrentValue.toStdString().data());
    } else {}

}

void SettingPageHandler::sendHTML(HttpResponse &response)
{
    response.write(htmlPage.toUtf8());
}

void SettingPageHandler::saveSetting(QString settingValue)
{
    QStringList elements = settingValue.split(',');
    if (elements.size() > 7) {
        DLOG("Saved all setting");

        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_DEVICEID,         elements.at(1));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_DEVICENAME,       elements.at(2));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_DEVICETYPE,       elements.at(3));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_THRESOLD_MAXTEMP, elements.at(4));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_THRESOLD_MINTEMP, elements.at(5));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_VERIFYTIME,       elements.at(6));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_SERVERIP,         elements.at(7));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_SERVERPORT,       elements.at(8));

        SETDP(DPID::DP_SETTINGS_DEVICEID,           elements.at(1));
        SETDP(DPID::DP_SETTINGS_DEVICENAME,         elements.at(2));
        SETDP(DPID::DP_SETTINGS_DEVICETYPE,         elements.at(3));
        SETDP(DPID::DP_SETTINGS_THRESOLD_MAXTEMP,   elements.at(4));
        SETDP(DPID::DP_SETTINGS_THRESOLD_MINTEMP,   elements.at(5));
        SETDP(DPID::DP_SETTINGS_VERIFYTIME,         elements.at(6));
        SETDP(DPID::DP_SETTINGS_SERVERIP,           elements.at(7));
        SETDP(DPID::DP_SETTINGS_SERVERPORT,         elements.at(8));
    }
    else {
        DLOG("Can't saved, request invalid %s", settingValue.toStdString().data());
    }

}
