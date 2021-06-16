#ifndef CEMSSIMULATOR_H
#define CEMSSIMULATOR_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QtSerialPort/QSerialPort>

#define MCR_FRAND(FMIN, FMAX) (FMIN + (double)rand() / RAND_MAX * (FMAX - FMIN))
#define MCR_STR_BUILDER QString(">+%1\r").arg(MCR_FRAND(4., 20.)).toUtf8()

#define HS_O2       0.75
#define HS_TEMP     9.340
#define HS_OPP      6.278
#define HS_DUST_PM  154.523
#define HS_VEL      6.373

#define HS_AMP_2_PPM_CO     142.857
#define HS_AMP_2_PPM_NO     81.235
#define HS_AMP_2_PPM_NOX
#define HS_AMP_2_PPM_SO2    49.804

#define HS_PPM_2_STD_CO       1.14
#define HS_PPM_2_STD_NO       1.23
#define HS_PPM_2_STD_NO2      1.88
#define HS_PPM_2_STD_NOX      1.88
#define HS_PPM_2_STD_SO2      2.62

class CEMSSimulator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString componentO2      READ componentO2        WRITE setComponentO2        NOTIFY componentO2Changed)
    Q_PROPERTY(QString componentCO      READ componentCO        WRITE setComponentCO        NOTIFY componentCOChanged)
    Q_PROPERTY(QString componentNO      READ componentNO        WRITE setComponentNO        NOTIFY componentNOChanged)
    Q_PROPERTY(QString componentSO2     READ componentSO2       WRITE setComponentSO2       NOTIFY componentSO2Changed)
    Q_PROPERTY(QString componentTEMP    READ componentTEMP      WRITE setComponentTEMP      NOTIFY componentTEMPChanged)
    Q_PROPERTY(QString componentOPP     READ componentOPP       WRITE setComponentOPP       NOTIFY componentOPPChanged)
    Q_PROPERTY(QString componentVEL     READ componentVEL       WRITE setComponentVEL       NOTIFY componentVELChanged)
    Q_PROPERTY(bool    isFixed          READ isFixed            WRITE setIsFixed            NOTIFY isFixedChanged)
    Q_PROPERTY(bool    isConnected      READ isConnected        WRITE setIsConnected        NOTIFY isConnectedChanged)

public:
    explicit CEMSSimulator(QObject *parent = nullptr);
    ~CEMSSimulator();

    Q_INVOKABLE void connectSerialPort(QString portname, int baudrate);

    double fRandoom(double fMin, double fMax);

    QString componentO2() const;
    void setComponentO2(const QString &componentO2);

    QString componentCO() const;
    void setComponentCO(const QString &componentCO);

    QString componentNO() const;
    void setComponentNO(const QString &componentNO);

    QString componentSO2() const;
    void setComponentSO2(const QString &componentSO2);

    QString componentTEMP() const;
    void setComponentTEMP(const QString &componentTEMP);

    QString componentOPP() const;
    void setComponentOPP(const QString &componentOPP);

    QString componentVEL() const;
    void setComponentVEL(const QString &componentVEL);

    bool isFixed() const;
    void setIsFixed(bool isFixed);

    bool isConnected() const;
    void setIsConnected(bool isConnected);

public slots:
    void sltReadData();

signals:
    void componentO2Changed();
    void componentCOChanged();
    void componentNOChanged();
    void componentSO2Changed();
    void componentTEMPChanged();
    void componentOPPChanged();
    void componentVELChanged();
    void isFixedChanged();
    void isConnectedChanged();

private:
    QSerialPort *m_serial;

    QString m_componentO2;
    QString m_componentCO;
    QString m_componentNO;
    QString m_componentSO2;
    QString m_componentTEMP;
    QString m_componentOPP;
    QString m_componentVEL;

    bool m_isFixed;
    bool m_isConnected;
};

#endif // CEMSSIMULATOR_H
