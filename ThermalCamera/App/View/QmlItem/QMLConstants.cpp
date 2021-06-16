/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: QMLConstants.cpp
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#include "QMLConstants.h"
#include "Common.h"

QMLConstants::QMLConstants(QObject *parent)
    : QObject(parent)
    , m_screenWidth(SCREEN_WIDTH)
    , m_screenHeight(SCREEN_HEIGHT)
    , m_topbarHeight(TOPBAR_HEIGHT)
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
