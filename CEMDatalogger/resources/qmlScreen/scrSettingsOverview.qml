import QtQuick 2.0
import CEMSEnum 1.0
import "../Widget"

Item {
    objectName: "scr_settings_overview"
    anchors.fill: parent
    property int gotoDevMode: 0

    onGotoDevModeChanged: {
        if(gotoDevMode == 10)
            UIBridge.hmiEvent("", CEMSEnum.HMI_TAB_SELECT, "development")
    }

    QLeftTabView {
        currentIndex: 0
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
                text: "Overview"
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
            x: 50
            y: 70
            Text {
                x: 0
                y: 0
                width: 150
                height: 40
                text: "Sensors:"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                objectName: "settings_overview_serialport_information"
                x: 150
                y: 0
                width: 250
                height: 40
                text: "COM1,115200,8,N,1"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                objectName: "settings_overview_serialport_status"
                property bool isConnected: false
                x: 400
                y: 0
                width: 150
                height: 40
                text: isConnected ? "Connected" : "Not Connect"
                color: isConnected ? "#00cc00" : "#ff0000"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                x: 0
                y: 50
                width: 150
                height: 40
                text: "Main Server:"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                objectName: "settings_overview_server_address"
                x: 150
                y: 50
                width: 250
                height: 40
                text: "192.168.0.101:11111"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                objectName: "settings_overview_server_status"
                property bool isConnected: false
                x: 400
                y: 50
                width: 150
                height: 40
                text: isConnected ? "Connected" : "Not Connect"
                color: isConnected ? "#00cc00" : "#ff0000"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                x: 0
                y: 100
                width: 150
                height: 40
                text: "FTP Server:"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                objectName: "settings_overview_ftp_address"
                x: 150
                y: 100
                width: 250
                height: 40
                text: "192.168.0.100:22"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                objectName: "settings_overview_ftp_status"
                property bool isConnected: false
                x: 400
                y: 100
                width: 150
                height: 40
                text: isConnected ? "Connected" : "Not Connect"
                color: isConnected ? "#00cc00" : "#ff0000"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                x: 0
                y: 150
                width: 150
                height: 40
                text: "Main Interval:"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                objectName: "settings_overview_server_interval"
                x: 150
                y: 150
                width: 250
                height: 40
                text: "00:05:00"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                x: 0
                y: 200
                width: 150
                height: 40
                text: "FTP Interval:"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            Text {
                objectName: "settings_overview_ftp_interval"
                x: 150
                y: 200
                width: 250
                height: 40
                text: "00:05:00"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }
        }
    }
}
