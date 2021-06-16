/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: Window.cpp
    Create: 11/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#include "Window.h"

Window::Window(QObject *parent)
    : QObject(parent)
{
    DLOG("Window Create");
    qmlRegisterType<HMIEvents>("HMIEvents", 1, 0, "HMIEvents");
    MODEL;
    UIBRIDGE;
}

Window::~Window()
{}

void Window::start()
{
    initDatalogger();
    displayScreen(SCR_HOME);
//    historyScreenPushBack(SCR_HOME);
//    displayScreen(SCR_WORK_MAIN);
//    showOverlay(SPLASH_SCREEN, 3000, Z_SPLASH);
}

void Window::initDatalogger()
{
    connect(UIBRIDGE, SIGNAL(hmiEvent(QString,int,QString)), this, SLOT(hmiHandle(QString,int,QString)), Qt::QueuedConnection);

    m_qmlAppEngine.rootContext()->setContextProperty("UIBridge", UIBRIDGE);
    m_qmlAppEngine.rootContext()->setContextProperty("AppModel", MODEL);
    m_qmlAppEngine.rootContext()->setContextProperty("Fonts", new FontManager(this));

    m_qmlAppEngine.load(QUrl(QStringLiteral("qrc:/resources/main.qml")));

    m_modelHandler = new ModelHandler(this);
    m_screenAdapter = new ScreenAdapter(&m_qmlAppEngine, this);
    m_keyboardAdapter = new KeyboardAdapter(m_qmlAppEngine.rootObjects().at(0)->findChild<QQuickItem*>("keyboardContainer"), this);
    m_topbarContainer = m_qmlAppEngine.rootObjects().at(0)->findChild<QQuickItem*>("topbarContainer");
    m_statusbarContainer = m_qmlAppEngine.rootObjects().at(0)->findChild<QQuickItem*>("statusbarContainer");
    m_overlayContainer = m_qmlAppEngine.rootObjects().at(0)->findChild<QQuickItem*>("overlayContainer");
    m_quicknotesContainer = m_qmlAppEngine.rootObjects().at(0)->findChild<QQuickItem*>("quicknotesContainer");
    connect(UIBRIDGE, SIGNAL(keyboardEvent(int,QString)), m_keyboardAdapter, SLOT(keyboardKeyHandle(int,QString)), Qt::QueuedConnection);
}

void Window::displayScreen(int screenId)
{
    DLOG("displayScreen %s", MODEL->screenName(screenId).toStdString().data());
    if(screenId == m_screenAdapter->getCurrentScreen()) {
        return;
    }

    //DLOG("starting load screen %d", screenId);
    m_screenAdapter->showScreen(screenId);

    showTopbar(m_screenAdapter->isShowTopbar());
    showStatusbar(m_screenAdapter->isShowStatusbar());

    if(m_keyboardAdapter->isKeyboardShow())
        m_keyboardAdapter->hideKeyboard();
    //DLOG("Load screen %d finished", screenId);
}

void Window::showKeyboard(int mode)
{
    if(!m_keyboardAdapter->isKeyboardShow())
        m_keyboardAdapter->showKeyboard(mode);
}

void Window::hideKeyboard()
{
    m_keyboardAdapter->hideKeyboard();
}

void Window::showOverlay(int overlayId, int timeout, int layer, QString message)
{
    Q_UNUSED(message)
    DLOG("showOverlay %s, overlay %d", MODEL->screenName(overlayId).toStdString().data(), layer);

    QObject *container = nullptr;
    //hideOverlay();
    if(layer == Z_QUICKNOTES) {
        container = m_quicknotesContainer;
    } else {
        container = m_overlayContainer;
    }

    if(layer > Z_BACKGROUND)
        container->setProperty("z", QVariant::fromValue(layer));

    container->setProperty("source", QVariant::fromValue(screenList.value(overlayId)));
    QObject *overlay = qvariant_cast<QObject*>(container->property("item"));

    if(overlay->property("hideTimeout").isValid())
        overlay->setProperty("hideTimeout", QVariant::fromValue(timeout));
    if(overlay->property("message").isValid() && !message.isEmpty())
        overlay->setProperty("message", QVariant::fromValue(message));
    m_overlayId = overlayId;
}

void Window::hideOverlay(int layer)
{
    DLOG("hideOverlay %d", layer);
    if(layer == Z_QUICKNOTES) {
        m_quicknotesContainer->setProperty("source", "");
    }
    else {
        if(m_keyboardAdapter->isKeyboardShow()) {
            m_keyboardAdapter->hideKeyboard();
        }
        m_overlayContainer->setProperty("source", "");
    }
}

void Window::screenShot()
{
    QQuickWindow *_rootObject = qobject_cast<QQuickWindow *>(m_qmlAppEngine.rootObjects().at(0));
    if (_rootObject) {
        QImage _image = _rootObject->grabWindow();
        QString savePath;
#ifdef __WIN32
        savePath = "C://KTTVAuto/ScreenShot/";
#elif __linux__
        savePath = "/user/KTTVAuto/ScreenShot/";
#else
        savePath = "";
#endif
        QFile _file(savePath + "KTTVAuto_Screenshot" + QDateTime::currentDateTime().toString("_yyyy_MM_dd_HH_mm_ss_zzz") + ".png");
        _file.open(QIODevice::WriteOnly);
        if (_file.isOpen()) {
            _image.save(&_file, "PNG");
        }
        showOverlay(QN_COMMON, 1000, Z_QUICKNOTES, "Save Screenshot at\n" + savePath);
    }
}

void Window::showTopbar(bool isShow)
{
    if(!isShowTopbar() && isShow) {
        m_topbarContainer->setProperty("source", QVariant::fromValue(screenList.value(PRT_TOPBAR)));
    }
    else if(isShowTopbar() && !isShow)
        m_topbarContainer->setProperty("source", "");
}

bool Window::isShowTopbar()
{
    return m_topbarContainer && !m_topbarContainer->property("source").toString().isEmpty();
}

void Window::showStatusbar(bool isShow)
{
    if(!isShowStatusbar() && isShow)
        m_statusbarContainer->setProperty("source",  QVariant::fromValue(screenList.value(PRT_STATUSBAR)));
    else if(isShowStatusbar() && !isShow)
        m_statusbarContainer->setProperty("source", "");
}

bool Window::isShowStatusbar()
{
    return m_statusbarContainer && !m_statusbarContainer->property("source").toString().isEmpty();
}

void Window::hmiHandle(QString objectName, int eventId, QString param)
{
//    if(eventId > HMIEvents::DB_HANDLE_START)
//        return;

    DLOG("Request %s - %s", MODEL->eventName(eventId).toStdString().data(), param.toStdString().data());
    switch (eventId) {
    case HMIEvents::HMI_BUTTON_HOME: {
        displayScreen(SCR_HOME);
        break;
    }

    case HMIEvents::HMI_BUTTON_BACK: {
        displayScreen(HISTORY_LATEST_SCREEN);
        break;
    }

    case HMIEvents::HMI_HOME_WORK_MAIN: {
        if(MODEL->isLogin()) {
            if(MODEL->deviceType() == TYPE_KHITUONG) {
                displayScreen(SCR_WORK_SIMPLE);
            } else if(MODEL->deviceType() == TYPE_THUYVAN) {
                displayScreen(SCR_WORK_THUYVAN);
            } else if(MODEL->deviceType() == TYPE_HAIVAN) {
                displayScreen(SCR_WORK_HAIVAN);
            }

        } else {
            showOverlay(POPUP_REQUEST_LOGIN, 0, Z_OVERLAY);
            UIBRIDGE->setDelayEvent(objectName, eventId, param);
        }

        break;
    }

    case HMIEvents::HMI_HOME_SETTING: {
        displayScreen(SCR_SETTINGS_OVERVIEW);
        break;
    }

    case HMIEvents::HMI_HOME_DATAVIEW: {
        displayScreen(SCR_DATAVIEW);
        break;
    }

    case HMIEvents::HMI_TAB_SELECT: {
        if(param == "overview" || param.isEmpty()) {
            displayScreen(SCR_SETTINGS_OVERVIEW);
        } else if(param == "devices") {
            displayScreen(SCR_SETTINGS_DEVICES);
        } else if(param == "users") {
            displayScreen(SCR_SETTINGS_USER);
        } else if(param == "sensor") {
            displayScreen(SCR_SETTINGS_SENSOR);
        } else if(param == "telemetry") {
            displayScreen(SCR_SETTINGS_TELEMETRY);
        } else if(param == "position") {
            displayScreen(SCR_SETTINGS_POSITION);
        } else if(param == "electrical") {
            displayScreen(SCR_SETTINGS_ELECTRICAL_CODES);
        } else if(param == "data") {
            displayScreen(SCR_SETTINGS_DATA);
        } else if(param == "alert") {
            displayScreen(SCR_SETTINGS_ALERT);
        }
        break;
    }

    case HMIEvents::HMI_TEXTINPUT_FOCUS_CHANGED: {
        int keyMode = param.toInt();
        if(m_keyboardAdapter) {
            m_keyboardAdapter->setCurrentTextInput(m_qmlAppEngine.rootObjects().at(0)->findChild<QObject*>(objectName));
            showKeyboard(keyMode);
        }
        break;
    }

    case HMIEvents::HMI_REQUEST_SHOW_COMMON_QN: {
        QStringList paramList = getListParam(param);
        DLOG_THREAD << paramList;
        showOverlay(QN_COMMON, paramList.at(0).toUInt(), Z_QUICKNOTES, paramList.at(1));
        break;
    }

    case HMIEvents::HMI_REQUEST_HIDE_POPUP: {
        hideOverlay(param.toInt());
        break;
    }

    case HMIEvents::HMI_REQUEST_HIDE_QN: {
        hideOverlay(Z_QUICKNOTES);
        break;
    }

    case HMIEvents::HMI_BUTTON_DEVELOPER_SAVE_SCREENSHOT: {
        screenShot();
        break;
    }

    case HMIEvents::HMI_REQUEST_SHOW_LOGIN: {
        if(!MODEL->isLogin()) {
            showOverlay(POPUP_LOGIN, 0, Z_LOGIN);
        } else {
            showOverlay(POPUP_LOGOUT, 3000, Z_OVERLAY);
        }
        break;
    }

    case HMIEvents::HMI_BUTTON_REQUEST_LOGIN_TO_CONTINUE: {
        showOverlay(POPUP_LOGIN, 0, Z_LOGIN);
        break;
    }

    case HMIEvents::DB_RESPONSE_LOGIN_FINISHED: {
        bool isSuccessful = param.toInt() != 0;
        if(isSuccessful) {
            hideOverlay(Z_LOGIN);

            /* emit delay event if having a request delayed */
            if(m_screenAdapter->getCurrentScreen() == SCR_HOME) {
                UIBRIDGE->emitDelayEvent();
            } else {
                UIBRIDGE->resetDelayEvent();
            }
        }
        break;
    }

    case HMIEvents::HMI_REQUEST_ADD_DELAY_EVENT: {
        break;
    }

    case HMIEvents::HMI_RESPONSE_LOAD_SETTINGS_INI_FINISHED: {
        DLOG("Load settings ini finished, model starting");
        m_modelHandler->start();
        break;
    }

    case HMIEvents::HMI_BUTTON_WORK_SWITCH_MODE: {
        if (MODEL->currentScreenId() == SCR_WORK_MAIN) {
            displayScreen(SCR_WORK_SIMPLE);
        } else if (MODEL->currentScreenId() == SCR_WORK_SIMPLE) {
            displayScreen(SCR_WORK_MAIN);
        }
        break;
    }

    case HMIEvents::HMI_REQUEST_SHOW_DELETE_ACCOUNT_CONFIRM_POPUP: {
        showOverlay(POPUP_REQUEST_DELETE_ACCOUNT, 0, Z_LOGIN, param);
        break;
    }

    case HMIEvents::HMI_REQUEST_SHOW_CHANGE_PASSWORD_POPUP: {
        showOverlay(POPUP_CHANGE_PASSWORD, 0, Z_LOGIN);
        break;
    }
    case HMIEvents::HMI_REQUEST_SHOW_CREATE_ACCOUNT_POPUP: {
        showOverlay(POPUP_CREATE_ACCOUNT, 0, Z_LOGIN);
        break;
    }

    default:
        break;
    }
}
