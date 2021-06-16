import QtQuick 2.0
import HMIEvents 1.0
import "../Widget"
import "../Js/Constants.js" as CONSTANTS
import "../Js/Translations.js" as TRANS

Item {
    id: tabHeader
    y: 3
    width: CONSTANTS.LEFT_TAB_WIDTH
    height: CONSTANTS.APP_HEIGHT

    property int currentIndex: 0

    Rectangle {
        anchors.fill: parent
        color: "#000000"
        opacity: 0.3
        z: -1
    }

    QTabDelegate {
        id: tabOverview
        parentIndex: currentIndex
        tabIndex: 0
        tabContentText: TRANS.STR_SETTINGS_LEFTTAB_COMMON_INFO
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", HMIEvents.HMI_TAB_SELECT, "overview")
        }
    }

    QTabDelegate {
        parentIndex: currentIndex
        tabIndex: 1
        tabContentText: TRANS.STR_SETTINGS_LEFTTAB_DEVICES
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", HMIEvents.HMI_TAB_SELECT, "devices")
        }
    }

    QTabDelegate {
        parentIndex: currentIndex
        tabIndex: 2
        tabContentText: TRANS.STR_SETTINGS_LEFTTAB_USERS
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", HMIEvents.HMI_TAB_SELECT, "users")
        }
    }

    QTabDelegate {
        parentIndex: currentIndex
        tabIndex: 3
        tabContentText: TRANS.STR_SETTINGS_LEFTTAB_SENSOR
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", HMIEvents.HMI_TAB_SELECT, "sensor")
        }
    }
    QTabDelegate {
        parentIndex: currentIndex
        tabIndex: 4
        tabContentText: TRANS.STR_SETTINGS_LEFTTAB_TELEMETRY
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", HMIEvents.HMI_TAB_SELECT, "telemetry")
        }
    }
    QTabDelegate {
        parentIndex: currentIndex
        tabIndex: 5
        tabContentText: TRANS.STR_SETTINGS_LEFTTAB_POSITION
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", HMIEvents.HMI_TAB_SELECT, "position")
        }
    }
    QTabDelegate {
        parentIndex: currentIndex
        tabIndex: 6
        tabContentText: TRANS.STR_SETTINGS_LEFTTAB_DATA
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", HMIEvents.HMI_TAB_SELECT, "data")
        }
    }
    QTabDelegate {
        parentIndex: currentIndex
        tabIndex: 7
        tabContentText: TRANS.STR_SETTINGS_LEFTTAB_ALERT
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", HMIEvents.HMI_TAB_SELECT, "alert")
        }
    }
}
