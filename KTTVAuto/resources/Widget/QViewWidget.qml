import QtQuick 2.0

Item {
    property string textValue: ""
    property alias textName: txtName.text
    property alias textUnit: txtUnit.text
    property string isAlarmOn: "0"
    width: 385
    height: 73
//    enabled: false

    signal viewClicked
    signal viewPressAndHold

    Rectangle {
        id: rect
        anchors.fill: parent
        color: isAlarmOn === "1" ? "#ff0000" : "#6a9bc3"
        opacity: viewArea.containsMouse ? 0.7 : (isAlarmOn === "1" ? 0.5 : 0.15)
//        gradient: Gradient {
//            GradientStop { position: 0.0; color: "#1c3448" }
//            GradientStop { position: 0.4; color: "#6a9bc3" }
//            GradientStop { position: 0.6; color: "#6a9bc3" }
//            GradientStop { position: 1.0; color: "#1c3448" }
//        }
    }

    Text {
        id: txtValue
        x: 0
        y: 0
        text: textValue.length ? textValue : "--"
        width: parent.width * 7/10
        height: parent.height
        font.pixelSize: 55
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "#FFFFFF"
        elide: Text.ElideRight
    }

    Text {
        id: txtName
        x: txtValue.width
        y: 0
        width: parent.width - txtValue.width
        height: parent.height / 2
        font.pixelSize: 23
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        color: "#FFFFFF"
        elide: Text.ElideRight
    }

    Text {
        id: txtUnit
        x: txtValue.width
        y: txtName.height
        width: parent.width - txtValue.width
        height: parent.height / 2
        font.pixelSize: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        color: "#FFFFFF"
        elide: Text.ElideRight
    }

    MouseArea {
        id: viewArea
        anchors.fill: parent
        onClicked: viewClicked()
        onPressAndHold: viewPressAndHold()
    }
}

