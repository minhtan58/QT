import QtQuick 2.0
import CEMSEnum 1.0
import "../Widget"

Item {
    objectName: "scr_settings_serial_port"
    anchors.fill: parent
    property string listSerialPort: ""
    property string currentSerialPort: ""
    onListSerialPortChanged: {
        UIBridge.log("listSerialPort = " + listSerialPort)
        var listPort = listSerialPort.split(",")
        var listModel = []
        if(!listPort.length) {
            return
        }
        for(var idx = 0; idx < listPort.length; idx++)
            listModel.push(listPort[idx])
        UIBridge.log("listModel = " + listModel)
        settings_serialport_portname.model = listModel
        if(contains(listModel, currentSerialPort))
            settings_serialport_portname.currentValue = currentSerialPort
        else
            settings_serialport_portname.currentValue = listModel[0]
    }

    function setFocus() {
        var oldState = this.pressed
        settings_serialport_portname.pressed = false
        settings_serialport_baudrate.pressed = false
        this.pressed = oldState
    }

    function contains(list, element) {
        for(var idx = 0; idx < list.length; idx++)
            if(list[idx] === element)
                return true
        return false
    }

    QLeftTabView {
        currentIndex: 3
    }

    Item {
        x: 210
        y: 10
        width: 580
        height: 390

        Rectangle {
            id: background
            radius: 10
            anchors.fill: parent
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
                text: "Serial Port Settings"
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
            x: 150
            y: 100
            Text {
                x: 0
                y: 0
                width: 120
                height: 40
                text: "Port Name:"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            QComboBox {
                id: settings_serialport_portname
                objectName: "settings_serialport_portname"
                x: 120
                y: 0
                onComboBoxClicked: setFocus()
            }

            Text {
                x: 0
                y: 50
                width: 120
                height: 40
                text: "Baudrate:"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            QComboBox {
                id: settings_serialport_baudrate
                objectName: "settings_serialport_baudrate"
                x: 120
                y: 50
                model: ["4800", "9600", "19200", "38400", "57600", "115200"]
                onComboBoxClicked: setFocus()
            }

            Text {
                x: 0
                y: 100
                width: 350
                height: 40
                text: settings_serialport_portname.currentValue === '' ? '' : settings_serialport_portname.currentValue
                                                                         + " " + settings_serialport_baudrate.currentValue
                                                                         + "bps 8, N, 1, None"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                font.bold: true
                wrapMode: Text.Wrap
            }

            QButton {
                x: 0
                y: 160
                width: 170
                height: 40
                text: "Test Connection"
                eventID: CEMSEnum.HMI_BUTTON_TEST_CONNECTIONS_SERIALPORT
                eventParams: settings_serialport_portname.currentValue + "," +
                             settings_serialport_baudrate.currentValue;
            }

            QButton {
                x: 180
                y: 160
                width: 100
                height: 40
                text: "Save"
                eventID: CEMSEnum.HMI_BUTTON_SAVE_SETTINGS_SERIALPORT
                eventParams: settings_serialport_portname.currentValue + "," +
                             settings_serialport_baudrate.currentValue;
            }
        }
    }
}
