/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: Screenlist
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef SCREENLIST_H
#define SCREENLIST_H

#include <QHash>

enum OverlayZ{
    Z_BACKGROUND = -1,
    Z_APPCONTAINER,
    Z_TOPBAR,
    Z_LOGIN,
    Z_KEYBOARD,
    Z_OVERLAY,
    Z_QUICKNOTES,
    Z_SPLASH
};

enum ScreenID {
    SCR_START,
    SCR_HOME,
    SCR_SETTINGS,
    SCR_SETTINGS_OVERVIEW,
    SCR_SETTINGS_DEVELOPMENT,
    SCR_SETTINGS_DEVICES,
    SCR_SETTINGS_USER,
    SCR_SETTINGS_SENSOR,
    SCR_SETTINGS_TELEMETRY,
    SCR_SETTINGS_POSITION,
    SCR_SETTINGS_ELECTRICAL_CODES,
    SCR_SETTINGS_DATA,
    SCR_SETTINGS_ALERT,
    SCR_WORK_MAIN,
    SCR_WORK_SIMPLE,
    SCR_DATAVIEW,
    SCR_WORK_THUYVAN,
    SCR_WORK_HAIVAN,
    SCR_END,

    PRT_TOPBAR,
    PRT_STATUSBAR,
    PRT_KEYBOARD,
    PRT_KEYBOARD_NUMBER_ONLY,

    OVERLAY_START = 0xA000,
    QN_COMMON,
    POPUP_LOGIN,
    POPUP_REQUEST_LOGIN,
    POPUP_LOGOUT,
    POPUP_REQUEST_DELETE_ACCOUNT,
    POPUP_CHANGE_PASSWORD,
    POPUP_CREATE_ACCOUNT,
    SPLASH_SCREEN,
    OVERLAY_END,
};

const QHash<int, QString> screenList = {
    {PRT_TOPBAR,                            "qrc:/resources/qmlScreen/prtTopBar.qml"                },
    {PRT_STATUSBAR,                         "qrc:/resources/qmlScreen/prtStatusBar.qml"             },
    {SCR_HOME,                              "qrc:/resources/qmlScreen/scrHome.qml"                  },
    {SCR_SETTINGS,                          "qrc:/resources/qmlScreen/scrSettings.qml"              },
    {PRT_KEYBOARD,                          "qrc:/resources/qmlScreen/prtKeyboard.qml"              },
    {PRT_KEYBOARD_NUMBER_ONLY,              "qrc:/resources/qmlScreen/prtKeyboardNumberOnly.qml"    },
    {SCR_SETTINGS_OVERVIEW,                 "qrc:/resources/qmlScreen/scrSettingsOverview.qml"      },
    {SCR_SETTINGS_DEVELOPMENT,              "qrc:/resources/qmlScreen/scrSettingsDevelopment.qml"   },
    {SCR_SETTINGS_DEVICES,                  "qrc:/resources/qmlScreen/scrSettingsDevices.qml"       },
    {SCR_SETTINGS_USER,                     "qrc:/resources/qmlScreen/scrSettingsUser.qml"          },
    {SCR_SETTINGS_SENSOR,                   "qrc:/resources/qmlScreen/scrSettingsSensor.qml"        },
    {SCR_SETTINGS_TELEMETRY,                "qrc:/resources/qmlScreen/scrSettingsTelemetry.qml"     },
    {SCR_SETTINGS_POSITION,                 "qrc:/resources/qmlScreen/scrSettingsPosition.qml"      },
    {SCR_SETTINGS_ELECTRICAL_CODES,         "qrc:/resources/qmlScreen/scrSettingsElectricalCodes.qml"},
    {SCR_SETTINGS_DATA,                     "qrc:/resources/qmlScreen/scrSettingsData.qml"          },
    {SCR_SETTINGS_ALERT,                    "qrc:/resources/qmlScreen/scrSettingsAlert.qml"         },
    {SCR_WORK_MAIN,                         "qrc:/resources/qmlScreen/scrWorkMain.qml"              },
    {SCR_WORK_SIMPLE,                       "qrc:/resources/qmlScreen/scrWorkSimple.qml"            },
    {SCR_WORK_THUYVAN,                      "qrc:/resources/qmlScreen/scrWorkThuyVan.qml"           },
    {SCR_WORK_HAIVAN,                       "qrc:/resources/qmlScreen/scrWorkHaiVan.qml"            },
    {SCR_DATAVIEW,                          "qrc:/resources/qmlScreen/scrDataview.qml"              },
    {SPLASH_SCREEN,                         "qrc:/resources/qmlScreen/splashScreen.qml"             },
    {QN_COMMON,                             "qrc:/resources/qmlScreen/qnCommon.qml"                 },
    {POPUP_LOGIN,                           "qrc:/resources/qmlScreen/popupLogin.qml"               },
    {POPUP_LOGOUT,                          "qrc:/resources/qmlScreen/popupLogout.qml"              },
    {POPUP_REQUEST_DELETE_ACCOUNT,          "qrc:/resources/qmlScreen/popupRequestDeleteAccount.qml"},
    {POPUP_REQUEST_LOGIN,                   "qrc:/resources/qmlScreen/popupRequestLogin.qml"        },
    {POPUP_CHANGE_PASSWORD,                 "qrc:/resources/qmlScreen/popupChangePassword.qml"      },
    {POPUP_CREATE_ACCOUNT,                  "qrc:/resources/qmlScreen/popupCreateAccount.qml"       },
};

#endif // SCREENLIST_H
