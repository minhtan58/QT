#include "HMIEvents.h"
#include "DataManager.h"
#include "TemperatureAlarmHandler.h"

TemperatureAlarmHandler::TemperatureAlarmHandler(QObject *parent)
    : QObject(parent)
    , m_thresoldMinTemp(GETDP(DPID::DP_SETTINGS_THRESOLD_MINTEMP).toDouble())
    , m_thresoldMaxTemp(GETDP(DPID::DP_SETTINGS_THRESOLD_MAXTEMP).toDouble())
{
    DLOG("Create");
    m_timTempAlarm = new QTimer(this);
    m_timTempAlarm->setInterval(GETDP(DPID::DP_SETTINGS_VERIFYTIME).toInt() * 1000);
    m_timTempAlarm->setSingleShot(true);
    connect(DataManager::getInstance(), SIGNAL(dataChanged(int,QString)), this, SLOT(updateData(int,QString)));
}

void TemperatureAlarmHandler::updateData(int dpid, QString value)
{
    switch (dpid) {
    case DPID::DP_THERMAL_TEMPERATURE: {
        double currentMaxTemp = value.toDouble();

        /* dummy code */
        if(currentMaxTemp > m_thresoldMaxTemp || currentMaxTemp < m_thresoldMinTemp) {
            SETDP(DPID::DP_THERMAL_TEMPERATURE_ALARM_NOTIFY, "1");
        } else {
            SETDP(DPID::DP_THERMAL_TEMPERATURE_ALARM_NOTIFY, "0");
        }
        //

        if(currentMaxTemp > m_thresoldMaxTemp || currentMaxTemp < m_thresoldMinTemp) {
            if(!m_timTempAlarm->isActive()) {
                DLOG("Send request REQUEST_SEND_FDALARM");
                emit Delivery::getInstance()->hmiEvent("", REQUEST_SEND_FDALARM, "");
                m_timTempAlarm->start();
            }
        }

        break;
    }
    case DPID::DP_SETTINGS_THRESOLD_MINTEMP: {
        m_thresoldMinTemp = value.toDouble();
        break;
    }
    case DPID::DP_SETTINGS_THRESOLD_MAXTEMP: {
        m_thresoldMaxTemp = value.toDouble();
        break;
    }
    case DPID::DP_SETTINGS_VERIFYTIME: {
        m_timTempAlarm->setInterval(value.toInt()*1000);
        break;
    }
    default:
        break;
    }
}
