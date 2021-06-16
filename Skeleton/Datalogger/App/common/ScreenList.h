/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: ScreenList
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef SCREENLIST_H
#define SCREENLIST_H

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
    SCR_START = 0x0000,
    SCR_DATAVIEW,
    SCR_HISTORY_DATAVIEW,
    SCR_SETTINGS_OVERVIEW,
    SCR_SETTINGS_GENERAL,
    SCR_SETTINGS_NETWORK,
    SCR_SETTINGS_SERIALPORT,
    SCR_SETTINGS_AIRCOEFFICIENT,
    SCR_SETTINGS_ALARM,
    SCR_SETTINGS_DEVELOPMENT,
    SCR_END,

    PRT_TOPBAR,
    PRT_STATUSBAR,
    PRT_KEYBOARD,
    PRT_KEYBOARD_NUMBER_ONLY,

    OVERLAY_START = 0xA000,
    QN_COMMON,
    POPUP_EXPORT_FILE,
    SPLASH_SCREEN
};

const QHash<int, QString> screenList = {
    {SCR_DATAVIEW,                          "qrc:/resources/qmlScreen/scrDataView.qml"              },
    {PRT_KEYBOARD,                          "qrc:/resources/qmlScreen/prtKeyboard.qml"              },
    {PRT_KEYBOARD_NUMBER_ONLY,              "qrc:/resources/qmlScreen/prtKeyboardNumberOnly.qml"    },
    {SCR_SETTINGS_OVERVIEW,                 "qrc:/resources/qmlScreen/scrSettingsOverview.qml"      },
    {SCR_SETTINGS_GENERAL,                  "qrc:/resources/qmlScreen/scrSettingsGeneral.qml"       },
    {SCR_SETTINGS_NETWORK,                  "qrc:/resources/qmlScreen/scrSettingsNetwork.qml"       },
    {SCR_SETTINGS_SERIALPORT,               "qrc:/resources/qmlScreen/scrSettingsSerialPort.qml"    },
    {SCR_SETTINGS_AIRCOEFFICIENT,           "qrc:/resources/qmlScreen/scrSettingsAirCoefficient.qml"},
    {SCR_SETTINGS_ALARM,                    "qrc:/resources/qmlScreen/scrSettingsAlarm.qml"         },
    {SCR_SETTINGS_DEVELOPMENT,              "qrc:/resources/qmlScreen/scrSettingsDevelopment.qml"   },
    {SCR_HISTORY_DATAVIEW,                  "qrc:/resources/qmlScreen/scrHistoryDataView.qml"       },
    {SPLASH_SCREEN,                         "qrc:/resources/qmlScreen/splashScreen.qml"             },
    {QN_COMMON,                             "qrc:/resources/qmlScreen/qnCommon.qml"                 },
    {POPUP_EXPORT_FILE,                     "qrc:/resources/qmlScreen/popupExportFile.qml"          },
};

#endif // SCREENLIST_H
