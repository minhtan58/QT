import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS
import "../Js/Defines.js" as DEFINES

Item {
    objectName: "prt_topbar"
    x: 0
    y: 0
    width: CONSTANTS.SCREEN_WIDTH
    height: CONSTANTS.TOPBAR_HEIGHT

    Rectangle {
        x: 10
        y: CONSTANTS.TOPBAR_HEIGHT - 2
        z: 1
        width: CONSTANTS.SCREEN_WIDTH - 20
        height: 1
        color: "#ffffff"
    }

    Image {
        x: 0
        y: 0
        width: 70
        height: 68
        source: mouseHome.containsMouse ? DEFINES.IMG_HOME_ACTIVE : DEFINES.IMG_HOME_INACTIVE

        MouseArea {
            id: mouseHome
            anchors.fill: parent
            onClicked: UIBridge.hmiEvent("", HMIEvents.HMI_BUTTON_HOME, "")
        }
    }

//    Image {
//        x: 70
//        y: 0
//        width: 70
//        height: 68
//        source: DEFINES.IMG_SETTINGS
//        fillMode: Image.Pad
//        verticalAlignment: Image.AlignVCenter
//        horizontalAlignment: Image.AlignHCenter
//        Rectangle {
//            anchors.fill: parent
//            color: "gray"
//            opacity: 0.3
//            visible: mouseSetting.containsMouse
//        }

//        MouseArea {
//            id: mouseSetting
//            anchors.fill: parent
//            onClicked: UIBridge.hmiEvent("", HMIEvents.HMI_HOME_SETTING, "")
//        }
//    }

    Image {
        id: btnSwitchMode
        anchors.right: btnBack.left
        anchors.rightMargin: 20
        y: 10
        width: 50
        height: 50
        source: "qrc:/resources/Image/switch.png"
        visible: AppModel.isWorkingScreen()
        opacity: mouseSwitch.containsMouse ? 0.5 : 1

        MouseArea {
            id: mouseSwitch
            anchors.fill: parent
            onClicked: UIBridge.hmiEvent("", HMIEvents.HMI_BUTTON_WORK_SWITCH_MODE, "")
        }
    }

    Image {
        id: btnBack
        anchors.top: parent.top
        anchors.right: parent.right
        source: mouseBack.containsMouse ? DEFINES.IMG_BACK_PRESS : DEFINES.IMG_BACK_NORMAL

        MouseArea {
            id: mouseBack
            anchors.fill: parent
            onClicked: UIBridge.hmiEvent("", HMIEvents.HMI_BUTTON_BACK, "")
        }
    }

    QText {
        anchors.centerIn: parent
        width: 500
        height: CONSTANTS.TOPBAR_HEIGHT
        text: AppModel.deviceName
        font.pixelSize: 30
        font.bold: true
        color: "#FFFFFF"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
