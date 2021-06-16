import QtQuick 2.0
import CEMSEnum 1.0
import "../Widget"

Item {
    objectName: "scr_settings_development"
    anchors.fill: parent

    QLeftTabView {
        currentIndex: 5

        QTabDelegate {
            parentIndex: parent.currentIndex
            y: 250
            tabIndex: 5
            tabContentText: "DEVELOPMENT"       
        }
    }

    Item {
        x: 210
        y: 10
        width: 580
        height: 390
        Rectangle {
            anchors.fill: parent
            radius: 10
            color: "#315b7d"
            opacity: 0.3
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
                text: "Development"
                elide: Text.ElideRight
                font.bold: true
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }
        }

        Item {
            x: 50
            y: 50

            QButton {
                x: 100
                y: 50
                width: 300
                height: 40
                text: "Reload Configuration File"
                eventID: CEMSEnum.HMI_BUTTON_RELOAD_CONFIGURATION_FILE
            }

            QButton {
                x: 100
                y: 100
                width: 300
                height: 40
                text: "Set Air Coefficient"
                eventID: CEMSEnum.HMI_TAB_SELECT
                eventParams: "aircoefficient"
            }
        }
    }
}
