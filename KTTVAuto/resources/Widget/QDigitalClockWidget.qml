import QtQuick 2.0
import "../Js/Constants.js" as CONSTANTS

Item {
    id : clock
    width: 630
    height: 590
    property int hours: 0
    property int minutes: 0
    property int seconds: 0

    Image {
        id: imgBg
        width: parent.width
        height: parent.height
        z: 0
        fillMode: Image.PreserveAspectFit
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        source: "qrc:/resources/Image/bg_widget.png"
    }

    Image {
        id: imgTouch
        width: parent.width
        height: parent.height
        z: 1
        fillMode: Image.PreserveAspectFit
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        source: mouseClock.containsMouse ?  "qrc:/resources/Image/bg_widget_p.png" : "qrc:/resources/Image/bg_widget_f.png"

        MouseArea {
            id: mouseClock
            anchors.fill: parent
        }
    }

    Item {
        z: 2
        anchors.fill: parent
        Text {
            anchors.centerIn: parent
            text: "12:34"
            width: parent.width * 7/10
            height: parent.height
            font.pixelSize: 150
            font.family: CONSTANTS.FONT_SEGOE_UI_LIGHT
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#FFFFFF"
            elide: Text.ElideRight
        }
    }
}
