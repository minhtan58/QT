#include "DConSimulator.h"
#include "iostream"

DConSimulator::DConSimulator(QObject *parent)
{
    m_serial = new QSerialPort(parent);
    m_serial->setPortName("COM1");
    m_serial->setBaudRate(115200);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    if(m_serial->open(QIODevice::ReadWrite)) {
        std::cout << "Conneted COM1" << std::endl;
        QObject::connect(m_serial, SIGNAL(readyRead()), this, SLOT(sltReadData()), Qt::UniqueConnection);
    }
    else {
        std::cout << "Can't Connet COM1" << std::endl;
    }
}

DConSimulator::~DConSimulator()
{}

double DConSimulator::fRandoom(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void DConSimulator::sltReadData()
{
    QByteArray msg= m_serial->readAll();
//    qDebug() << "Rev msg: " << msg;
    m_serial->flush();
    QString sendValue(">+%1\r");
    static double chanel[8];
    static int step = 0;

    if(step == 0)
        for(int i = 0; i < 8; i++)
            chanel[i] = fRandoom(4., 20.);

    if (msg == "#010\r") {
        m_serial->write(sendValue.arg(chanel[step++]).toUtf8());
    }
    else if (msg == "#011\r") {
        m_serial->write(sendValue.arg(chanel[step++]).toUtf8());
    }
    else if (msg == "#012\r") {
        m_serial->write(sendValue.arg(chanel[step++]).toUtf8());
    }
    else if (msg == "#013\r") {
        m_serial->write(sendValue.arg(chanel[step++]).toUtf8());
    }
    else if (msg == "#014\r") {
        m_serial->write(sendValue.arg(chanel[step++]).toUtf8());
    }
    else if (msg == "#015\r") {
        m_serial->write(sendValue.arg(chanel[step++]).toUtf8());
    }
    else if (msg == "#016\r") {
        m_serial->write(sendValue.arg(chanel[step++]).toUtf8());
    }
    else if (msg == "#017\r") {
        m_serial->write(sendValue.arg(chanel[step++]).toUtf8());
    }

    if(step == 8) {
        QString send("Sent data: \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\"");
        for(int i = 0; i < 8; i++) {
            send = send.arg(chanel[i]);
        }
        std::cout << send.toStdString() << std::endl;
        step = 0;
    }
}
