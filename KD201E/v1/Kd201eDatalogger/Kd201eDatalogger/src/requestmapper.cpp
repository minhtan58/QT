#include "requestmapper.h"

HttpSessionStore* RequestMapper::sessionStore=0;

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent)
{
    isFoundSettingFile = loadSettingFromFile();                 //load settings to common variables
    Datapool::getInstance()->loadSettingsState();

//    DLG << "STATE SETTING: " << QString("%1").arg(kd201eCommon.m_settingsState, 0, 2);

    mainPageController = new MainPageController(parent);
    settingPage = new SettingPage(parent);
    m_timerAutoUpdateIniFile = new QTimer(parent);

    QObject::connect(settingPage, SIGNAL(sgn_requestRestartReadTimer()), mainPageController, SLOT(slt_restartTimer()));
    QObject::connect(m_timerAutoUpdateIniFile, SIGNAL(timeout()), this, SLOT(slt_autoUpdateSettingFromIniFile()));
    m_timerAutoUpdateIniFile->start(TIME_RELOAD_INI);
}

RequestMapper::~RequestMapper()
{
    delete sessionStore;
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    QByteArray msgBody = request.getBody();

    isFoundSettingFile = checkIniFile();

    if (path=="/" && isFoundSettingFile) {
        if(msgBody == "") {
            mainPageController->sendHTML(response);
        }
        else
            mainPageController->service(request, response);
    }

    else if ((path=="/" && !isFoundSettingFile)
             || (path == "/kd201e-settings" && !isFoundSettingFile)
             || (path == "/kd201e-settings" && isFoundSettingFile))
    {
        if(msgBody == "")
            settingPage->sendHTML(response);
        else
            settingPage->service(request, response);
    }
    else {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.");
    }
}

void RequestMapper::slt_autoUpdateSettingFromIniFile()
{
    bool isChanged = false;
    QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
    QString temp;
    if (checkIniFile()) {
        settingFile.beginGroup("General");

        if (settingFile.contains(KEY_STATION_NAME)) {
            temp = settingFile.value(KEY_STATION_NAME).toString();
            if(temp != GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME)) {
                SETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME, temp);
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_COMPANY_NAME)) {
            temp = settingFile.value(KEY_COMPANY_NAME).toString();
            if (temp != GETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME)) {
                SETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME, temp);
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_STATION_TYPE)) {
            temp = settingFile.value(KEY_STATION_TYPE).toString();
            if (temp != GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE)) {
                SETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE, temp);
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_STATION_LINK)) {
            temp = settingFile.value(KEY_STATION_LINK).toString();
            if (temp.size() >= 8 && (!temp.contains("http://")) && (!temp.contains("https://"))) {           //1.1.1.1
                temp = QString("http://%1").arg(temp);
            }
            if (temp != GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONLINK)) {
                SETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONLINK, temp);
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_READ_INTERVAL)) {
            temp = settingFile.value(KEY_READ_INTERVAL).toString();
            if ((temp.toInt() >= 1000 && temp.toInt() <= 12*60*60*1000) && (temp != GETDPDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL))) {    //1s -> 12h
                SETDPDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL, temp);
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_FTP_SERVER)) {
            temp = settingFile.value(KEY_FTP_SERVER).toString();
            if (temp != GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP)) {
                SETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP, temp);
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_FTP_USER)) {
            temp = settingFile.value(KEY_FTP_USER).toString();
            if (temp != GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_USER)) {
                SETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_USER, temp);
                isChanged = true;
            }
        }


        if (settingFile.contains(KEY_FTP_PASSWD)) {
            temp = settingFile.value(KEY_FTP_PASSWD).toString();
            if (temp != GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW)) {
                SETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW, temp);
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_USE_TIME_HTML)){
            temp = settingFile.value(KEY_USE_TIME_HTML).toString();
            bool btemp = ((temp == "0") || (temp == "false")) ? false : true;
            if((btemp && (!GETDPDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML).toInt() == 1)) || ((!btemp) && GETDPDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML).toInt() == 1)) {
                SETDPDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML, btemp ? "1" : "0");
                isChanged = true;
            }
        }

        settingFile.endGroup();

        if(isChanged) {
            Datapool::getInstance()->loadSettingsState();
            emit settingPage->sgn_requestRestartReadTimer();
        }
    }
}

bool RequestMapper::loadSettingFromFile()
{
    if (!checkIniFile())
        return false;

    QSettings settingFile(INI_CONFIG_FILE, QSettings::IniFormat);
    QString temp;
    if (checkIniFile()) {
        settingFile.beginGroup("General");
        temp = settingFile.value(KEY_STATION_NAME).toString();
        SETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME, temp);

        temp = settingFile.value(KEY_COMPANY_NAME).toString();
        SETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME, temp);

        temp = settingFile.value(KEY_STATION_TYPE).toString();
        SETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE, temp);

        temp = settingFile.value(KEY_STATION_LINK).toString();
        if (temp.size() >= 8 && (!temp.contains("http://")) && (!temp.contains("https://"))) {           //1.1.1.1
            temp = QString("http://%1").arg(temp);
        }
        SETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONLINK, temp);

        temp = settingFile.value(KEY_READ_INTERVAL).toString();
        if (temp.toInt() >= 1000 && temp.toInt() <= 12*60*60*1000) {    //1s -> 12h
            SETDPDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL, temp);
        }

        temp = settingFile.value(KEY_FTP_SERVER).toString();
        if (temp.size() >= 8 && (temp.contains("ftp://")) && (temp.contains("ftps://"))) {             //1.1.1.1
            temp.replace("ftp://", "");
            temp.replace("ftps://", "");
            temp.replace("/", "");
        }
        SETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP, temp);

        temp = settingFile.value(KEY_FTP_USER).toString();
        SETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_USER, temp);

        temp = settingFile.value(KEY_FTP_PASSWD).toString();
        SETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW, temp);

        temp = settingFile.value(KEY_USE_TIME_HTML).toString();
        SETDPDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML, ((temp == 0) || (temp == "false")) ? "0" : "1");

        settingFile.endGroup();

        DLOG("Loaded setting from file: %s,%s,%s,%s,%s,%s,%s,%s,%s",
             GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME).toStdString().data(),
             GETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME).toStdString().data(),
             GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE).toStdString().data(),
             GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONLINK).toStdString().data(),
             GETDPDATA(Kd201eEnum::DP_SETTINGS_READ_INTERVAL).toStdString().data(),
             GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP).toStdString().data(),
             GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_USER).toStdString().data(),
             GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW).toStdString().data(),
             GETDPDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML).toStdString().data());
        return true;
    }
    return false;
}
