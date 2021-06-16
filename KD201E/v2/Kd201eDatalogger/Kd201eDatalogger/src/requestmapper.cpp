#include "requestmapper.h"

HttpSessionStore* RequestMapper::sessionStore=0;

Kd201eVariables kd201eVariant = {"!", "!", "!", "!", "!", "!", "!", "!","!", "!", "!", "!"};
Kd201eSetting kd201eSetting = {"!", "!", "!", "!","!", "!", "!", "!", false};
Kd201eCommon kd201eCommon = {false, false, STATE_INVALID_ALL ,"", {}};

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent)
{
    isFoundSettingFile = loadSettingFromFile();                 //load settings to common variables
    kd201eCommon.m_settingsState = getSettingsState();          //update new status

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
    delete mainPageController;
    delete settingPage;
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
            if(temp.toStdString() != kd201eSetting.m_stationName) {
                kd201eSetting.m_stationName = temp.toStdString();
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_STATION_ID)) {
            temp = settingFile.value(KEY_STATION_ID).toString();
            if (temp.toStdString() != kd201eSetting.m_stationID) {
                kd201eSetting.m_stationID = temp.toStdString();
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_STATION_TYPE)) {
            temp = settingFile.value(KEY_STATION_TYPE).toString();
            if (temp.toStdString() != kd201eSetting.m_stationType) {
                kd201eSetting.m_stationType = temp.toStdString();
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_STATION_LINK)) {
            temp = settingFile.value(KEY_STATION_LINK).toString();
            if (temp.size() >= 8 && (!temp.contains("http://")) && (!temp.contains("https://"))) {           //1.1.1.1
                temp = QString("http://%1").arg(temp);
            }
            if (temp.toStdString() != kd201eSetting.m_stationLink) {
                kd201eSetting.m_stationLink = temp.toStdString();
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_READ_INTERVAL)) {
            temp = settingFile.value(KEY_READ_INTERVAL).toString();
            if ((temp.toInt() >= 1000 && temp.toInt() <= 12*60*60*1000) && (temp.toStdString() != kd201eSetting.m_readInterval)) {    //1s -> 12h
                kd201eSetting.m_readInterval = temp.toStdString();
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_FTP_SERVER)) {
            temp = settingFile.value(KEY_FTP_SERVER).toString();
            if (temp.toStdString() != kd201eSetting.m_ftpServerIP) {
                kd201eSetting.m_ftpServerIP = temp.toStdString();
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_FTP_USER)) {
            temp = settingFile.value(KEY_FTP_USER).toString();
            if (temp.toStdString() != kd201eSetting.m_ftpUser) {
                kd201eSetting.m_ftpUser = temp.toStdString();
                isChanged = true;
            }
        }


        if (settingFile.contains(KEY_FTP_PASSWD)) {
            temp = settingFile.value(KEY_FTP_PASSWD).toString();
            if (temp.toStdString() != kd201eSetting.m_ftpPwd) {
                kd201eSetting.m_ftpPwd = temp.toStdString();
                isChanged = true;
            }
        }

        if (settingFile.contains(KEY_USE_TIME_HTML)){
            temp = settingFile.value(KEY_USE_TIME_HTML).toString();
            bool btemp = ((temp == "0") || (temp == "false")) ? false : true;
            if((btemp && (!kd201eSetting.m_useTimeHtml)) || ((!btemp) && kd201eSetting.m_useTimeHtml)) {
                kd201eSetting.m_useTimeHtml = btemp;
                isChanged = true;
            }
        }

        settingFile.endGroup();

        if(isChanged) {
            kd201eCommon.m_settingsState = getSettingsState();      //update new status
            emit settingPage->sgn_requestRestartReadTimer();
        }
    }
}
