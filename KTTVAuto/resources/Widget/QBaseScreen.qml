import QtQuick 2.2

Item {
    id: root
    width: 50
    height: 30
    property int eventID: -1
    property string eventParams: ""
    property alias source: imgbtn.source
    property alias background: background.color
    property alias text: txtContent.text

    signal buttonClicked

    Rectangle {
        id: background
        anchors.fill: parent
        border.color: parent.enabled ? "#FFFFFF" : "#2c2c2e"
        border.width: 1
        color: mouseBtn.containsMouse ? "#2c2c2e" : "#000000"
    }

    Image {
        id: imgbtn
        anchors.centerIn: parent
        width: 70
        height: 70
        z: 5
    }

    Text {
        id: txtContent
        anchors.centerIn: parent
        wrapMode: Text.WordWrap
        color: parent.enabled ? "#FFFFFF" : "#2c2c2e"
        font.pixelSize: 20
    }

    MouseArea {
        id: mouseBtn
        anchors.fill: parent
        onClicked: {
            buttonClicked()
            if(eventID !== -1)
                UIBridge.hmiEvent(this.objectName, eventID, eventParams)
        }
    }
}

