#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <thread>

#include "commontype.h"
#include "Defines.h"
#include "Constants.h"
#include "ScreenList.h"
#include "Delivery.h"
#include "SettingsLoader.h"

enum AirModeView {
    CEMS_SETTINGS_VIEW_STD = 0,
    CEMS_SETTINGS_VIEW_PPM,
    CEMS_SETTINGS_VIEW_AMP,
};

enum KeyboardType {
    CEMS_KEYBOARD_KEY_TYPE_CHARACTER = 0,
    CEMS_KEYBOARD_KEY_TYPE_CTRL
};

enum TestConnection {
    TC_IDLE,
    TC_TESTING,
    TC_TEST_RESULT_OK,
    TC_TEST_RESULT_FAIL,
};

enum FetchDataStatus {
    FETCH_IDLE,
    FETCH_STARTING,
    FETCH_FINISHED
};

inline QStringList getListParam(QString params)
{
    return params.split(",");
}

#endif // COMMON_H
