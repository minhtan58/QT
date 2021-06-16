#include "GPSHandler.h"

GPSHandler::GPSHandler(QObject *parent)
    : QObject(parent)
{
    m_timerReadData = new QTimer(this);
    connect(m_timerReadData, SIGNAL(timeout()), this, SLOT(readGPS()));
    m_timerReadData->start(100);
    serialPortConfigure();
}

void GPSHandler::readGPS()
{
    //m_serial->waitForReadyRead(200);
    QString receiveMsg;
    if (m_serial->isOpen() && m_serial->isReadable()) {
        receiveMsg = QString(m_serial->readLine());
        if(receiveMsg.startsWith("$GPRMC"))
        {
            DLOG("GPS msg: %s", receiveMsg.toStdString().data());
            analysisRMC(receiveMsg);
        }
    }
}

void GPSHandler::serialPortConfigure()
{
    m_serial = new QSerialPort(this);
    m_serial->setPortName(MODEL->gpsPortName());
    m_serial->setBaudRate(MODEL->gpsBaudrate().isEmpty() ? QSerialPort::Baud9600 : MODEL->gpsBaudrate().toUInt());
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    MODEL->isConnectedGPSSet(m_serial->open(QIODevice::ReadWrite));
    DLOG("%s to Serial Port %s", (MODEL->isConnectedGPS() ? "Connected" : "Can't connect"), m_serial->portName().toStdString().data());
}

void GPSHandler::analysisRMC(QString &msg)
{
    QStringList elements;
    QRegExp rx("(\\,)");
    int listSize;
    elements = msg.split(rx);
    listSize = elements.size();
    if(listSize >= 9) {
        /* Valid message */
        if (elements.at(2) == "A") {
            /* Time */
            if (elements.at(1) != "")
                MODEL->gpsTimeSet(QString("%1:%2:%3 GMT+0")
                                  .arg(elements.at(1).mid(0, 2))
                                  .arg(elements.at(1).mid(2, 2))
                                  .arg(elements.at(1).mid(4, 2)));
            /* Latitude */
            if (elements.at(3) != "")
                MODEL->gpsLatitudeSet(QString("%1 %2")
                                      .arg(convertStdLatitude(elements.at(3)))
                                      .arg(elements.at(4)));

            /* Longitude */
            if (elements.at(5) != "")
                MODEL->gpsLongtitudeSet(QString("%1 %2")
                                        .arg(convertStdLongitude(elements.at(5)))
                                        .arg(elements.at(6)));

            /* Date */
            if (elements.at(9) != "")
                MODEL->gpsDateSet(QString("%1-%2-%3")
                                  .arg(elements.at(9).mid(0, 2))
                                  .arg(elements.at(9).mid(2, 2))
                                  .arg(elements.at(9).mid(4, 2)));
        }
        else if (elements.at(2) == "V"){}   //invalid
        else {}
    }
    else {}
}

QString GPSHandler::convertStdLatitude(const QString &gpsLat)
{
    int first = gpsLat.mid(0, 2).toInt();
    double last = gpsLat.mid(2, 7).toDouble();
    double gmap = first + last/60;
    return QString::number(gmap, 'g', 9);
}

QString GPSHandler::convertStdLongitude(const QString &gpsLng)
{
    int first = gpsLng.mid(0, 3).toInt();
    double last = gpsLng.mid(3, 7).toDouble();;
    double gmap = first + last/60;
    return QString::number(gmap, 'g', 10);
}
