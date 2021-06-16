/****************************************************************************

    Copyright (C) 2018 by King Kong JSC
    File: Window.h
    Create: 28
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ScreenAdapter.h"
#include "ModelHandler.h"
#include "SettingsLoader.h"
#include "DataManager.h"

class Window : public QObject
{
    Q_OBJECT
public:
    explicit Window(QObject *parent = nullptr);
    void show();

signals:

public slots:

private:
    QQmlApplicationEngine m_qmlEngine;
    ScreenAdapter *m_screenAdapter = nullptr;
    ModelHandler *m_modelHandler = nullptr;

    void initWindow();
    void displayScreen(int screenId);
    void displayOverlay(int overlayId, int z, int timeout = 3000);
    void hideOverlay(int overlayId);
    void loadIniSettings();
};

#endif // WINDOW_H
