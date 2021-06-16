import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS

Item {
    objectName: "scr_settings_network"

    QLeftTabView {
        currentIndex: 2
    }

    Item {
        x: CONSTANTS.LEFT_TAB_WIDTH + 5
        y: 10
        width: CONSTANTS.SCREEN_WIDTH - x - 5
        height: CONSTANTS.APP_HEIGHT - 20

        Rectangle {
            anchors.fill: parent
            radius: 10
//            color: "#315b7d"
            opacity: 0.3
            gradient: Gradient {
                GradientStop { position: 0.0; color: "steelblue" }
                GradientStop { position: 1.0; color: "#1c3448" }
            }
        }

        QTabWidget {
            id: tabs
            anchors.fill: parent
            Item {
                property string title: "Main Server Settings"
                id: grpServer
                x: 100
                y: 50
                Text {
                    x: 0
                    y: 0
                    width: 100
                    height: 40
                    text: "Host IP:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_network_server_ip
                    objectName: "settings_network_server_ip"
                    x: 100
                    y: 0
                    width: 200
                    height: 40
                }

                Text {
                    x: 0
                    y: 50
                    width: 100
                    height: 40
                    text: "Port:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_network_server_port
                    objectName: "settings_network_server_port"
                    x: 100
                    y: 50
                    width: 200
                    height: 40
                }

                Text {
                    x: 0
                    y: 100
                    width: 150
                    height: 40
                    text: "Send Interval:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QSpinBox {
                    id: settings_network_server_interval
                    objectName: "settings_network_server_interval"
                    x: 150
                    y: 100
                }

                Text {
                    x: 300
                    y: 100
                    width: 100
                    height: 40
                    text: "minute(s)"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QButton {
                    x: 20
                    y: 160
                    width: 170
                    height: 40
                    text: "Test Connection"
                    eventID: HMIEvents.HMI_BUTTON_TEST_CONNECTIONS_NETWORK_SERVER
                    params: [settings_network_server_ip.text, settings_network_server_port.text]
                }

                QButton {
                    x: 200
                    y: 160
                    width: 100
                    height: 40
                    text: "Save"
                    eventID: HMIEvents.HMI_BUTTON_SAVE_SETTINGS_NETWORK_SERVER
                    params: [
                        settings_network_server_ip.text,
                        settings_network_server_port.text,
                        settings_network_server_interval.currentValue * 60000
                    ]
                }
            }

            //-------------------------------------------------------------------------
            Item {
                property string title: "FTP Settings"
                x: 100
                y: 20

                Text {
                    x: 0
                    y: 0
                    width: 100
                    height: 40
                    text: "User:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_network_ftp_user
                    objectName: "settings_network_ftp_user"
                    x: 100
                    y: 0
                    width: 250
                    height: 40
                    isFullKey: true
                }

                Text {
                    x: 0
                    y: 50
                    width: 100
                    height: 40
                    text: "Password:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_network_ftp_password
                    objectName: "settings_network_ftp_password"
                    x: 100
                    y: 50
                    width: 250
                    height: 40
                    isFullKey: true
                }

                Text {
                    x: 0
                    y: 100
                    width: 100
                    height: 40
                    text: "Host IP:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_network_ftp_ip
                    objectName: "settings_network_ftp_ip"
                    x: 100
                    y: 100
                    width: 250
                    height: 40
                }

                Text {
                    x: 0
                    y: 150
                    width: 100
                    height: 40
                    text: "Port:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_network_ftp_port
                    objectName: "settings_network_ftp_port"
                    x: 100
                    y: 150
                    width: 250
                    height: 40
                }

                Text {
                    x: 0
                    y: 200
                    width: 150
                    height: 40
                    text: "Send Interval:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QSpinBox {
                    id: settings_network_ftp_interval
                    objectName: "settings_network_ftp_interval"
                    x: 200
                    y: 200
                }

                Text {
                    x: 370
                    y: 200
                    width: 100
                    height: 40
                    text: "minute(s)"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QButton {
                    x: 70
                    y: 260
                    width: 170
                    height: 40
                    text: "Test Connection"
                    enabled: false
                    eventID: HMIEvents.HMI_BUTTON_TEST_CONNECTIONS_NETWORK_FTP
                    params: [
                        settings_network_ftp_ip.text,
                        settings_network_ftp_port.text,
                        settings_network_ftp_user.text,
                        settings_network_ftp_password.text
                    ]
                }

                QButton {
                    x: 250
                    y: 260
                    width: 100
                    height: 40
                    text: "Save"
                    eventID: HMIEvents.HMI_BUTTON_SAVE_SETTINGS_NETWORK_FTP
                    params: [
                        settings_network_ftp_ip.text,
                        settings_network_ftp_port.text,
                        settings_network_ftp_user.text,
                        settings_network_ftp_password.text,
                        settings_network_ftp_interval.currentValue * 60000
                    ]
                }
            }
        }
    }
}
