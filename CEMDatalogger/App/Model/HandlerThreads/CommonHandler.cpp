#include "CommonHandler.h"

CommonHandler::CommonHandler(QObject *parent)
    : QObject(parent)
{
}

void CommonHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case CEMSEnum::HMI_DATAVIEW_SWITCH_UNIT: {
        if (objectName == "viewCO") {
            SETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_CO, param);
        } else if (objectName == "viewNO") {
            SETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NO, param);
        } else if (objectName == "viewNOX") {
            SETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_NOX, param);
        } else if (objectName == "viewSO2") {
            SETDPDATA(CEMSEnum::DP_SETTINGS_DATAVIEW_MODE_SO2, param);
        }
        else {}
        break;
    }
    default:
        break;
    }
}

void CommonHandler::updateAppData(int dpid)
{
    QString data = GETDPDATA(dpid);
    switch (dpid) {
    case CEMSEnum::DP_AIR_O2:
    case CEMSEnum::DP_AIR_CO:
    case CEMSEnum::DP_AIR_NO:
    case CEMSEnum::DP_AIR_NOX:
    case CEMSEnum::DP_AIR_SO2:
    case CEMSEnum::DP_TEMP:
    case CEMSEnum::DP_OPP:
    case CEMSEnum::DP_DUST_PM:
    case CEMSEnum::DP_VEL:
    case CEMSEnum::DP_FLOW:

    case CEMSEnum::DP_SETTINGS_ALARM_O2_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_CO_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_NO_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_NOX_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_SO2_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_TEMP_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_OPP_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_VEL_STATUS:
    case CEMSEnum::DP_SETTINGS_ALARM_FLOW_STATUS:

    case CEMSEnum::DP_SETTINGS_ALARM_O2_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_CO_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_NO_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_NOX_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_SO2_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_TEMP_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_OPP_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_VEL_MIN:
    case CEMSEnum::DP_SETTINGS_ALARM_FLOW_MIN:

    case CEMSEnum::DP_SETTINGS_ALARM_O2_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_CO_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_NO_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_NOX_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_SO2_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_TEMP_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_OPP_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_DUST_PM_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_VEL_MAX:
    case CEMSEnum::DP_SETTINGS_ALARM_FLOW_MAX: {
        int cnt = 0;
        for (int idx = 0; idx < 10; ++idx) {
            if(GETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_STATUS + idx*3) == "1"
                    && !(GETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MIN + idx*3).isEmpty())
                    && !(GETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MAX + idx*3).isEmpty())
                    && !(GETDPDATA(CEMSEnum::DP_AIR_O2 + idx).isEmpty())) {
                double curVal = GETDPDATA(CEMSEnum::DP_AIR_O2 + idx).toDouble();
                if(curVal < GETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MIN + idx*3).toDouble()
                        || curVal > GETDPDATA(CEMSEnum::DP_SETTINGS_ALARM_O2_MAX + idx*3).toDouble()) {
                    SETDPDATA(CEMSEnum::DP_STATUS_ALARM_O2 + idx, "1");
                    cnt++;
                } else {
                    SETDPDATA(CEMSEnum::DP_STATUS_ALARM_O2 + idx, "0");
                }
            } else {
                SETDPDATA(CEMSEnum::DP_STATUS_ALARM_O2 + idx, "0");
            }
        }
        SETDPDATA(CEMSEnum::DP_STATUS_ALARM_ON_COUNT, QString::number(cnt));
        break;
    }
    case CEMSEnum::DP_SETTINGS_SERIALPORT_TEST_CONNECTION:
    case CEMSEnum::DP_SETTINGS_NETWORK_SERVER_TEST_CONNECTION:
    case CEMSEnum::DP_SETTINGS_NETWORK_FTP_TEST_CONNECTION: {
        switch (data.toInt()) {
        case TC_TESTING:
            break;
        case TC_TEST_RESULT_OK:
            SENDEVENT("" , CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Connect OK!");
            SETDPDATA(dpid, QString::number(int(TC_IDLE)));
            break;
        case TC_TEST_RESULT_FAIL:
            SENDEVENT("" , CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Connect Fail!");
            SETDPDATA(dpid, QString::number(int(TC_IDLE)));
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
