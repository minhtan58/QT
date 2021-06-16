import QtQuick 2.0
import CEMSEnum 1.0

Item {
    objectName: "prt_topbar"
    x: 0
    y: 0
    width: CEMSConstants.screenWidth
    height: CEMSConstants.topbarHeight

    property string stationId: ""
    property string stationName: ""
    property string systemDate: ""
    property string systemTime: ""
    property int alarmCount: 0

    Rectangle {
        x: 10
        y: CEMSConstants.topbarHeight - 1
        z: 1
        width: CEMSConstants.screenWidth - 20
        height: 1
        color: "grey"
    }

    Image {
        x: 0
        y: 0
        width: 70
        height: 68
        source: mouseHome.containsMouse ? "qrc:/resources/Image/home_active.png" : "qrc:/resources/Image/home_inactive.png"

        MouseArea {
            id: mouseHome
            anchors.fill: parent
            onClicked: Delivery.hmiEvent("", CEMSEnum.HMI_BUTTON_HOME, "")
        }
    }

    Image {
        x: 70
        y: 0
        width: 70
        height: 68
        source: "qrc:/resources/Image/settings.png"
        fillMode: Image.Pad
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        Rectangle {
            anchors.fill: parent
            color: "gray"
            opacity: 0.3
            visible: mouseSetting.containsMouse
        }

        MouseArea {
            id: mouseSetting
            anchors.fill: parent
            onClicked: Delivery.hmiEvent("", CEMSEnum.HMI_BUTTON_SETTING, "")
        }
    }

    Image {
        x: 140
        y: 0
        width: 70
        height: 68
        source: "qrc:/resources/Image/history.png"
        fillMode: Image.Pad
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        enabled: false

        Rectangle {
            anchors.fill: parent
            color: "gray"
            opacity: 0.3
            visible: mouseHistory.containsMouse
        }

        MouseArea {
            id: mouseHistory
            anchors.fill: parent
            onClicked: Delivery.hmiEvent("", CEMSEnum.HMI_BUTTON_HISTORY, "")
        }
    }

    Image {
        anchors.top: parent.top
        anchors.right: seperator.left
        width: 70
        height: 68
        source: "qrc:/resources/Image/bell.png"
        fillMode: Image.Pad
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        enabled: false

        Rectangle {
            anchors.fill: parent
            color: "gray"
            opacity: 0.3
            visible: mouseAlarm.containsMouse
        }

        Text {
            text: alarmCount
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 5
            font.pixelSize: 20
            font.bold: true
            color: "#ff0000"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            visible: alarmCount > 0
        }

        MouseArea {
            id: mouseAlarm
            anchors.fill: parent
            onClicked: Delivery.hmiEvent("", CEMSEnum.HMI_BUTTON_BELL, "")
        }
    }

    Text {
        id: sttStationName
        anchors.centerIn: parent
        width: 500
        height: CEMSConstants.topbarHeight
        text: stationName
        font.pixelSize: 30
        font.bold: true
        color: "#FFFFFF"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Rectangle {
        id: seperator
        anchors.right: sttTime.left
        anchors.rightMargin: 10
        width: 1
        height: 40
        y: 15
        visible: sttTime.text !== ''
    }

    Text {
        id: sttTime
        anchors.right: parent.right
        anchors.rightMargin: 20
        height: CEMSConstants.topbarHeight
        text: systemTime
        font.pixelSize: 28
        font.bold: true
        color: "#FFFFFF"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
