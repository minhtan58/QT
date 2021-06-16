/****************************************************************************

    Copyright (C) 2018 by LGE
    File: StatusBarAdapter.h
    Create: 21
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef STATUSBARADAPTER_H
#define STATUSBARADAPTER_H

#include <QObject>
#include <QQuickItem>

#include "common.h"

class StatusBarAdapter : public QObject
{
    Q_OBJECT
public:
    explicit StatusBarAdapter(QQuickItem *container, QObject *parent = nullptr);
    void initAppData();

public slots:
    void updateAppData(int dpid);

private:
    QQuickItem *m_statusBarContainer = nullptr;
    QObject *m_statusBarView = nullptr;
};

#endif // STATUSBARADAPTER_H
