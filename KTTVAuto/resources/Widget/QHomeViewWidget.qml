import QtQuick 2.2
import "../Js/Constants.js" as CONSTANTS

Item {
    property url normalSource: ""
    property url focusSource: ""
    property alias textContent: iconName.text

    signal appClick

    Rectangle {
        id: rect
        anchors.fill: parent
        anchors.margins: 10
        color: mouseHome.containsMouse ? "#FFFFFF" : "#000000"
        opacity: 0.5
        border.width: 2
        border.color: "#FFFFFF"
//        opacity: mouseHome.containsMouse ? 0.3 : 0.15
        radius: 30
//        gradient: Gradient {
//            GradientStop { position: 0.0; color: "#1c3448" }
//            GradientStop { position: 0.3; color: "#6a9bc3" }
//            GradientStop { position: 0.7; color: "#6a9bc3" }
//            GradientStop { position: 1.0; color: "#1c3448" }
//        }
    }

    Image {
        id: imgIcon
        anchors.fill: parent
        fillMode: Image.Pad
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        source: normalSource
    }
    QText {
        id: iconName
        width: parent.width
        y: 230
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 30
    }

    MouseArea {
        id: mouseHome
        anchors.fill: parent
        anchors.margins: 10
        preventStealing: true
        onClicked: appClick()
    }
}


