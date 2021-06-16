/****************************************************************************

    Copyright (C) 2018 by LGE
    File: QQuickImage.cpp
    Create: 28
    Author: Vuong Nguyen

 ****************************************************************************/

#include "QQuickImage.h"

QQuickImage::QQuickImage()
{}

QImage QQuickImage::image() const
{
    return m_image;
}

void QQuickImage::setImage(const QImage &image)
{
    m_image = image;
    update();
}

void QQuickImage::paint(QPainter *painter)
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
