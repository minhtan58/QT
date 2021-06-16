/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: QMLConstants.h
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef QMLCONSTANTS_H
#define QMLCONSTANTS_H

#include <QObject>

#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   800
#define TOPBAR_HEIGHT   70

class QMLConstants : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int screenWidth      READ screenWidth    CONSTANT)
    Q_PROPERTY(int screenHeight     READ screenHeight   CONSTANT)
    Q_PROPERTY(int topbarHeight     READ topbarHeight   CONSTANT)
    Q_PROPERTY(int backgroundZ      READ backgroundZ    CONSTANT)
    Q_PROPERTY(int appContainerZ    READ appContainerZ  CONSTANT)
    Q_PROPERTY(int overlayZ         READ overlayZ       CONSTANT)
    Q_PROPERTY(int topbarZ          READ topbarZ        CONSTANT)
    Q_PROPERTY(int keyboardZ        READ keyboardZ      CONSTANT)
    Q_PROPERTY(int splashZ          READ splashZ        CONSTANT)

public:
    explicit QMLConstants(QObject *parent = nullptr);

    int screenWidth() const;
    int screenHeight() const;
    int topbarHeight() const;
    int backgroundZ() const;
    int appContainerZ() const;
    int overlayZ() const;
    int topbarZ() const;
    int keyboardZ() const;
    int splashZ() const;

private:
    int m_screenWidth;
    int m_screenHeight;
    int m_topbarHeight;

    //overlay
    int m_backgroundZ;
    int m_appContainerZ;
    int m_topbarZ;
    int m_keyboardZ;
    int m_overlayZ;
    int m_splashZ;
};

#endif // QMLCONSTANTS_H
