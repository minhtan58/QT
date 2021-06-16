/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: ScreenAdapter.h
    Create: 23/12/2017
    Author: Minh Tan

 ****************************************************************************/

#ifndef SCREENADAPTER_H
#define SCREENADAPTER_H

#include "Common.h"
#include "DataManager.h"
#include <QQuickItem>
#include <QQmlProperty>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "QMLModel/HistoryDataListModel.h"

class ScreenAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ScreenAdapter(QQmlApplicationEngine *qmlAppEngine, QObject *parent = nullptr);
    ~ScreenAdapter();
    void createScreen();
    int getCurrentScreen();
    void initAppData();
    void setScreenId(int screenId);

public slots:
    void updateAppData(int dpid);
    void eventHandler(QString objectName, int eventId, QString param);

private:
    int m_screenId;
    QQmlApplicationEngine *m_qmlAppEngine = nullptr;
    QQuickItem* m_appContainer = nullptr;
    QObject* m_screenView = nullptr;

    HistoryDataListModel *m_listHistory = nullptr;

    QString createIntervalDisplay(int msec);
};

#endif // SCREENADAPTER_H
