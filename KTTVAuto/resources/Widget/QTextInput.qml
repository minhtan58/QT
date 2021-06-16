import QtQuick 2.0
import HMIEvents 1.0

Item {
    height: 45
    property alias cursorPosition: txtInp.cursorPosition
    property alias cursorVisible: txtInp.cursorVisible
    property alias readOnly: txtInp.readOnly
    property alias text: txtInp.text
    property bool isTextCenter: true
    property alias echoMode: txtInp.echoMode
    property alias textInputEnabled: txtInp.enabled

    property alias font: txtInp.font

    property bool isFullKey: true

    property int doneEventID: -1
    property string doneEventParams: ""

    Rectangle {
        anchors.fill: parent
        color: "#000000"
        opacity: 0.5
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: readOnly ? "gray" : "#FFFFFF"
        border.width: 2
    }

    TextInput {
        id: txtInp
        anchors.fill: parent
        anchors.margins: 10
        cursorVisible: false
        horizontalAlignment: isTextCenter ? Text.AlignHCenter : Text.AlignLeft
        verticalAlignment: isTextCenter ? Text.AlignVCenter : Text.AlignTop
        font.pixelSize: 23
        color: readOnly ? "gray" : "#FFFFFF"
        clip: true
    }

    MouseArea {
        id: mouseTextInput
        anchors.fill: parent
        enabled: textInputEnabled
        onPressed: {
            if(!readOnly)
                UIBridge.hmiEvent(parent.objectName, HMIEvents.HMI_TEXTINPUT_FOCUS_CHANGED, isFullKey ? "1" : "0")
            mouse.accepted = false
        }
        onClicked: mouse.accepted = false
        onReleased: mouse.accepted = false
        onDoubleClicked: mouse.accepted = false
        onPositionChanged: mouse.accepted = false
        onPressAndHold: mouse.accepted = false
    }

    function doneInput() {
        if(doneEventID != -1)
            UIBridge.hmiEvent(this.objectName, doneEventID, doneEventParams)
    }
}
