#include "CEMSSimulator.h"
#include "iostream"

CEMSSimulator::CEMSSimulator(QObject *parent)
    : QObject(parent)
    , m_componentO2("11.61")
    , m_componentCO("228.98")
    , m_componentNO("440.64")
    , m_componentSO2("817.37")
    , m_componentTEMP("122.88")
    , m_componentOPP("4.65")
    , m_componentVEL("1.2")
    , m_isFixed(true)
    , m_isConnected(false)
{
    m_serial = new QSerialPort(parent);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    QObject::connect(m_serial, SIGNAL(readyRead()), this, SLOT(sltReadData()), Qt::UniqueConnection);

    connectSerialPort("COM1", 115200);
}

CEMSSimulator::~CEMSSimulator()
{}

void CEMSSimulator::connectSerialPort(QString portname, int baudrate)
{
    qDebug() << "connectSerialPort " << portname << " - " << baudrate;
    if(isConnected()) {
        m_serial->close();
        setIsConnected(false);
    }
    else {
        if(m_serial->isOpen()) {
            if(m_serial->portName() != portname || m_serial->baudRate() != baudrate) {
                m_serial->close();
                setIsConnected(false);
            }
        }
        m_serial->setPortName(portname);
        m_serial->setBaudRate(baudrate);
        setIsConnected(m_serial->open(QIODevice::ReadWrite));
    }
}

double CEMSSimulator::fRandoom(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void CEMSSimulator::sltReadData()
{
    QByteArray msg= m_serial->readAll();
    m_serial->flush();

    QString sendValue(">+%1\r");
    if(!isFixed()) {

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
            qDebug() << send;
            step = 0;
        }
    }
    else {
        if (msg == "#010\r") {
            double value = componentO2().toDouble() / HS_O2;
            m_serial->write(sendValue.arg(value).toUtf8());
        }
        else if (msg == "#011\r") {
            double std = componentCO().toDouble();
            double ppm = std / HS_PPM_2_STD_CO;
            double delta = ppm / HS_AMP_2_PPM_CO;
            double amp = delta + 3.997;
            m_serial->write(sendValue.arg(amp).toUtf8());
        }
        else if (msg == "#012\r") {
            double std = componentSO2().toDouble();
            double ppm = std / HS_PPM_2_STD_SO2;
            double delta = ppm / HS_AMP_2_PPM_SO2;
            double amp = delta + 3.997;
            m_serial->write(sendValue.arg(amp).toUtf8());
        }
        else if (msg == "#013\r") {
            double std = componentNO().toDouble();
            double ppm = std / HS_PPM_2_STD_NO;
            double delta = ppm / HS_AMP_2_PPM_NO;
            double amp = delta + 3.997;
            m_serial->write(sendValue.arg(amp).toUtf8());
        }
        else if (msg == "#014\r") {
            double std = componentTEMP().toDouble();
            double delta = std / HS_TEMP;
            double amp = delta + 4.001;
            m_serial->write(sendValue.arg(amp).toUtf8());
        }
        else if (msg == "#015\r") {
            double std = componentVEL().toDouble();
            double delta = std / HS_VEL;
            double amp = delta + 4.087;
            m_serial->write(sendValue.arg(amp).toUtf8());
        }
        else if (msg == "#016\r") {
            double std = componentOPP().toDouble();
            double delta = std / HS_OPP;
            double amp = delta + 4.001;
            m_serial->write(sendValue.arg(amp).toUtf8());
        }
        else if (msg == "#017\r") {
            m_serial->write(sendValue.arg(0).toUtf8());
        }
    }

}

bool CEMSSimulator::isConnected() const
{
    return m_isConnected;
}

void CEMSSimulator::setIsConnected(bool isConnected)
{
    if(isConnected != m_isConnected) {
        m_isConnected = isConnected;
        emit isConnectedChanged();
    }
}

bool CEMSSimulator::isFixed() const
{
    return m_isFixed;
}

void CEMSSimulator::setIsFixed(bool isFixed)
{
    if(isFixed != m_isFixed) {
        m_isFixed = isFixed;
        emit isFixedChanged();
    }
}

QString CEMSSimulator::componentVEL() const
{
    return m_componentVEL;
}

void CEMSSimulator::setComponentVEL(const QString &componentVEL)
{
    if(componentVEL != m_componentVEL) {
        m_componentVEL = componentVEL;
        emit componentVELChanged();
    }
}

QString CEMSSimulator::componentOPP() const
{
    return m_componentOPP;
}

void CEMSSimulator::setComponentOPP(const QString &componentOPP)
{
    if(componentOPP != m_componentOPP) {
        m_componentOPP = componentOPP;
        emit componentOPPChanged();
    }
}

QString CEMSSimulator::componentTEMP() const
{
    return m_componentTEMP;
}

void CEMSSimulator::setComponentTEMP(const QString &componentTEMP)
{
    if(componentTEMP != m_componentTEMP) {
        m_componentTEMP = componentTEMP;
        emit componentTEMPChanged();
    }
}

QString CEMSSimulator::componentSO2() const
{
    return m_componentSO2;
}

void CEMSSimulator::setComponentSO2(const QString &componentSO2)
{
    if(componentSO2 != m_componentSO2) {
        m_componentSO2 = componentSO2;
        emit componentSO2Changed();
    }
}

QString CEMSSimulator::componentNO() const
{
    return m_componentNO;
}

void CEMSSimulator::setComponentNO(const QString &componentNO)
{
    if(componentNO != m_componentNO) {
        m_componentNO = componentNO;
        emit componentNOChanged();
    }
}

QString CEMSSimulator::componentCO() const
{
    return m_componentCO;
}

void CEMSSimulator::setComponentCO(const QString &componentCO)
{
    if(componentCO != m_componentCO) {
       m_componentCO = componentCO;
       emit componentCOChanged();
    }
}

QString CEMSSimulator::componentO2() const
{
    return m_componentO2;
}

void CEMSSimulator::setComponentO2(const QString &componentO2)
{
    if(componentO2 != m_componentO2) {
       m_componentO2 = componentO2;
       emit componentO2Changed();
    }
}
