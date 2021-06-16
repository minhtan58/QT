import QtQuick 2.0
import QtQuick.Controls 1.4
import CEMSEnum 1.0
import "../Widget"

Item {
    objectName: "scr_settings_general"
    anchors.fill: parent

    property int isAutoUpdateTime: 0

    onIsAutoUpdateTimeChanged: Delivery.log("onIsAutoUpdateTimeChanged: " + isAutoUpdateTime)

    function setVisiblesCursor(isShow) {
        settings_general_station_id.cursorVisible = false
        settings_general_station_name.cursorVisible = false
        settings_general_r.cursorVisible = false
        this.cursorVisible = isShow
    }

    QLeftTabView {
        currentIndex: 1
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

        QTabWidget {
            id: tabs
            anchors.fill: parent

            Item {
                property string title: "Station Settings"
                id: grpSystem
                x: 50
                y: 20

                Text {
                    x: 50
                    y: 0
                    width: 150
                    height: 40
                    text: "Station ID:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_general_station_id
                    objectName: "settings_general_station_id"
                    x: 200
                    y: 0
                    text: CEMSConstants.stationId
                    width: 250
                    height: 40
                    isFullKey: true
                    onTextInputClicked: setVisiblesCursor(true)
                    doneEventID: CEMSEnum.HMI_TEXTINPUT_DONE_STATION_ID
                }

                Text {
                    x: 50
                    y: 50
                    width: 150
                    height: 40
                    text: "Station Name:"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_general_station_name
                    objectName: "settings_general_station_name"
                    x: 200
                    y: 50
                    text: CEMSConstants.stationName
                    width: 250
                    height: 40
                    isFullKey: true
                    onTextInputClicked: setVisiblesCursor(true)
                    doneEventID: CEMSEnum.HMI_TEXTINPUT_DONE_STATION_NAME
                }

                Rectangle {
                    x: 20
                    y: 150
                    width: 450
                    height: 2
                    color: "#FFFFFF"
                }

                Text {
                    x: 50
                    y: 170
                    width: 450
                    height: 40
                    text: "Flow(m\u00B3/s) = Velocity × πr\u00B2"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                Text {
                    x: 50
                    y: 220
                    width: 150
                    height: 40
                    text: "Radius(r):"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QTextInput {
                    id: settings_general_r
                    objectName: "settings_general_r"
                    x: 200
                    y: 220
                    text: CEMSConstants.stationName
                    width: 200
                    height: 40
                    onTextInputClicked: setVisiblesCursor(true)
                    doneEventID: CEMSEnum.HMI_BUTTON_SET_RADIUS
                }
                Text {
                    x: 410
                    y: 220
                    width: 100
                    height: 40
                    text: "meter"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }
            }

            Item {
                property string title: "Time Settings"
                x: 50
                y: 20

                Text {
                    x: 0
                    y: 0
                    width: 350
                    height: 40
                    text: "Automatic Update Internet Time"
                    color: "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QSwitch {
                    x: 350
                    y: 3
                    width: 100
                    height: 35
                    checked: isAutoUpdateTime === 1
                    onSwitchClicked: {
                        Delivery.hmiEvent(this.objectName, CEMSEnum.HMI_SWITCH_UPDATE_TIME_AUTOMATIC, isAutoUpdateTime)
                    }
                }

                Text {
                    x: 0
                    y: 50
                    width: 130
                    height: 40
                    text: "Hour(s)"
                    color: !isAutoUpdateTime ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                Text {
                    x: 160
                    y: 50
                    width: 130
                    height: 40
                    text: "Minute(s)"
                    color: !isAutoUpdateTime ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QSpinBox {
                    id: spinHour
                    objectName: "spinHour"
                    enabled: !isAutoUpdateTime
                    x: 0
                    y: 100
                    width: 130
                    minValue: 0
                    maxValue: 23
                }

                QSpinBox {
                    id: spinMinute
                    objectName: "spinMinute"
                    enabled: !isAutoUpdateTime
                    x: 160
                    y: 100
                    width: 130
                    minValue: 0
                    maxValue: 59
                }

                Text {
                    x: 0
                    y: 150
                    width: 130
                    height: 40
                    text: "Day(s)"
                    color: !isAutoUpdateTime ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                Text {
                    x: 160
                    y: 150
                    width: 130
                    height: 40
                    text: "Month(s)"
                    color: !isAutoUpdateTime ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                Text {
                    x: 320
                    y: 150
                    width: 170
                    height: 40
                    text: "Year(s)"
                    color: !isAutoUpdateTime ? "#FFFFFF" : "gray"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                }

                QSpinBox {
                    id: spinDay
                    objectName: "spinDay"
                    enabled: !isAutoUpdateTime
                    x: 0
                    y: 200
                    width: 120
                    minValue: 1
                    maxValue: parent.getMaxDay(spinMonth.currentValue, spinYear.currentValue)
                }

                QSpinBox {
                    id: spinMonth
                    objectName: "spinMonth"
                    enabled: !isAutoUpdateTime
                    x: 160
                    y: 200
                    width: 130
                    minValue: 1
                    maxValue: 12
                }

                QSpinBox {
                    id: spinYear
                    objectName: "spinYear"
                    enabled: !isAutoUpdateTime
                    x: 320
                    y: 200
                    width: 170
                    currentValue: 2018
                    minValue: 1970
                    maxValue: 2100
                }

                QButton {
                    x: 390
                    y: 270
                    width: 100
                    height: 40
                    text: "Set"
                    isEnabled: !isAutoUpdateTime
                    eventID: CEMSEnum.HMI_BUTTON_SET_DATE_TIME
                    eventParams: spinYear.currentValue + "," + spinMonth.currentValue + "," + spinDay.currentValue + "," + spinHour.currentValue + "," + spinMinute.currentValue
                }

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
                    case 2:
                        if(year%4 == 0 && year % 100 != 0 || year%400 == 0)
                            return 29
                        else
                            return 28
                    default:
                        return 30
                    }
                }
            }
        }
    }
}
