/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: Defines
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <QHash>

enum OverlayZ {
    Z_BACKGROUND = -1,
    Z_APPCONTAINER,
    Z_TOPBAR,
    Z_KEYBOARD,
    Z_OVERLAY,
    Z_SPLASH
};

enum ScreenID {
    SCR_THERMAL_NORMAL,
};

const QHash<int, QString> screenList = {
    {SCR_THERMAL_NORMAL,        "qrc:/resources/qml/screen/scrThermalNormal.qml"},
};

#endif // COMMON_H
