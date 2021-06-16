/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: ScreenAdapter.cpp
    Create: 12
    Author: Vuong Nguyen

 ****************************************************************************/

#include "ScreenAdapter.h"

ScreenAdapter::ScreenAdapter(QQmlApplicationEngine *qmlAppEngine, QObject *parent)
    : QObject(parent)
    , m_qmlAppEngine(qmlAppEngine)
    , m_screenContainer(qmlAppEngine->rootObjects().at(0)->findChild<QQuickItem*>("appContainer"))
    , m_qmlContext(m_qmlAppEngine->rootContext())
    , m_screenId(HISTORY_LATEST_SCREEN)
{
    m_qmlContext->setContextProperty("loginModel", nullptr);
    m_qmlContext->setContextProperty("accountModel", nullptr);
    m_qmlContext->setContextProperty("dataviewModel", nullptr);
    connect(UIBRIDGE, SIGNAL(hmiEvent(QString,int,QString)), this, SLOT(eventHandler(QString,int,QString)));
}

void ScreenAdapter::createScreen(int screenId)
{
    if(HISTORY_LATEST_SCREEN == screenId) {
//        DLOG("Display history screen");
        m_screenId = historyScreenPopBack();
    } else {
        m_screenId = screenId;
    }

    switch (m_screenId) {
    case SCR_SETTINGS_USER:
        break;
    default:
        break;
    }
    if(m_screenContainer && MCR_ISSCREEN(m_screenId)) {
        m_screenContainer->setProperty("source", QVariant::fromValue(screenList.value(m_screenId)));
        m_screenView = qvariant_cast<QObject*>(m_screenContainer->property("item"));
    }

    MODEL->currentScreenIdSet(m_screenId);
}

void ScreenAdapter::showScreen(int screenId)
{
    closeCurrentScreen(screenId);
    createScreen(screenId);
}

void ScreenAdapter::closeCurrentScreen(int screenId)
{
    switch (m_screenId) {
    case SCR_SETTINGS_USER:
        if(m_listLogin) {
            emit m_listLogin->terminateFetchData();
            m_qmlContext->setContextProperty("loginModel", nullptr);
        }
        if(m_listAccount) {
            emit m_listAccount->terminateFetchData();
            m_qmlContext->setContextProperty("accountModel", nullptr);
        }
        if(m_listDataview) {
            emit m_listDataview->terminateFetchData();
            m_qmlContext->setContextProperty("dataviewModel", nullptr);
        }
        break;
    default:
        break;
    }
    if(m_screenContainer && MCR_ISSCREEN(screenId)) {
        m_screenContainer->setProperty("source", "");
        if(HISTORY_LATEST_SCREEN != screenId) {
//            DLOG("Save history screen %d", m_screenId);
            historyScreenPushBack(m_screenId);
        }
    }
}

int ScreenAdapter::getCurrentScreen()
{
    return m_screenId;
}

bool ScreenAdapter::isShowTopbar()
{
    if(m_screenView && !m_screenView->property("isShowTopBar").isValid())
        return true;    //default show top bar
    return m_screenView->property("isShowTopBar").toBool();
}

bool ScreenAdapter::isShowStatusbar()
{
    if(m_screenView && !m_screenView->property("isShowStatusBar").isValid())
        return true;    //default show status bar
    return m_screenView->property("isShowStatusBar").toBool();
}

void ScreenAdapter::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
//    DLOG("Rev request: %d", eventId);
    switch (eventId) {
    case HMIEvents::HMI_REQUEST_GET_LOGIN_HISTORY: {
        QStringList params = getListParam(param);
        if(m_listLogin) {
            m_listLogin->~LoginHistoryListModel();
            m_listLogin = nullptr;
            m_qmlContext->setContextProperty("loginModel", nullptr);
        }
        MODEL->historySearchDateStartSet(params.at(0));
        MODEL->historySearchDateEndSet(params.at(1));

        break;
    }
    case HMIEvents::DB_RESPONSE_GET_LOGIN_HISTORY_FINISHED: {
        m_listLogin = new LoginHistoryListModel(this);
        m_listLogin->fetchData();
        m_qmlContext->setContextProperty("loginModel", m_listLogin);
        break;
    }
    case HMIEvents::HMI_REQUEST_DELETE_LOGIN_LIST: {
        if(m_listLogin) {
            m_qmlContext->setContextProperty("loginModel", nullptr);
        }
        break;
    }
    case HMIEvents::HMI_REQUEST_GET_DATAVIEW_LIST: {
        QStringList params = getListParam(param);
        if(m_listDataview) {
            m_listDataview->~DataviewListModel();
            m_listDataview = nullptr;
            m_qmlContext->setContextProperty("dataviewModel", nullptr);
        }
        MODEL->dataviewSearchDateStartSet(params.at(0));
        MODEL->dataviewSearchDateEndSet(params.at(1));
        break;
    }
    case HMIEvents::DB_RESPONSE_GET_DATAVIEW_LIST_FINISHED: {
        m_listDataview = new DataviewListModel(this);
        m_listDataview->fetchData();
        m_qmlContext->setContextProperty("dataviewModel", m_listDataview);
        break;
    }
    case HMIEvents::HMI_REQUEST_DELETE_DATAVIEW_LIST: {
        if(m_listDataview) {
            m_qmlContext->setContextProperty("dataviewModel", nullptr);
        }
        break;
    }
    case HMIEvents::HMI_REQUEST_GET_ACCOUNT_LIST: {
        if(m_listAccount) {
            m_listAccount->~AccountListModel();
            m_listAccount = nullptr;
            m_qmlContext->setContextProperty("accountModel", nullptr);
        }
        break;
    }
    case HMIEvents::DB_RESPONSE_GET_ACCOUNT_LIST_FINISHED: {
        m_listAccount = new AccountListModel(this);
        m_listAccount->fetchData();
        m_qmlContext->setContextProperty("accountModel", m_listAccount);
        break;
    }
    case HMIEvents::HMI_REQUEST_DELETE_ACCOUNT_LIST: {
        if(m_listAccount) {
            m_qmlContext->setContextProperty("accountModel", nullptr);
        }
    }
    default:
        break;
    }
}

void ScreenAdapter::historyScreenPushBack(int screenId)
{
    if(m_historyScreen.size() == MAX_SCREEN_HISTORY_LIST) {
        m_historyScreen.erase(m_historyScreen.begin());
    }
    m_historyScreen.push_back(screenId);
}

int ScreenAdapter::historyScreenPopBack()
{
    int latestScreen = SCR_HOME;
    if(m_historyScreen.size() > 0) {
        latestScreen = m_historyScreen[m_historyScreen.size() - 1];
        m_historyScreen.pop_back();
    }
//    DLOG("historyScreenPopBack = %d", latestScreen);
    return latestScreen;
}
