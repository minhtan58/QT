/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: CEMSDatalogger.h
    Create: 11/12/2017
    Author: Minh Tan

 ****************************************************************************/

#ifndef CEMSDATALOGGER_H
#define CEMSDATALOGGER_H

#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include <QDateTime>

#include "Common.h"
#include "DataManager.h"
#include "UIBridge.h"
#include "ScreenAdapter.h"
#include "QMLConstants.h"
#include "KeyboardAdapter.h"
#include "TopBarAdapter.h"
#include "SettingsLoader.h"
#include "ModelHandler.h"

class CEMSDatalogger : public QObject
{
    Q_OBJECT
public:
    explicit CEMSDatalogger(QObject *parent = nullptr);
    ~CEMSDatalogger();

    void exec();

private:
    QQmlApplicationEngine m_qmlAppEngine;
    QMLConstants m_qmlConstant;
    ScreenAdapter *m_screenAdapter = nullptr;
    KeyboardAdapter *m_keyboardAdapter = nullptr;
    TopBarAdapter *m_topBarAdapter = nullptr;
    ModelHandler *m_modelHandler = nullptr;

    void initDatalogger();

    void showScreen(int screenId);

    void showKeyboard(int mode);
    void hideKeyboard();

    void showOverlay(int overlayId, int timeout, int layer = Z_OVERLAY, QString message = "");
    void hideOverlay();

    void screenShot();

private slots:
    void hmiHandle(QString objectName, int eventId, QString param);

signals:
    void sgnUpdateSerialList();
};

#endif // CEMSDATALOGGER_H
