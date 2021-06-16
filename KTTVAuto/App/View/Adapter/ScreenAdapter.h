/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: ScreenAdapter.h
    Create: 12
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef SCREENADAPTER_H
#define SCREENADAPTER_H

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ScreenList.h"
#include "LoginHistoryListModel.h"
#include "AccountListModel.h"
#include "DataviewListModel.h"
#include "Common.h"

#define MAX_SCREEN_HISTORY_LIST 10
#define HISTORY_LATEST_SCREEN   -1

class ScreenAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ScreenAdapter(QQmlApplicationEngine *qmlAppEngine, QObject *parent = nullptr);

    void createScreen(int screenId);
    void showScreen(int screenId);
    void closeCurrentScreen(int screenId);
    int getCurrentScreen();
    bool isShowTopbar();
    bool isShowStatusbar();

signals:

public slots:
    void eventHandler(QString objectName, int eventId, QString param);

private:
    int m_screenId;
    QQmlApplicationEngine *m_qmlAppEngine = nullptr;
    QQmlContext *m_qmlContext = nullptr;
    QObject *m_screenContainer = nullptr;
    QObject *m_screenView = nullptr;
    std::vector<int> m_historyScreen;
    LoginHistoryListModel *m_listLogin = nullptr;
    AccountListModel *m_listAccount = nullptr;
    DataviewListModel *m_listDataview = nullptr;

    void historyScreenPushBack(int screenId);
    int historyScreenPopBack();

    int m_previousScreen = -1;
};

#endif // SCREENADAPTER_H
