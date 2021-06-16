import QtQuick 2.0
import CEMSEnum 1.0
import "../Widget/"

Item {
    id: toast
    property alias timeout: tim.interval
    property alias message: textContent.text
    width: 800
    height: 480

    Timer {
        id: tim
        repeat: false
        onTriggered: UIBridge.hmiEvent(this.objectName, CEMSEnum.HMI_REQUEST_HIDE_POPUP, "")
    }

    Rectangle {
        anchors.fill: parent
        color: "#000000"
        opacity: 0.5
        MouseArea {
            anchors.fill: parent
        }
    }

    Rectangle {
        id: qnBgr
        width: 400
        height: 200
        anchors.centerIn: parent
        color: "#315b7d"
        opacity: 0.95
        border.color: "#FFFFFF"
        border.width: 2

        Text {
            id: textContent
            width: parent.width
            height: 150
            z: 1
            text: "Export data for " + UIBridge.getDPData(CEMSEnum.DP_SEARCH_TIME_HISTORY_DATA) + "?"
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 25
            wrapMode: Text.Wrap
        }

        QButton {
            x: 5
            y: 145
            z: 1
            width: 190
            height: 50
            text: "Yes"
            eventID: CEMSEnum.HMI_BUTTON_REQ_EXPORT
        }

        QButton {
            z: 1
            x: 205
            y: 145
            width: 190
            height: 50
            text: "No"
            eventID: CEMSEnum.HMI_REQUEST_HIDE_POPUP
        }
    }

    Component.onCompleted: {
        tim.start()
    }
}
