import QtQuick 2.0
import QtQuick.Controls 1.4
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS

Item {
    objectName: "scr_settings_general"

    function setVisiblesCursor(isShow) {
        settings_general_station_id.cursorVisible = false
        settings_general_station_name.cursorVisible = false
        this.cursorVisible = isShow
    }

    QLeftTabView {
        currentIndex: 6
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
                text: "Data"
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

            QText {
                x: 150
                y: 0
                width: 170
                height: 45
                text: "Tần suất dữ liệu"
                color: "#ffffff"
                wrapMode: Text.Wrap
            }

            QSpinBox {
                id: settings_data_request_interval
                objectName: "settings_data_request_interval"
                x: 350
                y: 0
                width: 170
                currentValue: AppModel.dataSendAutomaticRequestInterval / 1000
                onSpinClicked: {
                    UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_SPINBOX_SENSOR_INTERVAL, currentValue * 1000)
                }
            }

            QText {
                x: 540
                y: 0
                width: 170
                height: 45
                text: "giây"
                color: "#ffffff"
                wrapMode: Text.Wrap
            }

            QText {
                x: 150
                y: 70
                width: 170
                height: 45
                text: "Hệ Số Slope"
                color: "#ffffff"
                wrapMode: Text.Wrap
            }

            QComboBox {
                id: settings_data_slope
                x: 350
                y: 70
                width: 170
                model: ["0.1", "0.2", "0.5"]
                currentValue: AppModel.dataSlope
                onCurrentValueChanged: AppModel.dataSlope = currentValue
            }

        }
    }
}
