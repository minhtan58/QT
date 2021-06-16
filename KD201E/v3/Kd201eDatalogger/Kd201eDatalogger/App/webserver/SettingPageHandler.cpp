#include <QTime>
#include <QDebug>
#include "SettingPageHandler.h"

SettingPageHandler::SettingPageHandler(QObject *parent)
    :HttpRequestHandler(parent)
{
    QFile page(PATH_WEB_SETTING);
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
        QString updateCurrentValue = QString("CurrentSettings,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13")
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_PROVINCE_CODE))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_NAME))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_CODE))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_NAME))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_CODE))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_TYPE))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_SOURCE))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_IP))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PORT))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_USER))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PASSWD))
                .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_TIME_USINGHTML));
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
    if (elements.size() > 9) {
        DLOG("Saved all setting");
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_PROVINCE_CODE, elements.at(1));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_COMPANY_NAME, elements.at(2));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_COMPANY_CODE, elements.at(3));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_STATION_NAME, elements.at(4));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_STATION_CODE, elements.at(5));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_STATION_TYPE, elements.at(6));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_HTML_SOURCE, elements.at(7));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_HTML_READ_INTERVAL, elements.at(8));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_FTPSERVER_IP, elements.at(9));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_FTPSERVER_PORT, elements.at(10));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_FTPSERVER_USER, elements.at(11));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_FTPSERVER_PASSWD, elements.at(12));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_TIME_USINGHTML, elements.at(13));
        SettingsLoader::loadIniSettings();
        Datapool::getInstance()->updateSettingsState();
    }
    else {
        DLOG("Can't saved, request invalid %s", settingValue.toStdString().data());
    }

}
