/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: TimeSystemHandler.cpp
    Create: 06/03/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#include "TimeSystemHandler.h"

TimeSystemHandler::TimeSystemHandler(QObject *parent)
    : QObject(parent)
{
}

void TimeSystemHandler::updateSystemTime()
{
    MODEL->systemDateSet(QDateTime::currentDateTime().toString("dd/MM/yyyy"));
    MODEL->systemTimeSet(QDateTime::currentDateTime().toString("hh:mm"));

    MODEL->systemHourSet(QDateTime::currentDateTime().toString("HH").toUInt());     //hour always 24h format
    MODEL->systemMinuteSet(QDateTime::currentDateTime().toString("mm").toUInt());
    MODEL->systemSecondSet(QDateTime::currentDateTime().toString("ss").toUInt());

    MODEL->systemYearSet(QDateTime::currentDateTime().toString("yyyy").toUInt());
    MODEL->systemMonthSet(QDateTime::currentDateTime().toString("MM").toUInt());
    MODEL->systemDaySet(QDateTime::currentDateTime().toString("dd").toUInt());
    MODEL->systemDayNameSet(QDateTime::currentDateTime().toString("ddd"));

    MODEL->dbFormatCurrentTimeSet(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
}

void TimeSystemHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case HMIEvents::HMI_SWITCH_UPDATE_TIME_AUTOMATIC: {
        SettingsLoader::setValue(SETTINGS_GROUP_DEVICE, SETTINGS_DEVICE_SYSTEMTIME_UPDATE_AUTOMATIC, QString::number(1 - param.toUInt()));
        SENDREQUEST(HMIEvents::HMI_REQUEST_GET_NETWORK_TIME);
        QProcess process;
        process.start("sudo timedatectl set-ntp true");
        process.waitForFinished();
        break;
    }
    case HMIEvents::HMI_BUTTON_SET_DATE_TIME: {
        QStringList params = getListParam(param);
        if(param.size() >= 5) {
            DLOG("set time %s-%s-%s %s:%s",
                 params[0].toStdString().data(),
                    params[1].toStdString().data(),
                    params[2].toStdString().data(),
                    params[3].toStdString().data(),
                    params[4].toStdString().data());
            QProcess process;
#if 0
            QString command = QString("sudo timedatectl set-ntp false && sudo timedatectl set-time '%1-%2-%3 %4:%5'")
                    .arg(params.at(0))
                    .arg(params.at(1))
                    .arg(params.at(2))
                    .arg(params.at(3))
                    .arg(params.at(4));
            process.start(command);
#else
            process.start("/usr/KTTVAuto/scripts/settime.sh", params);
#endif
            process.waitForFinished();
            SENDEVENT("" , HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Đã cài đặt ngày");
        }
        break;
    }
    default:
        break;
    }
}

#ifdef  __linux__
void TimeSystemHandlerThread::sltSetSystemTime()
{

}
#endif
