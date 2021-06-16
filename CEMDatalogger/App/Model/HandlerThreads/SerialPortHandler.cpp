/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: SerialPortHandler.cpp
    Create: 12/03/2018
    Author: Minh Tan

 ****************************************************************************/

#include "SerialPortHandler.h"

SerialPortHandler::SerialPortHandler(QObject *parent) : QObject(parent)
{
    //DUMMY
    SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_INTERVAL, QString::number(UPDATE_DATA_INTERVAL));
#ifdef __WIN32
//    SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME, SERIAL_PORT_COM(2));
#elif __linux__
//    SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME, SERIAL_PORT_TTY_USB(0));
#endif
    updateSerialPortList();

    m_dcon = new DConI7017RC();
    connect(m_dcon, SIGNAL(sgnReadComplete()), this, SLOT(sltReadConnect()), Qt::UniqueConnection);
    connect(this, SIGNAL(requestConnectSerialPort()), m_dcon, SLOT(sltConnectSerialPort()), Qt::UniqueConnection);
}

void SerialPortHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case CEMSEnum::HMI_TAB_SELECT: {
        if(param == "serialport") {
            updateSerialPortList();
        }
        break;
    }
    case CEMSEnum::HMI_BUTTON_TEST_CONNECTIONS_SERIALPORT: {
        QStringList paramList = getListParam(param);
        SENDEVENT("" , CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Connecting...");
        SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_TEST_CONNECTION, QString::number(int(TC_TESTING)));
        m_dcon->testConnection(paramList.at(0), paramList.at(1).toInt());
        break;
    }
    default:
        break;
    }
}

void SerialPortHandler::sltReadConnect()
{
    readDConChanel(0, CEMSEnum::DP_AMP_AIR_O2);
    readDConChanel(1, CEMSEnum::DP_AMP_AIR_CO);
    readDConChanel(2, CEMSEnum::DP_AMP_AIR_SO2);
    readDConChanel(3, CEMSEnum::DP_AMP_AIR_NO);
    readDConChanel(4, CEMSEnum::DP_AMP_TEMP);
    readDConChanel(5, CEMSEnum::DP_AMP_VEL);
    readDConChanel(6, CEMSEnum::DP_AMP_OPP);
    //readDConChanel(7, CEMSEnum::DP_AMP_DUST_PM);
}

void SerialPortHandler::updateAppData(int dpid)
{
    switch (dpid) {
    case CEMSEnum::DP_GENERAL_RADIUS: {
        double valueVel = GETDPDATA(CEMSEnum::DP_VEL).toDouble();
        double radius = GETDPDATA(CEMSEnum::DP_GENERAL_RADIUS).toDouble();
        if(radius > 0 && valueVel > 0) {
            double valueFlow = valueVel * 3.14 * radius * radius;
            SETDPDATA(CEMSEnum::DP_FLOW, MCR_DPDATA_DOUBLE_STD(valueFlow, 2));
        } else {
            SETDPDATA(CEMSEnum::DP_FLOW, EMPTY_STR);
        }
        break;
    }
    case CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME:
    case CEMSEnum::DP_SETTINGS_SERIALPORT_BAUDRATE:
        DLOG("Request connect serial port");
        emit requestConnectSerialPort();
        break;
    default:
        break;
    }
}

void SerialPortHandler::updateSerialPortList()
{
    QStringList list;
    foreach (const QSerialPortInfo &serialInfo, QSerialPortInfo::availablePorts()) {
        if(!serialInfo.isBusy())
            list.append(serialInfo.portName());
    }
    if(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS) == "1")
        list.append(GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_PORTNAME));

    qSort(list.begin(), list.end());

    QString listString = "";
    foreach (QString element, list) {
        listString += element + ",";
    }
    listString.remove(listString.length() - 1, 1);

    DLOG("List SerialPort: %s", listString.toStdString().data());

    SETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_LIST_AVAIABLE_PORTNAME, listString);
}

void SerialPortHandler::readDConChanel(int chanel, int ampType)
{
    QString chanelValue = m_dcon->getChanelValue(chanel);
    bool isNumber = false;
    double chanelNumber = chanelValue.toDouble(&isNumber);
    if(!isNumber) {
        DLOG("Read Chanel %f fail, value: %s", chanel, chanelValue.toStdString().data());
        return;
    }

    //update ampere
    SETDPDATA(ampType, chanelValue);

    switch (ampType) {
    case CEMSEnum::DP_AMP_AIR_O2: {
        if(chanelNumber > AMP_MIN) {
            double deltaO2 = 4.001;
            double valueO2 = deltaO2 * HS_O2;
            SETDPDATA(CEMSEnum::DP_AIR_O2, MCR_DPDATA_DOUBLE_STD(valueO2, 2));
        } else {
            SETDPDATA(CEMSEnum::DP_AIR_O2, EMPTY_STR);
        }
        break;
    }

    case CEMSEnum::DP_AMP_AIR_CO: {
        if (chanelNumber > AMP_MIN) {
            double deltaCO = 3.997;
            double valuePpmCO = deltaCO * HS_AMP_2_PPM_CO;
            SETDPDATA(CEMSEnum::DP_PPM_AIR_CO, MCR_DPDATA_DOUBLE_STD(valuePpmCO, 2));

            double valueCO = valuePpmCO * HS_PPM_2_STD_CO;
            SETDPDATA(CEMSEnum::DP_AIR_CO, MCR_DPDATA_DOUBLE_STD(valueCO, 2));
        } else {
            SETDPDATA(CEMSEnum::DP_PPM_AIR_CO, EMPTY_STR);
            SETDPDATA(CEMSEnum::DP_AIR_CO, EMPTY_STR);
        }
        break;
    }

    case CEMSEnum::DP_AMP_AIR_NO: {
        if (chanelNumber > AMP_MIN) {
            double deltaNO = 3.997;
            double valuePpmNO = deltaNO * HS_AMP_2_PPM_NO;
            SETDPDATA(CEMSEnum::DP_PPM_AIR_NO, MCR_DPDATA_DOUBLE_STD(valuePpmNO, 2));

            double valueNO = valuePpmNO * HS_PPM_2_STD_NO;
            SETDPDATA(CEMSEnum::DP_AIR_NO, MCR_DPDATA_DOUBLE_STD(valueNO, 2));

            double valuePpmNOx = valuePpmNO * (46/30.0) / 0.95;
            SETDPDATA(CEMSEnum::DP_PPM_AIR_NOX, MCR_DPDATA_DOUBLE_STD(valuePpmNOx, 2));

            double valueNOx = valueNO * (46/30.0) / 0.95;
            SETDPDATA(CEMSEnum::DP_AIR_NOX, MCR_DPDATA_DOUBLE_STD(valueNOx, 2));
        } else {
            SETDPDATA(CEMSEnum::DP_PPM_AIR_NO, EMPTY_STR);
            SETDPDATA(CEMSEnum::DP_AIR_NO, EMPTY_STR);
            SETDPDATA(CEMSEnum::DP_PPM_AIR_NOX, EMPTY_STR);
            SETDPDATA(CEMSEnum::DP_AIR_NOX, EMPTY_STR);
        }
        break;
    }

    case CEMSEnum::DP_AMP_AIR_SO2: {
        if (chanelNumber > AMP_MIN) {
            double deltaSO2 = 3.997;
            double valuePpmSO2 = deltaSO2 * HS_AMP_2_PPM_SO2;
            SETDPDATA(CEMSEnum::DP_PPM_AIR_SO2, MCR_DPDATA_DOUBLE_STD(valuePpmSO2, 2));

            double valueSO2 = valuePpmSO2 * HS_PPM_2_STD_SO2;
            SETDPDATA(CEMSEnum::DP_AIR_SO2, MCR_DPDATA_DOUBLE_STD(valueSO2, 2));
        } else {
            SETDPDATA(CEMSEnum::DP_PPM_AIR_SO2, EMPTY_STR);
            SETDPDATA(CEMSEnum::DP_AIR_SO2, EMPTY_STR);
        }
        break;
    }

    case CEMSEnum::DP_AMP_TEMP: {
        if (chanelNumber > AMP_MIN) {
            double deltaTemp = 4.001;
            double valueTemp = deltaTemp * HS_TEMP;
            SETDPDATA(CEMSEnum::DP_TEMP, MCR_DPDATA_DOUBLE_STD(valueTemp, 2));
        } else {
            SETDPDATA(CEMSEnum::DP_TEMP, EMPTY_STR);
        }
        break;
    }

    case CEMSEnum::DP_AMP_OPP: {
        if (chanelNumber > AMP_MIN) {
            double deltaOpp = 4.001;
            double valueOpp = deltaOpp * HS_OPP;
            SETDPDATA(CEMSEnum::DP_OPP, MCR_DPDATA_DOUBLE_STD(valueOpp, 2));
            double valueDustPM = 4.123;
            SETDPDATA(CEMSEnum::DP_DUST_PM, MCR_DPDATA_DOUBLE_STD(valueDustPM, 2));
        } else {
            SETDPDATA(CEMSEnum::DP_OPP, EMPTY_STR);
            SETDPDATA(CEMSEnum::DP_DUST_PM, EMPTY_STR);
        }
        break;
    }

    case CEMSEnum::DP_AMP_VEL: {
        if (chanelNumber > AMP_MIN) {
            double deltaVel = 4.087;
            double valueVel = deltaVel * HS_VEL;
            SETDPDATA(CEMSEnum::DP_VEL, MCR_DPDATA_DOUBLE_STD(valueVel, 2));
            double radius = GETDPDATA(CEMSEnum::DP_GENERAL_RADIUS).toDouble();
            if(radius > 0) {
                double valueFlow = valueVel * 3.14 * radius * radius;
                SETDPDATA(CEMSEnum::DP_FLOW, MCR_DPDATA_DOUBLE_STD(valueFlow, 2));
            } else
                SETDPDATA(CEMSEnum::DP_FLOW, EMPTY_STR);
        } else {
            SETDPDATA(CEMSEnum::DP_VEL, EMPTY_STR);
            SETDPDATA(CEMSEnum::DP_FLOW, EMPTY_STR);
        }
        break;
    }

    default:
        break;
    }
}
