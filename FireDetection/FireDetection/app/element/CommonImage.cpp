/****************************************************************************

    Copyright (C) 2018 by LGE
    File: CommonImage.cpp
    Create: 12
    Author: Vuong Nguyen

 ****************************************************************************/

#include "CommonImage.h"

CommonImage::CommonImage(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_image = QImage();
}

void CommonImage::setImage(const QImage &image)
{
    m_image = image;
    update();
}

void CommonImage::paint(QPainter *painter)
{
    QRectF bounding_rect = boundingRect();
    QImage scaled = m_image.scaledToHeight(bounding_rect.height());
    QPointF center = bounding_rect.center() - scaled.rect().center();

    if(center.x() < 0)
        center.setX(0);
    if(center.y() < 0)
        center.setY(0);
    painter->drawImage(center, scaled);
}

QImage CommonImage::image() const
{
    return m_image;
}
