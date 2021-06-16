/****************************************************************************

    Copyright (C) 2018 by LGE
    File: QQuickImage.h
    Create: 28
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef QQUICKIMAGE_H
#define QQUICKIMAGE_H

#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QImage>

class QQuickImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)

public:
    QQuickImage();

    QImage image() const;
    void setImage(const QImage &image);
    void paint(QPainter *painter);

signals:
    void imageChanged();

private:
    QImage m_image;
};

#endif // QQUICKIMAGE_H
