/****************************************************************************

    Copyright (C) 2018 by LGE
    File: QImage.h
    Create: 12
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef QIMAGE_H
#define QIMAGE_H

#include <QObject>

class QImage : public QObject
{
    Q_OBJECT
public:
    explicit QImage(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QIMAGE_H