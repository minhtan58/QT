import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Js/Defines.js" as DEFINES

Item {
    property alias timeout: tim.interval

    Rectangle {
        anchors.fill: parent
        color: "#000000"
        MouseArea {
            anchors.fill: parent
        }
    }

    Image {
        anchors.fill: parent
        asynchronous: true
        source: DEFINES.IMG_SPLASH
    }

    Timer {
        id: tim
        repeat: false
        onTriggered: UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_REQUEST_HIDE_POPUP, "")
    }

    Component.onCompleted: {
        tim.start()
    }
}

