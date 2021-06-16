import QtQuick 2.0
import "../Js/Constants.js" as CONSTANTS

Rectangle {
    property int parentIndex: 0
    property int tabIndex: 0
    property alias tabIcon: icon.source
    property alias tabContentText: content.text
    width: parent.width
    height: 65
    y: height * tabIndex
    color: tabIndex === parentIndex ? "gray" : "transparent"
    opacity: mouseDelegate.containsMouse ? 0.5 : 1

    signal tabCliked

    Image {
        id: icon
        x: 5
        width: 70
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: content
        x: 50
        width: parent.width - x
        height: parent.height
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 23
        wrapMode: Text.Wrap
        font.family: CONSTANTS.FONT_REGULAR
    }

    Rectangle {
        x: 10
        y: parent.height - height
        width: parent.width - 20
        height: 1
        color: "gray"
    }

    MouseArea {
        id: mouseDelegate
        anchors.fill: parent
        onClicked: tabCliked()
    }
}
