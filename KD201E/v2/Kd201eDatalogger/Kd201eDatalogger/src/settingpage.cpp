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
    DLG << "Setting Rev: " + msgBody;

    if(msgBody.contains("SaveSetting")) {
        DLG << "Saved All";
        saveSetting(msgBody);
        response.flush();
        response.write(QByteArray::fromStdString("req_reload"));
    }
    else if(msgBody.contains("getCurrentSetting")) {
        DLG << "GET SETTING";
        QString updateCurrentValue = QString("CurrentSettings,%1,%2,%3,%4,%5,%6,%7,%8,%9")
                .arg(QString::fromStdString(kd201eSetting.m_stationName))
                .arg(QString::fromStdString(kd201eSetting.m_stationID))
                .arg(QString::fromStdString(kd201eSetting.m_stationType))
                .arg(QString::fromStdString(kd201eSetting.m_stationLink))
                .arg(QString::fromStdString(kd201eSetting.m_readInterval))
                .arg(QString::fromStdString(kd201eSetting.m_ftpServerIP))
                .arg(QString::fromStdString(kd201eSetting.m_ftpUser))
                .arg(QString::fromStdString(kd201eSetting.m_ftpPwd))
                .arg(kd201eSetting.m_useTimeHtml ? "true" : "false");
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
        kd201eSetting.m_stationName     = elements.at(1).toStdString();
        kd201eSetting.m_stationID       = elements.at(2).toStdString();
        kd201eSetting.m_stationType     = elements.at(3).toStdString();
        kd201eSetting.m_stationLink     = elements.at(4).toStdString();
        kd201eSetting.m_readInterval    = elements.at(5).toStdString();
        kd201eSetting.m_ftpServerIP     = elements.at(6).toStdString();
        kd201eSetting.m_ftpUser         = elements.at(7).toStdString();
        kd201eSetting.m_ftpPwd          = elements.at(8).toStdString();
        kd201eSetting.m_useTimeHtml     = elements.at(9) == "true" ? true : false;
        DLG << "Saved all setting";

        kd201eCommon.m_settingsState = getSettingsState();      //update new status

        QFile iniFile(INI_CONFIG_FILE);
        if (iniFile.exists()) {
            iniFile.remove();
        }

        QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
        settingFile.beginGroup("General");
        settingFile.setValue(KEY_STATION_NAME,     elements.at(1));
        settingFile.setValue(KEY_STATION_ID,       elements.at(2));
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
        DLG << "can't save setting";
    }

}
