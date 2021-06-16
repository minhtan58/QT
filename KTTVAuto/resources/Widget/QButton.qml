import QtQuick 2.0

Item {
    id: root
    width: 50
    height: 30
    property int eventID: -1
    property var params: []
    property alias source: imgbtn.source
    property alias background: background.color
    property alias text: txtContent.text
    property alias font: txtContent.font
    property alias border: background.border

    signal buttonClicked

    function createEventParams(paramsList) {
        var paramStr = "";
        if (paramsList.length >= 1) {
            for(var i = 0; i < paramsList.length - 1; i++) {
                paramStr += paramsList[i] + "";
            }
            paramStr += paramsList[paramsList.length - 1];
        }
        return paramStr;
    }

    Rectangle {
        id: background
        anchors.fill: parent
        border.color: parent.enabled ? "#FFFFFF" : "gray"
        border.width: 1
        color: mouseBtn.containsMouse ? "gray" : "#000000"
    }

    Image {
        id: imgbtn
        anchors.centerIn: parent
        width: 70
        height: 70
        z: 5
    }

    QText {
        id: txtContent
        anchors.centerIn: parent
        color: parent.enabled ? "#FFFFFF" : "#2c2c2e"
        font.pixelSize: 20
    }

    MouseArea {
        id: mouseBtn
        anchors.fill: parent
        onClicked: {
            buttonClicked()
            if(eventID !== -1) {
                UIBridge.hmiEvent(this.objectName, eventID, createEventParams(params))
            }
        }
    }
}

