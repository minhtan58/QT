#ifndef DCONSIMULATOR_H
#define DCONSIMULATOR_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QtSerialPort/QSerialPort>

#define MCR_FRAND(FMIN, FMAX) (FMIN + (double)rand() / RAND_MAX * (FMAX - FMIN))
#define MCR_STR_BUILDER QString(">+%1\r").arg(MCR_FRAND(4., 20.)).toUtf8()

class DConSimulator : public QObject
{
    Q_OBJECT
public:
    explicit DConSimulator(QObject *parent = nullptr);
    ~DConSimulator();

    double fRandoom(double fMin, double fMax);

public slots:
    void sltReadData();

private:
    QSerialPort *m_serial;
};

#endif // DCONSIMULATOR_H
