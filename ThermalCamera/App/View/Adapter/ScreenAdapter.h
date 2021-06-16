/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: ScreenAdapter.h
    Create: 23/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef SCREENADAPTER_H
#define SCREENADAPTER_H

#include "Common.h"
#include "DataManager.h"
#include <QQuickItem>
#include <QQmlProperty>
#include <QQmlContext>
#include <QImage>

class ScreenAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ScreenAdapter(QObject *appContainer, QObject *parent = nullptr);
    ~ScreenAdapter();
    void createScreen(int screenId);
    int currentScreenId();
    void initAppData();

public slots:
    void updateAppData(int dpid, QString value);
    void updateData(int eventId, void *data);

private:
    int m_screenId;
    QObject *m_appContainer = nullptr;
    QObject *m_screenView = nullptr;
};

#endif // SCREENADAPTER_H
