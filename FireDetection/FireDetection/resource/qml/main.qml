import QtQuick 2.6
import QtQuick.Window 2.2
import CommonImage 1.0
import "widget"

Window {
    visible: true
    width: 800
    height: 480
    title: qsTr("Fire Detection")

    Rectangle {
        id: grpPath
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50
        anchors.margins: 10
        color: "transparent"
        opacity: 0.5
        QTextInput {
            id: txtPath
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: grpPath.width * 0.8
        }
        QButton {
            anchors.left: txtPath.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            text: "Browser"
            width: grpPath.width * 0.2
        }
    }

    Rectangle {
        border.color: "gray"
        border.width: 1
        anchors.fill: imgDetect
        color: "transparent"
        z: -1
    }

    CommonImage {
        id: imgDetect
        objectName: "imgDetect"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: grpPath.bottom
        anchors.bottom: parent.bottom
        anchors.margins: 10
    }
}
