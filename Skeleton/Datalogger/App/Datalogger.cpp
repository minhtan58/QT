/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: Datalogger.cpp
    Create: 11/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#include "Datalogger.h"

Datalogger::Datalogger(QObject *parent)
    : QObject(parent)
{
    DLOG("Datalogger Create");
    qmlRegisterType<Delivery>("Delivery", 1, 0, "Delivery");
    qmlRegisterType<CEMSEnum>("CEMSEnum", 1, 0, "CEMSEnum");
    qRegisterMetaType<CEMSEnum::DatapoolID>("CEMSEnum::DatapoolID");
    qRegisterMetaType<CEMSEnum::HMIEvent>("CEMSEnum::HMIEvent");
}

Datalogger::~Datalogger()
{}

void Datalogger::exec()
{
    DataManager::getInstance();
    initDatalogger();
    m_modelHandler->start();
    showScreen(SCR_DATAVIEW);
//    showOverlay(SPLASH_SCREEN, 3000, Z_SPLASH);
}

void Datalogger::initDatalogger()
{
    m_modelHandler = new ModelHandler(this);

    connect(Delivery::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), this, SLOT(hmiHandle(QString,int,QString)));

    m_qmlAppEngine.rootContext()->setContextProperty("CEMSConstants", &m_qmlConstant);
    m_qmlAppEngine.rootContext()->setContextProperty("Delivery", Delivery::getInstance());

    m_qmlAppEngine.load(QUrl(QStringLiteral("qrc:/resources/main.qml")));

    m_screenAdapter = new ScreenAdapter(&m_qmlAppEngine, this);
    m_keyboardAdapter = new KeyboardAdapter(m_qmlAppEngine.rootObjects().at(0)->findChild<QQuickItem*>("keyboardContainer"), this);
    m_topBarAdapter = new TopBarAdapter(m_qmlAppEngine.rootObjects().at(0)->findChild<QQuickItem*>("topbarContainer"), this);
    connect(DataManager::getInstance(), SIGNAL(dataChanged(int)), m_topBarAdapter, SLOT(updateAppData(int)), Qt::UniqueConnection);
    connect(Delivery::getInstance(), SIGNAL(keyboardEvent(int,QString)), m_keyboardAdapter, SLOT(keyboardKeyHandle(int,QString)), Qt::UniqueConnection);
}

void Datalogger::showScreen(int screenId)
{
    DLOG("display screen - %d", screenId);
    if(m_screenAdapter && m_screenAdapter->getCurrentScreen() == screenId) {
        return;
    }
    m_screenAdapter->setScreenId(screenId);
    m_screenAdapter->createScreen();
    if(m_keyboardAdapter->isKeyboardShow())
        m_keyboardAdapter->hideKeyboard();
    connect(DataManager::getInstance(), SIGNAL(dataChanged(int)), m_screenAdapter, SLOT(updateAppData(int)), Qt::UniqueConnection);
}

void Datalogger::showKeyboard(int mode)
{
    if(!m_keyboardAdapter->isKeyboardShow())
        m_keyboardAdapter->showKeyboard(mode);
}

void Datalogger::showOverlay(int overlayId, int timeout, int layer, QString message)
{
    Q_UNUSED(message)
    DLOG("display overlay - %d", overlayId);

    QQuickItem *container = m_qmlAppEngine.rootObjects().at(0)->findChild<QQuickItem*>("overlayContainer");
    if(!container) {
        DLOG("container null");
        return;
    }

    if(layer > Z_BACKGROUND)
        container->setProperty("z", QVariant::fromValue(layer));
    container->setProperty("source", QVariant::fromValue(screenList.value(overlayId)));
    QObject *overlay = qvariant_cast<QObject*>(container->property("item"));
    overlay->setProperty("timeout", QVariant::fromValue(timeout));
    if(!message.isEmpty())
        overlay->setProperty("message", QVariant::fromValue(message));
}

void Datalogger::hideOverlay()
{
    QQuickItem *container = m_qmlAppEngine.rootObjects().at(0)->findChild<QQuickItem*>("overlayContainer");
    if(!container) {
        DLOG("container null");
        return;
    }

    container->setProperty("source", "");
}

void Datalogger::screenShot()
{
    QQuickWindow *_rootObject = qobject_cast<QQuickWindow *>(m_qmlAppEngine.rootObjects().at(0));
    if (_rootObject) {
        QImage _image = _rootObject->grabWindow();
        QString savePath;
#ifdef __WIN32
        savePath = "D://CEMS/";
#elif __linux__
        savePath = "/user/CEMS/";
#else
        savePath = "";
#endif
        QFile _file(savePath + "CEMS_Screenhot" + QDateTime::currentDateTime().toString("_yyyy_MM_dd_HH_mm_ss_zzz") + ".png");
        _file.open(QIODevice::WriteOnly);
        if (_file.isOpen()) {
            _image.save(&_file, "PNG");
        }
        showOverlay(QN_COMMON, 1000, Z_OVERLAY, "Save Screenshot at\n" + savePath);
    }
}

void Datalogger::hmiHandle(QString objectName, int eventId, QString param)
{
    DLOG("Received event: %d, params - %s", eventId, param.toStdString().data());
    switch (eventId) {
    case CEMSEnum::HMI_BUTTON_HOME: {
        if(m_screenAdapter && m_screenAdapter->getCurrentScreen() != SCR_DATAVIEW){
            showScreen(SCR_DATAVIEW);
        }
        break;
    }
    case CEMSEnum::HMI_BUTTON_SETTING: {
        if(m_screenAdapter->getCurrentScreen() < SCR_SETTINGS_OVERVIEW
                || m_screenAdapter->getCurrentScreen() > SCR_SETTINGS_DEVELOPMENT) {
            showScreen(SCR_SETTINGS_OVERVIEW);
        }
        break;
    }
    case CEMSEnum::HMI_BUTTON_HISTORY: {
        showScreen(SCR_HISTORY_DATAVIEW);
        break;
    }
    case CEMSEnum::HMI_TAB_SELECT: {
        if(param == "overview" || param.isEmpty()) {
            showScreen(SCR_SETTINGS_OVERVIEW);
        } else if(param == "general") {
            showScreen(SCR_SETTINGS_GENERAL);
        } else if(param == "network") {
            showScreen(SCR_SETTINGS_NETWORK);
        } else if(param == "serialport") {
            showScreen(SCR_SETTINGS_SERIALPORT);
        } else if(param == "aircoefficient") {
            showScreen(SCR_SETTINGS_AIRCOEFFICIENT);
        } else if(param == "alarm") {
            showScreen(SCR_SETTINGS_ALARM);
        } else if(param == "development") {
            showScreen(SCR_SETTINGS_DEVELOPMENT);
        }
        break;
    }
    case CEMSEnum::HMI_TEXTINPUT_FOCUS_CHANGED: {
        int keyMode = param.toUInt();
        if(m_keyboardAdapter) {
            m_keyboardAdapter->setCurrentTextInput(m_qmlAppEngine.rootObjects().at(0)->findChild<QObject*>(objectName));
            showKeyboard(keyMode);
        }
        break;
    }
    case CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP: {
        QStringList paramList = getListParam(param);
        showOverlay(QN_COMMON, paramList.at(0).toUInt(), Z_OVERLAY, paramList.at(1));
        break;
    }
    case CEMSEnum::HMI_REQUEST_HIDE_POPUP: {
        hideOverlay();
        break;
    }
    case CEMSEnum::HMI_BUTTON_DEVELOPER_SAVE_SCREENSHOT: {
        screenShot();
        break;
    }
    case CEMSEnum::HMI_REQUEST_SHOW_EXPORT_POPUP: {
        showOverlay(POPUP_EXPORT_FILE, 7000);
        break;
    }
    case CEMSEnum::HMI_BUTTON_BELL: {
        if(m_screenAdapter->getCurrentScreen() == SCR_DATAVIEW) {
            showScreen(SCR_SETTINGS_ALARM);
        } else {
            showScreen(SCR_DATAVIEW);
        }
        break;
    }
    default:
        break;
    }
}

