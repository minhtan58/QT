#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <thread>

#include "Defines.h"
#include "Constants.h"
#include "HMIEvents.h"

enum eKeyboardType {
    CEMS_KEYBOARD_KEY_TYPE_CHARACTER = 0,
    CEMS_KEYBOARD_KEY_TYPE_CTRL
};

enum eTestConnection {
    TC_IDLE,
    TC_TESTING,
    TC_TEST_RESULT_OK,
    TC_TEST_RESULT_FAIL,
};

enum eFetchDataStatus {
    FETCH_IDLE,
    FETCH_STARTING,
    FETCH_FINISHED
};

enum eCommandID{
    CMD_AT,
    CMD_AT_CLTS,
    CMD_AT_CCLK,

    //GPRS Command
    CMD_AT_CGATT,
    CMD_AT_CIPMUX,
    CMD_AT_CSTT,
    CMD_AT_CWMODE,
    CMD_AT_CIICR,
    CMD_AT_CIFSR,
    CMD_AT_CIPSTART,
    CMD_AT_CIPSEND,
    CMD_AT_CIPCLOSE,
    CMD_AT_CIPSHUT,
    CMD_AT_CFUN,

    //GSM Command
    CMD_AT_CMGF,
    CMD_AT_CMGW,
    CMD_AT_CMSS,
};

enum eTelemetrySendType {
    TELEMETRY_TYPE_INTERNET,
    TELEMETRY_TYPE_SMS,
    TELEMETRY_TYPE_AUTO
};

enum eTelemetryControlType {
    TELEMETRY_CONTROL_TYPE_USER,
    TELEMETRY_CONTROL_TYPE_AUTOMATIC
};

enum eDataviewType {
    TYPE_KHITUONG,
    TYPE_THUYVAN,
    TYPE_HAIVAN
};

inline QStringList getListParam(QString params)
{
    //DLOG("param size: %d", params.split("").size());
    return params.split("");
}

#endif // COMMON_H
