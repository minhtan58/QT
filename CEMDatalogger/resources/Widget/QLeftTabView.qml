import QtQuick 2.0
import CEMSEnum 1.0
import "../Widget"

Item {
    id: tabHeader
    y: 3
    width: 205
    height: 410

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
        y: 0
        tabIndex: 0
        tabContentText: "OVERVIEW"
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", CEMSEnum.HMI_TAB_SELECT, "overview")
        }
    }

    QTabDelegate {
        id: tabGeneral
        parentIndex: currentIndex
        y: 50
        tabIndex: 1
        tabContentText: "GENERAL"
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", CEMSEnum.HMI_TAB_SELECT, "general")
        }
    }


    QTabDelegate {
        parentIndex: currentIndex
        y: 100
        tabIndex: 2
        tabContentText: "NETWORK"
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", CEMSEnum.HMI_TAB_SELECT, "network")
        }
    }

    QTabDelegate {
        parentIndex: currentIndex
        y: 150
        tabIndex: 3
        tabContentText: "SENSOR"
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", CEMSEnum.HMI_TAB_SELECT, "serialport")
        }
    }

    QTabDelegate {
        parentIndex: currentIndex
        y: 200
        tabIndex: 4
        tabContentText: "ALARM"
        onTabCliked: {
            currentIndex = tabIndex
            UIBridge.hmiEvent("", CEMSEnum.HMI_TAB_SELECT, "alarm")
        }
    }
}
