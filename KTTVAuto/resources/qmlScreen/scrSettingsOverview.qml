import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS

Item {
    objectName: "scr_settings_overview"
    property int gotoDevMode: 0

    property int margin: 170
    property int spacing: 60

    onGotoDevModeChanged: {
        if(gotoDevMode == 10)
            UIBridge.hmiEvent("", HMIEvents.HMI_TAB_SELECT, "development")
    }

    QLeftTabView {
        currentIndex: 0
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

            QText {
                anchors.fill: parent
                text: "Tổng Quan"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: CONSTANTS.FONT_SEGOE_UI
                font.bold: true
                font.pixelSize: 20
                wrapMode: Text.Wrap
            }

            MouseArea {
                anchors.fill: parent
                onClicked: gotoDevMode++
            }
        }

        Item {
            x: 150
            y: 100

            QText {
                x: 0
                y: 0
                width: margin
                text: "Đăng Nhập:"
                color: "#ffffff"
            }

            QText {
                objectName: "settings_overview_account"
                x: margin
                y: 0
                width: 250
                text: AppModel.userAccount
            }

            QText {
                x: 0
                y: spacing
                width: margin
                text: "Mã Trạm:"
            }

            QText {
                objectName: "settings_overview_device_code"
                x: margin
                y: spacing
                width: 250
                text: AppModel.deviceCode
            }

            QText {
                x: 0
                y: spacing*2
                width: margin
                text: "Tên Trạm:"
            }

            QText {
                objectName: "settings_overview_device_name"
                x: margin
                y: spacing*2
                width: 250
                text: AppModel.deviceName
            }

            QText {
                x: 0
                y: spacing*3
                width: margin
                text: "Nhóm:"
            }

            QText {
                objectName: "settings_overview_device_type"
                x: margin
                y: spacing*3
                width: 250
                text: "Khí Tượng"
            }

            QText {
                x: 0
                y: spacing*4
                width: margin
                text: "Chế Độ:"
            }

            QText {
                objectName: "settings_overview_device_mode"
                x: margin
                y: spacing*4
                width: 250
                text: "Quan Trắc Viên"
            }

            QText {
                x: 0
                y: spacing*5
                width: margin
                text: "Định Vị:"
            }

            QText {
                objectName: "settings_overview_position"
                x: margin
                y: spacing*5
                width: 250
                text: "Cho Phép"
            }

            QText {
                x: 0
                y: spacing*6
                width: margin
                text: "Cảnh Báo:"
            }

            QText {
                objectName: "settings_overview_position"
                x: margin
                y: spacing*6
                width: 250
                height: 40
                text: "Không"
            }
        }
    }
}
