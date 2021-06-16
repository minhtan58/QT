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
        currentIndex: 5
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
                text: "Định Vị"
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
            x: 0
            y: 0

            QText {
                x: 150
                y: 150
                width: 150
                height: 40
                text: "Trạng Thái:"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
            }

            QText {
                x: 300
                y: 150
                width: 300
                height: 40
                text: "Không Có Tín Hiệu"
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
                font.bold: true
            }

//            QSwitch {
//                x: 400
//                y: 150
//                width: 120
//                height: 40
//                checked: true
//                onSwitchClicked: {
//                    AppModel.isSystemTimeAutoUpdate = !AppModel.isSystemTimeAutoUpdate
//                }
//            }

            QText {
                x: 150
                y: 200
                width: 150
                height: 40
                text: "Kinh Độ: "
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
            }

            QText {
                x: 300
                y: 200
                width: 300
                height: 40
                text: AppModel.gpsLongtitude
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
                font.bold: true
            }

            QText {
                x: 150
                y: 250
                width: 150
                height: 40
                text: "Vĩ Độ: "
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
            }

            QText {
                x: 300
                y: 250
                width: 300
                height: 40
                text: AppModel.gpsLatitude
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
                font.bold: true
            }

            QText {
                x: 150
                y: 300
                width: 150
                height: 40
                text: "Giờ GPS: "
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
            }

            QText {
                x: 300
                y: 300
                width: 300
                height: 40
                text: AppModel.gpsTime
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
                font.bold: true
            }

            QText {
                x: 150
                y: 350
                width: 150
                height: 40
                text: "Ngày GPS: "
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
            }

            QText {
                x: 300
                y: 350
                width: 300
                height: 40
                text: AppModel.gpsDate
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 25
                font.bold: true
            }
        }
    }
}
