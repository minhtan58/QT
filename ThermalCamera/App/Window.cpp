/****************************************************************************

    Copyright (C) 2018 by LGE
    File: Window.cpp
    Create: 28
    Author: Vuong Nguyen

 ****************************************************************************/

#include "Window.h"
#include "Defines.h"
#include "QMLConstants.h"
#include "QQuickImage.h"

Window::Window(QObject *parent)
    : QObject(parent)
{
    initWindow();
}

void Window::show()
{
    displayScreen(SCR_THERMAL_NORMAL);
}

void Window::initWindow()
{
    qmlRegisterType<QQuickImage>("QQuickImage", 1, 0, "QQuickImage");
    m_qmlEngine.rootContext()->setContextProperty("Constants", new QMLConstants(this));
    loadIniSettings();

    m_qmlEngine.load(QUrl(QStringLiteral("qrc:/resources/qml/main.qml")));
    if (m_qmlEngine.rootObjects().isEmpty()) {
        DLOG("");
        return;
    }

    m_screenAdapter = new ScreenAdapter(m_qmlEngine.rootObjects().at(0)->findChild<QObject*>("appContainer"), this);
    m_modelHandler = new ModelHandler(this);
    m_modelHandler->start();
}

void Window::displayScreen(int screenId)
{
    DLOG("display screen - %d", screenId);
    if(m_screenAdapter && m_screenAdapter->currentScreenId() == screenId) {
        return;
    }
    m_screenAdapter->createScreen(screenId);
    connect(DataManager::getInstance(), SIGNAL(dataChanged(int,QString)), m_screenAdapter, SLOT(updateAppData(int,QString)), Qt::UniqueConnection);
}

void Window::loadIniSettings()
{
    DLOG("Load ini settings start...");
    if(!SettingsLoader::exists()) {
        SettingsLoader::createSettingsFile();

        /* Default value */
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_DEVICETYPE, "0");
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_THRESOLD_MAXTEMP, "100");
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_THRESOLD_MINTEMP, "-10");
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_VERIFYTIME,       "5");
        SETDP(DPID::DP_SETTINGS_DEVICETYPE, "0");
        SETDP(DPID::DP_SETTINGS_THRESOLD_MAXTEMP, "100");
        SETDP(DPID::DP_SETTINGS_THRESOLD_MINTEMP, "-10");
        SETDP(DPID::DP_SETTINGS_VERIFYTIME, "5");
    } else {
        SettingsStruct settingsStruct = SettingsLoader::loadSettings();
        SETDP(DPID::DP_SETTINGS_DEVICEID, settingsStruct.gDeviceId);
        SETDP(DPID::DP_SETTINGS_DEVICENAME, settingsStruct.gDeviceName);
        SETDP(DPID::DP_SETTINGS_DEVICETYPE, settingsStruct.gDeviceType);
        SETDP(DPID::DP_SETTINGS_THRESOLD_MAXTEMP, settingsStruct.gThresoldMaxTemp);
        SETDP(DPID::DP_SETTINGS_THRESOLD_MINTEMP, settingsStruct.gThresoldMinTemp);
        SETDP(DPID::DP_SETTINGS_VERIFYTIME, settingsStruct.gVerifyTime);
        SETDP(DPID::DP_SETTINGS_SERVERIP, settingsStruct.gServerIP);
        SETDP(DPID::DP_SETTINGS_SERVERPORT, settingsStruct.gServerPort);
    }
    DLOG("Load ini settings finished");
}
