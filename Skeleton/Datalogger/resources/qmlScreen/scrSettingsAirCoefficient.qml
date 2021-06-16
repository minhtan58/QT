import QtQuick 2.0
import "../Widget"

Item {
    objectName: "scr_settings_air_coefficient"
    anchors.fill: parent

    Item {
        y: 5
        anchors.horizontalCenter: parent.horizontalCenter
        width: 580
        height: 390
        Rectangle {
            anchors.fill: parent
            radius: 10
            color: "#315b7d"
            opacity: 0.3
            gradient: Gradient {
                GradientStop { position: 0.0; color: "steelblue" }
                GradientStop { position: 1.0; color: "#000000" }
            }
        }

        Item {
            id: header
            x: 0
            y: 0
            width: parent.width
            height: 50
            Rectangle {
                anchors.fill: parent
                anchors.bottomMargin: 1
                opacity: 0.8
                clip: true
                border.color: "steelblue"
                border.width: 2
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#6a9bc3" }
                    GradientStop { position: 0.4; color: "#1c3448" }
                    GradientStop { position: 0.6; color: "#1c3448" }
                    GradientStop { position: 1.0; color: "#6a9bc3" }
                }
            }

            Text {
                anchors.fill: parent
                text: "Air Coefficient Settings"
                elide: Text.ElideRight
                font.bold: true
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }
        }
    }
}
