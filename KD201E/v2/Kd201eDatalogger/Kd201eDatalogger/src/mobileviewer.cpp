#include "mobileviewer.h"

MobileViewer::MobileViewer(QObject *parent) : QObject(parent)
{
    m_server = new QTcpServer(parent);
}

MobileViewer::~MobileViewer()
{
    delete m_server;
}

void MobileViewer::start()
{
    if (m_server != nullptr) {
        QObject::connect(m_server, SIGNAL(newConnection()), this, SLOT(slt_connectionHandler()), Qt::UniqueConnection);
        if (m_server->isListening())
            return;

        if(m_server->listen(QHostAddress::Any, MOBILE_PORT))
            DLG << "Server started";
        else
            DLG << "Server can't start";
    }
}

void MobileViewer::slt_connectionHandler()
{
    QTcpSocket *qSocket = m_server->nextPendingConnection();
    QObject::connect(qSocket, SIGNAL(disconnected()), this, SLOT(slt_clientDisconnected()));
    QObject::connect(qSocket, SIGNAL(readyRead()), this, SLOT(slt_readMobileRequest()));
    m_clientList.push_back(qSocket);
    DLG << "Total Client connected is " << m_clientList.size();
}

void MobileViewer::slt_clientDisconnected()
{
    QTcpSocket *pSocket = qobject_cast<QTcpSocket*>(QObject::sender());
    if(m_clientList.size() > 0) {
        int index = m_clientList.indexOf(pSocket);
        if(index >= 0 && index < m_clientList.size()) {
            m_clientList.removeAt(index);
            DLG << "remove client " << index << ", total client connected is " << m_clientList.size();
        }
    }
    pSocket->deleteLater();
}

void MobileViewer::slt_readMobileRequest()
{
    QTcpSocket *pSocket = qobject_cast<QTcpSocket*>(QObject::sender());
    QString request = pSocket->readAll();
    DLG << "Client " << QString::number(pSocket->peerAddress().toIPv4Address()) << " send: " << request;

    if(request.contains(MSG_UPDATE_STATUS)) {
        QString response = QString("msg_update,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16")
                .arg(QString::fromStdString(kd201eSetting.m_stationName))   //1
                .arg(QString::fromStdString(kd201eSetting.m_stationID))     //2
                .arg(QString::fromStdString(kd201eVariant.m_controller))    //3
                .arg(QString::fromStdString(kd201eVariant.m_serial))        //4
                .arg(QString::fromStdString(kd201eVariant.m_software))      //5
                .arg(QString::fromStdString(kd201eVariant.m_time))          //6
                .arg(QString::fromStdString(kd201eVariant.m_id01Val1))      //7
                .arg(QString::fromStdString(kd201eVariant.m_id01Val2))      //8
                .arg(QString::fromStdString(kd201eVariant.m_id02Val1))      //9
                .arg(QString::fromStdString(kd201eVariant.m_id02Val2))      //10
                .arg(QString::fromStdString(kd201eVariant.m_id03Val1))      //11
                .arg(QString::fromStdString(kd201eVariant.m_id03Val2))      //12
                .arg(QString::fromStdString(kd201eVariant.m_id04Val1))      //13
                .arg(QString::fromStdString(kd201eVariant.m_id04Val2))      //14
                .arg((kd201eCommon.m_isStationConnected ? "Connected" : "Disconnected"))    //15
                .arg((kd201eCommon.m_isFtpConnected ? "Connected" : "Disconnected"));       //16
        pSocket->flush();
        pSocket->write(QByteArray::fromStdString(response.toStdString()));
    }
    else{
        DLG << "Client " << QString::number(pSocket->peerAddress().toIPv4Address()) << " send: " << request;
    }
//    pSocket->deleteLater();
}

