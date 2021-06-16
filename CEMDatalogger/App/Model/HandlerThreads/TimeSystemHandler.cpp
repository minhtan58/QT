/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: TimeSystemHandler.cpp
    Create: 06/03/2018
    Author: Minh Tan

 ****************************************************************************/

#include "TimeSystemHandler.h"

TimeSystemHandler::TimeSystemHandler(QObject *parent)
    : QObject(parent)
{
    m_process = new QProcess(this);
}

void TimeSystemHandler::updateSystemTime()
{
    SETDPDATA(CEMSEnum::DP_SYS_DATE, QDateTime::currentDateTime().toString("dd/MM/yyyy"));
    SETDPDATA(CEMSEnum::DP_SYS_TIME, QDateTime::currentDateTime().toString("hh:mm"));

    SETDPDATA(CEMSEnum::DP_SYS_TIME_HOUR, QDateTime::currentDateTime().toString("HH"));     //hour always 24h format
    SETDPDATA(CEMSEnum::DP_SYS_TIME_MINUTES, QDateTime::currentDateTime().toString("mm"));

    SETDPDATA(CEMSEnum::DP_SYS_DATE_YEAR, QDateTime::currentDateTime().toString("yyyy"));
    SETDPDATA(CEMSEnum::DP_SYS_DATE_MONTH, QDateTime::currentDateTime().toString("MM"));
    SETDPDATA(CEMSEnum::DP_SYS_DATE_DAY, QDateTime::currentDateTime().toString("dd"));
}

void TimeSystemHandler::eventHandler(QString objectName, int eventId, QString param)
{
    QStringList params = getListParam(param);
    Q_UNUSED(objectName)
    switch (eventId) {
    case CEMSEnum::HMI_SWITCH_UPDATE_TIME_AUTOMATIC: {
        SETDPDATA(CEMSEnum::DP_SYS_SETTINGS_TIME_AUTOMATIC_UPDATE, QString::number(1 - param.toUInt()));
        SettingsLoader::setValue(SETTINGS_GROUP_GENERAL, SETTINGS_GENERAL_SYSTEMTIME_UPDATE_AUTOMATIC, QString::number(1 - param.toUInt()));
        m_process->start("/usr/CEMSDatalogger/scripts/updatetime.sh");
        m_process->waitForFinished();
        break;
    }
    case CEMSEnum::HMI_BUTTON_SET_DATE_TIME: {
        if(GETDPDATA(CEMSEnum::DP_SYS_SETTINGS_TIME_AUTOMATIC_UPDATE) != "1" && params.size() >= 5) {
#if 0
            QString command = QString("sudo timedatectl set-ntp false && sudo timedatectl set-time '%1-%2-%3 %4:%5'").arg(params.at(0)).arg(params.at(1)).arg(params.at(2)).arg(params.at(3)).arg(params.at(4));
            m_process->start(command);
#else
            m_process->start("/usr/CEMSDatalogger/scripts/settime.sh", params);
#endif
            m_process->waitForFinished();
            SENDEVENT("" , CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Date Time has been set");
        }
        break;
    }
    default:
        break;
    }
}

void TimeSystemHandler::updateAppData(int dpid)
{
    switch (dpid) {
    case CEMSEnum::DP_SYS_SETTINGS_TIME_AUTOMATIC_UPDATE: {
        if(GETDPDATA(dpid) == "1") {
            m_process->start("/usr/CEMSDatalogger/scripts/updatetime.sh");
            m_process->waitForFinished();
        }
        break;
    }
    default:
        break;
    }
}
