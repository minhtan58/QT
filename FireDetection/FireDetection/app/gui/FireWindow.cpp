/****************************************************************************

    Copyright (C) 2018 by LGE
    File: FireWindow.cpp
    Create: 12
    Author: Vuong Nguyen

 ****************************************************************************/

#include "FireWindow.h"

FireWindow::FireWindow(QObject *parent)
    : QObject(parent)
{
//    m_detectionEngine.setSourceImage("../FireDetection/resource/image/sample.png");
    m_detectionEngine.setSourceImage("../FireDetection/resource/image/firesmall.jpg");
    m_image = cvMat2QImage(m_detectionEngine.process(3));
    initWindow();
}

void FireWindow::initWindow()
{
    qmlRegisterType<CommonImage>("CommonImage", 1, 0, "CommonImage");
    m_qmlEngine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    m_qmlImage = m_qmlEngine.rootObjects().at(0)->findChild<QObject*>("imgDetect");

    m_qmlImage->setProperty("image", m_image);
}

QImage FireWindow::cvMat2QImage(const Mat &src)
{
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

    const double scale = 255.0;

    if (src.depth() == CV_8U) {
        if (src.channels() == 1) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    int level = src.at<quint8>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        } else if (src.channels() == 3) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    Vec3b bgr = src.at<Vec3b>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    } else if (src.depth() == CV_32F) {
        if (src.channels() == 1) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    int level = scale * src.at<double>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        } else if (src.channels() == 3) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    Vec3f bgr = scale * src.at<Vec3f>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    }

    return dest;
}
