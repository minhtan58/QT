import QtQuick 2.0
import "../Js/Constants.js" as CONSTANTS

Item {
    property string groupTitle: "Group Name"
//    Drag.active: dragArea.drag.active

    MouseArea {
        id: dragArea
        anchors.fill: parent
//        drag.target: parent
    }

    Rectangle {
        id: bgr
        anchors.fill: parent
        border.color: "#FFFFFF"
        border.width: 1
        color: "#000000"
        opacity: 0.5
    }

    Rectangle {
        id: rectTitle
        width: parent.width
        height: 35
        color: "#315b7d"
        QText {
            x: 20
            width: parent.width - 20
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            color: "#ffffff"
            font.pixelSize: 23
            wrapMode: Text.Wrap
            font.family: CONSTANTS.FONT_SEGOE_UI
            font.bold: true
            text: groupTitle
        }
    }
}

