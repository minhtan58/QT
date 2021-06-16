import QtQuick 2.0
import QtQuick.Controls 1.4
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS

Item {
    objectName: "scr_settings_general"

    function setFocus() {
        var oldState = this.pressed
        settings_telemetry_send_type.pressed = false
        settings_telemetry_controller_type.pressed = false
        this.pressed = oldState
    }

    function getIPPort(server) {
        var ip = '', port = ''
        if(server.contains(':')) {
            ip = server.slice(0, server.indexOf(':'))
            port = server.slice(0, server.indexOf(':'), server.length)
        } else {
            ip = server
        }

        return [ip, port]
    }

    QLeftTabView {
        currentIndex: 4
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


        QTabWidget {
            id: tabs
            anchors.fill: parent

            Item {
                x: 100
                y: 0
                property string title: "Cấu Hình Chung"
                id: grpServer

                QText {
                    x: 50
                    y: 70
                    width: 170
                    text: "Kiểu Truyền:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 23
                    wrapMode: Text.Wrap
                }

                QComboBox {
                    id: settings_telemetry_send_type
                    objectName: "settings_telemetry_send_type"
                    width: 250
                    x: 220
                    y: 70
                    model: ["Internet", "SMS", "Internet/SMS"]
                    onComboBoxClicked: setFocus()
                    currentIndex: AppModel.telemetryGeneralSendType
                    onCurrentIndexChanged: {
                        UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_COMBOBOX_TELEMETRY_SENDTYPE_CHANGED, currentIndex)
                    }
                }

                QText {
                    x: 50
                    y: 140
                    width: 170
                    text: "Điều Khiển:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 23
                    wrapMode: Text.Wrap
                }

                QComboBox {
                    id: settings_telemetry_controller_type
                    objectName: "settings_telemetry_controller_type"
                    width: 250
                    x: 220
                    y: 140
                    model: ["Quan Trắc Viên", "Tự Động"]
                    onComboBoxClicked: setFocus()
                    currentIndex: AppModel.telemetryGeneralControlType
                    onCurrentIndexChanged:
                        UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_COMBOBOX_TELEMETRY_CONTROLTYPE_CHANGED, currentIndex)
                }

                QText {
                    x: 50
                    y: 210
                    width: 170
                    text: "SMS Notify:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 23
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_telemetry_sms_notify
                    objectName: "settings_telemetry_sms_notify"
                    x: 220
                    y: 210
                    width: 250
                    isTextCenter: false
                    text: AppModel.telemetryGeneralSMSNotify
                    doneEventID: HMIEvents.HMI_TEXTINPUT_DONE_TELEMETRY_GENERAL_SMSNOTIFY
                    doneEventParams: text
                    isFullKey: false
                }

                QText {
                    x: 50
                    y: 280
                    width: 170
                    text: "Khoảng Truyền:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 23
                    wrapMode: Text.Wrap
                }

                QSpinBox {
                    id: settings_telemetry_send_interval
                    objectName: "settings_telemetry_send_interval"
                    x: 220
                    y: 280
                    width: 170
                    currentValue: AppModel.telemetryGeneralSendInterval / 60000
                    onSpinClicked: {
                        if(currentValue >= minValue && currentValue <= maxValue)
                            UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_SPINBOX_TELEMETRY_GENERAL_SENDINTERVAL, Number(currentValue) * 60000)
                    }
                }

                QText {
                    x: 410
                    y: 280
                    width: 150
                    text: "phút"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 23
                    wrapMode: Text.Wrap
                }

                QText {
                    x: 50
                    y: 350
                    width: 170
                    text: "Trạng Thái:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 23
                    wrapMode: Text.Wrap
                }
                QText {
                    x: 220
                    y: 350
                    width: 300
                    text: "Bình Thường(Modem)"
                    color: "green"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 25
                    wrapMode: Text.Wrap
                    font.bold: true
                }
            }

            Item {
                x: 150
                y: 100
                property string title: "Cấu Hình Internet"
                id: grpGPRS

                QText {
                    x: 0
                    y: 0
                    width: 150
                    text: "Nhà Mạng:"
                }

                QComboBox {
                    id: settings_telemetry_cell
                    objectName: "settings_telemetry_cell"
                    width: 250
                    x: 150
                    y: 0
                    model: ["Viettel", "Mobifone", "Vinaphone"]
                    onComboBoxClicked: setFocus()
                    currentIndex: AppModel.telemetryInternetNetworkType
                    onCurrentIndexChanged: {
                        UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_COMBOBOX_TELEMETRY_NETWORKTYPE_CHANGED, currentIndex)
                    }
                }

                QText {
                    x: 0
                    y: 70
                    width: 150
                    text: "Truyền Tin:"
                }

                QComboBox {
                    id: settings_telemetry_type
                    objectName: "settings_telemetry_type"
                    width: 250
                    x: 150
                    y: 70
                    model: ["TCP/IP", "FTP", "HTTP"]
                    onComboBoxClicked: setFocus()
                    currentIndex: AppModel.telemetryInternetProtocolType
                    onCurrentIndexChanged: {
                        UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_COMBOBOX_TELEMETRY_PROTOCOLTYPE_CHANGED, currentIndex)
                    }
                }

                QText {
                    x: 0
                    y: 140
                    width: 150
                    text: "Máy Chủ 1:"
                    color: "#ffffff"
                }

                QTextInput {
                    id: settings_telemetry_server1
                    objectName: "settings_telemetry_server1"
                    x: 150
                    y: 140
                    width: 250
                    text: AppModel.telemetryInternetServer1
                    doneEventID: HMIEvents.HMI_TEXTINPUT_DONE_TELEMETRY_INTERNET_SERVER1
                    doneEventParams: text
                    isFullKey: false
                    isTextCenter: false
                }

                QText {
                    x: 0
                    y: 210
                    width: 150
                    text: "Máy Chủ 2:"
                    color: "#ffffff"
                }

                QTextInput {
                    id: settings_telemetry_server2
                    objectName: "settings_telemetry_server2"
                    x: 150
                    y: 210
                    width: 250
                    text: AppModel.telemetryInternetServer2
                    doneEventID: HMIEvents.HMI_TEXTINPUT_DONE_TELEMETRY_INTERNET_SERVER2
                    doneEventParams: text
                    isFullKey: false
                    isTextCenter: false
                }
            }

            Item {
                x: 150
                y: 100
                property string title: "Cấu Hình SMS"
                id: grpGSM

                QText {
                    x: 0
                    y: 0
                    width: 200
                    text: "Số Trung Tâm:"
                    color: "#ffffff"
                }

                QTextInput {
                    id: settings_telemetry_
                    objectName: "settings_telemetry_"
                    x: 220
                    y: 0
                    width: 250
                }

                QText {
                    x: 0
                    y: 70
                    width: 200
                    text: "Chế Độ Thông Báo:"
                    color: "#ffffff"
                }

                QTextInput {
                    id: settings_telemetry
                    objectName: "settings_telemetry_server1"
                    x: 220
                    y: 70
                    width: 250
                }
                QText {
                    x: 0
                    y: 140
                    width: 200
                    text: "Nhận Thông Báo 1:"
                    color: "#ffffff"
                }

                QTextInput {
                    objectName: "settings_telemetry_server1"
                    x: 220
                    y: 140
                    width: 250
                }

                QText {
                    x: 0
                    y: 210
                    width: 200
                    text: "Nhận Thông Báo 2:"
                    color: "#ffffff"
                }

                QTextInput {
                    x: 220
                    y: 210
                    width: 250
                }
            }
        }
    }
}
