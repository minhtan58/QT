/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: Window.h
    Create: 11/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef Window_H
#define Window_H

#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include <QDateTime>

#include "Common.h"
#include "AppModel.h"
#include "UIBridge.h"
#include "ScreenAdapter.h"
#include "KeyboardAdapter.h"
#include "SettingsLoader.h"
#include "ModelHandler.h"
#include "DBManager.h"
#include "FontManager.h"

#include "LoginHistoryListModel.h"

class Window : public QObject
{
    Q_OBJECT
public:

    explicit Window(QObject *parent = nullptr);
    ~Window();

    void start();

private:
    QQmlApplicationEngine m_qmlAppEngine;
    ScreenAdapter *m_screenAdapter = nullptr;
    KeyboardAdapter *m_keyboardAdapter = nullptr;
    ModelHandler *m_modelHandler = nullptr;
    QObject *m_topbarContainer = nullptr;
    QObject *m_statusbarContainer = nullptr;
    QObject *m_overlayContainer = nullptr;
    QObject *m_quicknotesContainer = nullptr;

    int m_overlayId;
    QHash<int, int> m_mapListModelScreen;
    QHash<int, int> m_mapListModelSignal;

    void initDatalogger();

    void displayScreen(int screenId);

    void showKeyboard(int mode);
    void hideKeyboard();

    void showOverlay(int overlayId, int timeout, int layer = Z_OVERLAY, QString message = "");
    void hideOverlay(int layer = Z_QUICKNOTES);

    void screenShot();

    void showTopbar(bool isShow);
    bool isShowTopbar();
    void showStatusbar(bool isShow);
    bool isShowStatusbar();

private slots:
    void hmiHandle(QString objectName, int eventId, QString param);

signals:
    void sgnUpdateSerialList();
};

#endif // Window_H
