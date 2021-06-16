import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS
import "../Js/Defines.js" as DEFINES
import "../Js/Translations.js" as TRANS

Item {
    objectName: "prt_statusbar"
    x: 0
    y: 0
    width: CONSTANTS.SCREEN_WIDTH
    height: CONSTANTS.TOPBAR_HEIGHT

    Rectangle {
        x: 10
        y: 0
        z: 1
        width: CONSTANTS.SCREEN_WIDTH - 20
        height: 1
        color: "#FFFFFF"
    }

    Image {
        x: 15
        y: 10
        width: 50
        height: 50
        source: DEFINES.IMG_STATUSBAR_USER

        MouseArea {
            id: mouseHome
            anchors.fill: parent
            onClicked: UIBridge.hmiEvent("", HMIEvents.HMI_REQUEST_SHOW_LOGIN, "")
        }
    }

    QText {
        text: AppModel.isLogin ? (AppModel.userAccount + " " + TRANS.STR_STATUSBAR_LOGGED) : TRANS.STR_STATUSBAR_NO_LOGIN
        x: 80
        width: 300
        height: 70
    }

    QText {
        id: sttDayName
        anchors.right: sttDate.left
        anchors.rightMargin: 20
        height: CONSTANTS.TOPBAR_HEIGHT
        text: AppModel.systemDayName + "."
        font.pixelSize: 25
        color: "#FFFFFF"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    QText {
        id: sttDate
        anchors.right: sttTime.left
        anchors.rightMargin: 20
        height: CONSTANTS.TOPBAR_HEIGHT
        text: AppModel.systemDate
        font.pixelSize: 25
        color: "#FFFFFF"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }


    Rectangle {
        anchors.right: sttTime.left
        anchors.rightMargin: 10
        width: 1
        height: 40
        y: 15
        visible: sttTime.text !== ''
    }

    QText {
        id: sttTime
        anchors.right: parent.right
        anchors.rightMargin: 20
        height: CONSTANTS.TOPBAR_HEIGHT
        text: AppModel.systemTime
        font.pixelSize: 28
        font.bold: true
        color: "#FFFFFF"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
