/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: QMLConstants.cpp
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#include "QMLConstants.h"

QMLConstants::QMLConstants(QObject *parent)
    : QObject(parent)
    , m_currentTime("")
    , m_currentDate("")
    , m_screenWidth(SCREEN_WIDTH)
    , m_screenHeight(SCREEN_HEIGHT)
    , m_topbarHeight(TOPBAR_HEIGHT)
    , m_appHeight(APP_HEIGHT)
    , m_backgroundZ(Z_BACKGROUND)
    , m_appContainerZ(Z_APPCONTAINER)
    , m_topbarZ(Z_TOPBAR)
    , m_keyboardZ(Z_KEYBOARD)
    , m_overlayZ(Z_OVERLAY)
    , m_splashZ(Z_SPLASH)
{}

int QMLConstants::screenWidth() const
{
    return m_screenWidth;
}

int QMLConstants::screenHeight() const
{
    return m_screenHeight;
}

int QMLConstants::topbarHeight() const
{
    return m_topbarHeight;
}

int QMLConstants::appHeight() const
{
    return m_appHeight;
}

int QMLConstants::backgroundZ() const
{
    return m_backgroundZ;
}

int QMLConstants::appContainerZ() const
{
    return m_appContainerZ;
}

int QMLConstants::overlayZ() const
{
    return m_overlayZ;
}

QString QMLConstants::currentTime() const
{
    return m_currentTime;
}

void QMLConstants::setCurrentTime(const QString &currentTime)
{
    if(m_currentTime != currentTime) {
        m_currentTime = currentTime;
        emit currentTimeChanged();
    }
}

QString QMLConstants::currentDate() const
{
    return m_currentDate;
}

void QMLConstants::setCurrentDate(const QString &currentDate)
{
    if(m_currentDate != currentDate) {
        m_currentDate = currentDate;
        emit currentDateChanged();
    }
}

QString QMLConstants::stationName() const
{
    return m_stationName;
}

void QMLConstants::setStationName(const QString &stationName)
{
    if(m_stationName != stationName) {
        m_stationName = stationName;
        emit stationNameChanged();
    }
}

QString QMLConstants::stationId() const
{
    return m_stationId;
}

void QMLConstants::setStationId(const QString &stationId)
{
    if(m_stationId != stationId) {
        m_stationId = stationId;
        emit stationIdChanged();
    }
}

int QMLConstants::splashZ() const
{
    return m_splashZ;
}

int QMLConstants::topbarZ() const
{
    return m_topbarZ;
}

int QMLConstants::keyboardZ() const
{
    return m_keyboardZ;
}
