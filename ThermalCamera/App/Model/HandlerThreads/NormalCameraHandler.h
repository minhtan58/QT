#ifndef NORMALCAMERAHANDLER_H
#define NORMALCAMERAHANDLER_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTimer>

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkReply>

#include "Delivery.h"
#include "Common.h"
#include "DataManager.h"

#include <QTimer>
#include <QThread>
#include <QImage>
#include "Defines.h"

class NormalCameraHandler : public QObject
{
    Q_OBJECT
public:
    explicit NormalCameraHandler(QObject *parent = nullptr);
    void readScheduce();

public slots:
    void resetCamera();
    void readFrame();

    void finishedSlot(QNetworkReply *reply);
private:
    void initNormalModule();

    QNetworkAccessManager *m_nam = nullptr;
    QNetworkReply *m_reply = nullptr;
    QUrl *m_url = nullptr;
    QImage *m_normalImage = nullptr;
};

//thread define
class NormalCameraHandlerThread : public QThread
{
    Q_OBJECT
public:
    NormalCameraHandlerThread(QObject *parent = nullptr)
        : QThread(parent)
    {}

protected:
    void run() {
        DLOG("Start");
        NormalCameraHandler handler;
        forever {
            handler.readScheduce();
        }
        exec();
    }
};

#endif // NORMALCAMERAHANDLER_H
