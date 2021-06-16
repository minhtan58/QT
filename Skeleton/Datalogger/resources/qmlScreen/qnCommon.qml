import QtQuick 2.0
import CEMSEnum 1.0

Item {
    id: toast
    property alias timeout: tim.interval
    property alias message: textContent.text
    width: 800
    height: 480

    Timer {
        id: tim
        repeat: false
        onTriggered: Delivery.hmiEvent(this.objectName, CEMSEnum.HMI_REQUEST_HIDE_POPUP, "")
    }

    Rectangle {
        anchors.fill: parent
        color: "#000000"
        opacity: 0.5
    }

    Rectangle {
        id: qnBgr
        width: 400
        height: 100
        anchors.centerIn: parent
        color: "#315b7d"
        opacity: 0.95
    }

    Text {
        id: textContent
        anchors.fill: qnBgr
        text: "Save Successful"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 25
        wrapMode: Text.Wrap
    }

    MouseArea {
        anchors.fill: parent
        onClicked: Delivery.hmiEvent(this.objectName, CEMSEnum.HMI_REQUEST_HIDE_POPUP, "")
    }

    Component.onCompleted: {
        tim.start()
    }
}
