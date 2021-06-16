/****************************************************************************

    Copyright (C) 2018 by LGE
    File: CommonImage.h
    Create: 12
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef COMMONIMAGE_H
#define COMMONIMAGE_H

#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QImage>

class CommonImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
public:
    explicit CommonImage(QQuickItem *parent = nullptr);

    Q_INVOKABLE void setImage(const QImage &image);
    void paint(QPainter *painter);
    QImage image() const;

signals:
    void imageChanged();

private:
    QImage m_image;
};

#endif // COMMONIMAGE_H
