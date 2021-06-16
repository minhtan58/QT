/****************************************************************************

    Copyright (C) 2018 by LGE
    File: FireWindow.h
    Create: 12
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef FIREWINDOW_H
#define FIREWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "FireDetection.h"
#include "CommonImage.h"

class FireWindow : public QObject
{
    Q_OBJECT
public:
    explicit FireWindow(QObject *parent = nullptr);
    void initWindow();

signals:

public slots:

private:
    QQmlApplicationEngine m_qmlEngine;
    QObject *m_qmlImage = nullptr;
    QImage m_image;
    FireDetection m_detectionEngine;
    QImage cvMat2QImage(Mat const& src);
};

#endif // FIREWINDOW_H
