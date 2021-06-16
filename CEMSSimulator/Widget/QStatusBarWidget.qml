import QtQuick 2.0

Item {
    property alias textContent: txtContent.text
    Rectangle {
        anchors.fill: parent
        border.color: "gray"
        border.width: 2

        Text {
            id: txtContent
            anchors.fill: parent
            anchors.centerIn: parent
            text: qsTr("Text")
            font.pixelSize: 23
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}

