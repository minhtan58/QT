import QtQuick 2.0
import QtQuick.Controls 1.4
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS

Item {
    objectName: "scr_settings_general"

    function setFocus() {
        var oldState = this.pressed
        settings_serialport_portname.pressed = false
        settings_serialport_baudrate.pressed = false
        this.pressed = oldState
    }

    QLeftTabView {
        currentIndex: 3
    }

    Item {
        x: CONSTANTS.LEFT_TAB_WIDTH + 5
        y: 10
        width: CONSTANTS.SCREEN_WIDTH - x - 5
        height: CONSTANTS.APP_HEIGHT - 20
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
                text: "Sensor"
                elide: Text.ElideRight
                font.bold: true
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            MouseArea {
                anchors.fill: parent
                onClicked: gotoDevMode++
            }
        }

        Item {
            x: 300
            y: 150

            QText {
                x: 0
                y: 0
                width: 150
                height: 50
                text: "Port Name:"
                color: "#ffffff"
            }

            QComboBox {
                id: settings_serialport_portname
                objectName: "settings_serialport_portname"
                x: 150
                y: 0
                onComboBoxClicked: setFocus()
                width: 200
                height: 50
                model: ["ttyUSB0", "ttyUSB1", "ttyUSB2", "ttyUSB3"]
                currentValue: AppModel.sensorPortName
                onCurrentIndexChanged: AppModel.sensorPortName = currentValue
            }

            QText {
                x: 0
                y: 70
                width: 150
                height: 50
                text: "Baudrate:"
                color: "#ffffff"
            }

            QComboBox {
                id: settings_serialport_baudrate
                objectName: "settings_serialport_baudrate"
                x: 150
                y: 70
                width: 200
                height: 50
                model: ["4800", "9600", "19200", "38400", "57600", "115200"]
                onComboBoxClicked: setFocus()
                currentValue: String(AppModel.sensorBaudrate)
                onCurrentIndexChanged: AppModel.sensorBaudrate = Number(currentValue)
            }

            QText {
                x: 0
                y: 140
                width: 350
                height: 50
                text: settings_serialport_portname.currentValue === '' ? '' : settings_serialport_portname.currentValue
                                                                         + " " + settings_serialport_baudrate.currentValue
                                                                         + "bps 8, N, 1, None"
                color: "#ffffff"
                font.bold: true
            }

            QButton {
                x: 0
                y: 210
                width: 170
                height: 50
                text: "Test Connection"
                params: [settings_serialport_portname.currentValue, settings_serialport_baudrate.currentValue]
            }

            QButton {
                x: 180
                y: 210
                width: 100
                height: 50
                text: "Save"
                params: [settings_serialport_portname.currentValue, settings_serialport_baudrate.currentValue]
            }
        }
    }
}
