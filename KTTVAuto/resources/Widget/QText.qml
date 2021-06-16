import QtQuick 2.2
import "../Js/Constants.js" as CONSTANTS

Text {
    property alias backgroundColor : background.color
    property bool hasBorder: false
    color: "#ffffff"
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignLeft
    font.pixelSize: 23
    wrapMode: Text.Wrap
    font.family: CONSTANTS.FONT_SEGOE_UI
    height: 45
    Rectangle {
        id: background
        z: -1
        anchors.fill: parent
        color: hasBorder ? "#000000" : "transparent"
        opacity: hasBorder ? 0.5 : 1
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.width: 2
        border.color: "gray"
        visible: hasBorder
    }
}

