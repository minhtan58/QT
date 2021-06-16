import QtQuick 2.0
import "../Js/Constants.js" as CONSTANTS

Image {
    property alias border: rectBorder.border
    property alias emptyTextFont: txtEmptyText.font
    property alias emptyText: txtEmptyText.text
    property alias emptyTextColor: txtEmptyText.color

    Rectangle {
        id: rectBorder
        anchors.fill: parent
        color: "transparent"
        border.color: "#ffffff"
        border.width: 2
    }

    Text {
        id: txtEmptyText
        color: "#ffffff"
        anchors.centerIn: parent
        font.pixelSize: 23
        wrapMode: Text.Wrap
        font.family: CONSTANTS.FONT_SEGOE_UI
        text: qsTr("text")
    }
}
