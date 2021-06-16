import QtQuick 2.0

Item {
    property alias text: txtInp.text
    Rectangle {
        anchors.fill: parent
        color: "#000000"
        opacity: 0.5
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: parent.enabled ? "#FFFFFF" : "gray"
        border.width: 2
    }

    TextInput {
        id: txtInp
        anchors.fill: parent
        anchors.margins: 3
        cursorVisible: false
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 20
        color: parent.enabled ? "#FFFFFF" : "gray"
        inputMethodHints: Qt.ImhDigitsOnly
        clip: true 
    }
}
