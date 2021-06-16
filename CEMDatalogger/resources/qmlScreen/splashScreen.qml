import QtQuick 2.0
import CEMSEnum 1.0

Item {
    property alias timeout: tim.interval

    Rectangle {
        anchors.fill: parent
        color: "#000000"
    }

    Image {
        anchors.fill: parent
        asynchronous: true
        source: "qrc:/resources/Image/logox.png"
    }

    Timer {
        id: tim
        repeat: false
        onTriggered: UIBridge.hmiEvent(this.objectName, CEMSEnum.HMI_REQUEST_HIDE_POPUP, "")
    }

    MouseArea {
        anchors.fill: parent
    }

    Component.onCompleted: {
        tim.start()
    }
}

