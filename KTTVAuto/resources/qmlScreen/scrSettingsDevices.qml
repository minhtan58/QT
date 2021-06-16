import QtQuick 2.0
import QtQuick.Controls 1.4
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS
import "../Js/Translations.js" as TRANS

Item {
    objectName: "scr_settings_devices"

    function getMaxDay(month, year) {
        switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31
        case 4:
        case 6:
        case 9:
        case 11:
            return 30
        case 2:
            if(year%4 == 0 && year % 100 != 0 || year%400 == 0) {
                return 29
            } else {
                return 28
            }
        default:
            return 30
        }
    }

    QLeftTabView {
        currentIndex: 1
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
                property string title: TRANS.STR_DEVICE_TAB_DEVICE
                id: grpSystem
                x: 150
                y: 50

                QText {
                    x: 50
                    y: 0
                    width: 170
                    height: 45
                    text: TRANS.STR_DEVICE_CODE
                    color: "#ffffff"
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_device_code
                    objectName: "settings_device_code"
                    x: 220
                    y: 0
                    text: AppModel.deviceCode
                    width: 300
                    isFullKey: true
                    doneEventID: HMIEvents.HMI_TEXTINPUT_DONE_DEVICE_CODE
                    doneEventParams: text
                }

                QText {
                    x: 50
                    y: 70
                    width: 170
                    height: 45
                    text: TRANS.STR_DEVICE_NAME
                    color: "#ffffff"
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_device_name
                    objectName: "settings_device_name"
                    x: 220
                    y: 70
                    text: AppModel.deviceName
                    width: 300
                    isFullKey: true
                    doneEventID: HMIEvents.HMI_TEXTINPUT_DONE_DEVICE_NAME
                    doneEventParams: text
                }

                QText {
                    x: 50
                    y: 140
                    width: 170
                    height: 45
                    text: TRANS.STR_DEVICE_LOCATION
                    color: "#ffffff"
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_device_location
                    objectName: "settings_device_location"
                    x: 220
                    y: 140
                    text: AppModel.deviceLocation
                    width: 300
                    isFullKey: true
                    doneEventID: HMIEvents.HMI_TEXTINPUT_DONE_DEVICE_LOCATION
                    doneEventParams: text
                }

                QText {
                    x: 50
                    y: 210
                    width: 170
                    height: 45
                    text: "Nhóm"
                }

                QComboBox {
                    id: combobox_settings_alarm_air_component
                    x: 220
                    y: 210
                    width: 300
                    model: ["Khí Tượng", "Thủy Văn", "Hải Văn"]
                    currentIndex: AppModel.deviceType
                    onCurrentIndexChanged: {
                        AppModel.deviceType = currentIndex
                        UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_COMBOBOX_DEVICETYPE_CHANGED, currentIndex)
                    }
                }
            }

            Item {
                property string title: TRANS.STR_DEVICE_TAB_TIME
                x: 150; y: 50

                QText {
                    width: 550
                    text: TRANS.STR_DEVICE_SYSTEMTIME_AUTOMATIC_UPDATE_INTERNET
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 25
                }

                QSwitch {
                    x: 560; y: 3
                    width: 120; height: 40
                    checked: AppModel.isSystemTimeAutoUpdate
                    onSwitchClicked: {
                        UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_SWITCH_UPDATE_TIME_AUTOMATIC, !checked ? "1" : "0")
                    }
                }

                QText {
                    x: spinHour.x
                    y: spinHour.y - 50
                    width: spinHour.width
                    text: TRANS.STR_DEVICE_HOUR
                    color: !AppModel.isSystemTimeAutoUpdate ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.Wrap
                }

                QText {
                    x: spinMinute.x
                    y: spinMinute.y - 50
                    width: spinMinute.width
                    text: TRANS.STR_DEVICE_MINUTE
                    color: !AppModel.isSystemTimeAutoUpdate ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                QSpinBox {
                    id: spinHour
                    enabled: !AppModel.isSystemTimeAutoUpdate
                    currentValue: AppModel.systemHour
                    x: 0
                    y: 120
                    width: 200
                    height: 50
                    textSize: 25
                    minValue: 0
                    maxValue: 23
                }

                QSpinBox {
                    id: spinMinute
                    currentValue: AppModel.systemMinute
                    enabled: !AppModel.isSystemTimeAutoUpdate
                    x: 250
                    y: 120
                    width: 200
                    height: 50
                    textSize: 25
                    minValue: 0
                    maxValue: 59
                }

                QText {
                    x: spinDay.x
                    y: spinDay.y - 50
                    width: spinDay.width
                    text: TRANS.STR_DEVICE_DAY
                    color: !AppModel.isSystemTimeAutoUpdate ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                QText {
                    x: spinMonth.x
                    y: spinMonth.y - 50
                    width: spinMonth.width
                    text: TRANS.STR_DEVICE_MONTH
                    color: !AppModel.isSystemTimeAutoUpdate ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                QText {
                    x: spinYear.x
                    y: spinYear.y - 50
                    width: spinYear.width
                    text: TRANS.STR_DEVICE_YEAR
                    color: !AppModel.isSystemTimeAutoUpdate ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                QSpinBox {
                    id: spinDay
                    currentValue: AppModel.systemDay
                    enabled: !AppModel.isSystemTimeAutoUpdate
                    x: 0
                    y: 240
                    width: 200
                    height: 50
                    textSize: 25
                    minValue: 1
                    maxValue: getMaxDay(spinMonth.currentValue, spinYear.currentValue)
                }

                QSpinBox {
                    id: spinMonth
                    currentValue: AppModel.systemMonth
                    enabled: !AppModel.isSystemTimeAutoUpdate
                    x: 250
                    y: 240
                    width: 200
                    height: 50
                    textSize: 25
                    minValue: 1
                    maxValue: 12
                }

                QSpinBox {
                    id: spinYear
                    currentValue: AppModel.systemYear
                    enabled: !AppModel.isSystemTimeAutoUpdate
                    x: 500
                    y: 240
                    width: 200
                    height: 50
                    textSize: 25
                    minValue: 1970
                    maxValue: 2100
                }

                QButton {
                    x: 550
                    y: 320
                    width: 150
                    height: 50
                    border.width: 2
                    font.pixelSize: 25
                    text: TRANS.STR_DEVICE_SET_TIME
                    enabled: !AppModel.isSystemTimeAutoUpdate
                    eventID: HMIEvents.HMI_BUTTON_SET_DATE_TIME
                    params: [
                        spinYear.currentValue,
                        spinMonth.currentValue,
                        spinDay.currentValue,
                        spinHour.currentValue,
                        spinMinute.currentValue
                    ]
                }
            }
        }
    }
}
