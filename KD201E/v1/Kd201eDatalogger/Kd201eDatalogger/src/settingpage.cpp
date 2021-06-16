#include <QTime>
#include <QDebug>
#include "settingpage.h"

SettingPage::SettingPage(QObject *parent)
    :HttpRequestHandler(parent)
{
    QFile page(PATH_WEB_SETTING);
    if (!page.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream in(&page);
    in.setCodec("UTF-8");
    htmlPage = in.readAll().replace(QString("\n"), QString(""));
}

SettingPage::~SettingPage()
{}

void SettingPage::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    DLOG("Setting Rev: %s", msgBody.toStdString().data());

    if(msgBody.contains("SaveSetting")) {
        DLOG("Saved All");
        saveSetting(msgBody);
        response.flush();
        response.write(QByteArray::fromStdString("req_reload"));
    }
    else if(msgBody.contains("getCurrentSetting")) {
        DLOG("GET SETTING");
        QString updateCurrentValue = QString("CurrentSettings,%1,%2,%3,%4,%5,%6,%7,%8,%9")
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME))
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME))
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE))
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONLINK))
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL))
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP))
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_USER))
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW))
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML).toInt() == 1 ? "true" : "false");

        response.flush();
        response.write(updateCurrentValue.toUtf8());
    }
    else {}

}

void SettingPage::sendHTML(HttpResponse &response)
{
    response.write(htmlPage.toUtf8());
}

void SettingPage::saveSetting(QString settingValue)
{
    QStringList elements = settingValue.split(',');
    if (elements.size() > 9) {
        SETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME, elements.at(1));
        SETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME, elements.at(2));
        SETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE, elements.at(3));
        SETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONLINK, elements.at(4));
        SETDPDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL, elements.at(5));
        SETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP, elements.at(6));
        SETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_USER, elements.at(7));
        SETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW, elements.at(8));
        SETDPDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML, elements.at(9) == "true" ? "1" : "0");

        DLOG("Saved all setting");
        Datapool::getInstance()->loadSettingsState();

        QFile iniFile(INI_CONFIG_FILE);
        if (iniFile.exists()) {
            iniFile.remove();
        }

        QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
        settingFile.beginGroup("General");
        settingFile.setValue(KEY_STATION_NAME,     elements.at(1));
        settingFile.setValue(KEY_COMPANY_NAME,       elements.at(2));
        settingFile.setValue(KEY_STATION_TYPE,     elements.at(3));
        settingFile.setValue(KEY_STATION_LINK,     elements.at(4));
        settingFile.setValue(KEY_READ_INTERVAL,    elements.at(5));
        settingFile.setValue(KEY_FTP_SERVER,       elements.at(6));
        settingFile.setValue(KEY_FTP_USER,         elements.at(7));
        settingFile.setValue(KEY_FTP_PASSWD,       elements.at(8));
        settingFile.setValue(KEY_USE_TIME_HTML,    elements.at(9));
        settingFile.endGroup();

        emit sgn_requestRestartReadTimer();
    }
    else {
        DLOG("can't save setting");
    }

}
