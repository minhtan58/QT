#include "NormalCameraHandler.h"
#include "HMIEvents.h"

#define MAIN_TEXTURE_WIDTH 512
#define MAIN_TEXTURE_HEIGHT 512

char tmpbuff[MAIN_TEXTURE_WIDTH*MAIN_TEXTURE_HEIGHT*4];


NormalCameraHandler::NormalCameraHandler(QObject *parent)
    : QObject(parent)
{
    m_nam = new QNetworkAccessManager(this);
    connect(m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
    m_url = new QUrl("http://127.0.0.1:9000/?action=stream");
}

void NormalCameraHandler::readScheduce()
{
//    DLOG("Fetch data");
//    m_nam->get(QNetworkRequest(QUrl("http://127.0.0.1:9000/?action=stream")));
    m_nam->get(QNetworkRequest(QUrl("http://192.168.0.234:9000/?action=stream")));

//    m_reply = m_nam->get(QNetworkRequest(m_url));
//    connect(m_reply, SIGNAL(readyRead()), this, SLOT(readFrame()), Qt::UniqueConnection);
}

void NormalCameraHandler::initNormalModule()
{}

void NormalCameraHandler::readFrame()
{}

void NormalCameraHandler::resetCamera()
{}

void NormalCameraHandler::finishedSlot(QNetworkReply *reply)
{
    int bytesAvailable = reply->bytesAvailable();
    DLOG("bytesAvailable: %d", bytesAvailable);
    QByteArray jpegData = reply->readAll();
    m_normalImage->loadFromData(jpegData);
    emit Delivery::getInstance()->dataTransfer(DATA_NORMAL_IMAGE, m_normalImage);
    delete reply;
}
