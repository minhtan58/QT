import QtQuick 2.0
import CEMSEnum 1.0
import "../Widget"

Item {
    objectName: "scr_settings_network"
    anchors.fill: parent

    function setVisiblesCursor() {
        settings_network_server_ip.cursorVisible = false
        settings_network_server_port.cursorVisible = false
        settings_network_ftp_ip.cursorVisible = false
        settings_network_ftp_port.cursorVisible = false
        settings_network_ftp_user.cursorVisible = false
        settings_network_ftp_password.cursorVisible = false
        this.cursorVisible = true
    }

    QLeftTabView {
        currentIndex: 2
    }

    Item {
        x: 210
        y: 10
        width: 580
        height: 390

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
                    onTextInputClicked: {
                        setVisiblesCursor()
                    }
                    doneEventID: CEMSEnum.HMI_TEXTINPUT_DONE_SERVER_IP
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
                    onTextInputClicked: {
                        setVisiblesCursor()
                    }
                    doneEventID: CEMSEnum.HMI_TEXTINPUT_DONE_SERVER_PORT
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
                    onSpinClicked: {
                        if(currentValue >= minValue && currentValue <= maxValue)
                            UIBridge.hmiEvent(this.objectName, CEMSEnum.HMI_SPINBOX_CHANGE_SERVER_INTERVAL, (Number(currentValue) * 60000))
                    }
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
                    x: 100
                    y: 160
                    width: 200
                    height: 40
                    text: "Test Connection"
                    isEnabled: settings_network_server_ip.text.length > 0 && settings_network_server_port.text > 0
                    eventID: CEMSEnum.HMI_BUTTON_TEST_CONNECTIONS_NETWORK_SERVER
                    eventParams: settings_network_server_ip.text + "," +
                                 settings_network_server_port.text;
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
                    onTextInputClicked: {
                        setVisiblesCursor()
                    }
                    doneEventID: CEMSEnum.HMI_TEXTINPUT_DONE_FTP_USERNAME
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
                    onTextInputClicked: {
                        setVisiblesCursor()
                    }
                    doneEventID: CEMSEnum.HMI_TEXTINPUT_DONE_FTP_PASSWORD
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
                    onTextInputClicked: {
                        setVisiblesCursor()
                    }
                    doneEventID: CEMSEnum.HMI_TEXTINPUT_DONE_FTP_IP
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
                    onTextInputClicked: {
                        setVisiblesCursor()
                    }
                    doneEventID: CEMSEnum.HMI_TEXTINPUT_DONE_FTP_PORT
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
                    onSpinClicked: {
                        if(currentValue >= minValue && currentValue <= maxValue)
                            UIBridge.hmiEvent(this.objectName, CEMSEnum.HMI_SPINBOX_CHANGE_FTP_INTERVAL, (Number(currentValue) * 60000))
                    }
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
                    x: 100
                    y: 260
                    width: 250
                    height: 40
                    text: "Test Connection"
//                    isEnabled: false
                    eventID: CEMSEnum.HMI_BUTTON_TEST_CONNECTIONS_NETWORK_FTP
                    eventParams: settings_network_ftp_ip.text + "," +
                                 settings_network_ftp_port.text + "," +
                                 settings_network_ftp_user.text + "," +
                                 settings_network_ftp_password.text;
                }
            }
        }
    }
}
