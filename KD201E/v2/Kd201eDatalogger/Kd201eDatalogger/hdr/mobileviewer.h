#ifndef MOBILEVIEWER_H
#define MOBILEVIEWER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

#include "common.h"

#define MOBILE_PORT 10101

class MobileViewer : public QObject
{
    Q_OBJECT
private:
    QTcpServer *m_server;
    QVector<QTcpSocket*> m_clientList;

public:
    explicit MobileViewer(QObject *parent = 0);
    ~MobileViewer();
    void start();

signals:

public slots:
    void slt_connectionHandler();
    void slt_clientDisconnected();
    void slt_readMobileRequest();
};

#endif // MOBILEVIEWER_H
