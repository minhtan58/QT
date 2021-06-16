import QtQuick 2.2
import HMIEvents 1.0
import "../Js/Constants.js" as CONSTANTS

Item {
    width: 150; height: 80
    property string name: ""
    property alias cursorPosition: txtInp.cursorPosition
    property alias cursorVisible: txtInp.cursorVisible
    property alias readOnly: txtInp.readOnly
    property alias text: txtInp.text
    property bool isTextCenter: true

    property bool isFullKey: true

    property int doneEventID: -1
    property string doneEventParams: ""

    signal textValueChanged

    QText {
        text: name
        width: parent.width
        height: 40
        horizontalAlignment: Text.AlignHCenter
        font.family: "Segoe UI"
        font.pixelSize: 20
    }

    Rectangle {
        anchors.fill: txtInp
        color: "#000000"
        opacity: 0.5
    }

    Rectangle {
        anchors.fill: txtInp
        color: "transparent"
        border.color: readOnly ? "gray" : "#FFFFFF"
        border.width: 2
    }

    TextInput {
        id: txtInp
        width: parent.width; height: 40
        y: 40
        anchors.margins: 3
        cursorVisible: false
        horizontalAlignment: isTextCenter ? Text.AlignHCenter : Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 23
        color: readOnly ? "gray" : "#FFFFFF"
        clip: true
        onTextChanged: textValueChanged()
    }

    MouseArea {
        id: mouseTextInput
        anchors.fill: parent
        preventStealing: true
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

