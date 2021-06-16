import QtQuick 2.0
import HMIEvents 1.0

Item {
    height: 45
    property alias iconSrc: icon.source
    property alias cursorPosition: txtInp.cursorPosition
    property alias cursorVisible: txtInp.cursorVisible
    property alias readOnly: txtInp.readOnly
    property alias text: txtInp.text
    property bool isTextCenter: true
    property alias echoMode: txtInp.echoMode
    property alias verticalAlignment: txtInp.verticalAlignment

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

    Rectangle {
        id: rectIcon
        y: 2
        width: parent.height - 4
        height: parent.height - 4
        anchors.left: parent.left
        anchors.margins: 2
        border.color: readOnly ? "gray" : "#FFFFFF"
        border.width: 2
        Image {
            id: icon
            width: 40
            height: 40
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
        }
    }

    TextInput {
        id: txtInp
        anchors.left: rectIcon.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 3
        anchors.leftMargin: 10
        cursorVisible: false
        horizontalAlignment: isTextCenter ? Text.AlignHCenter : Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 23
        color: readOnly ? "gray" : "#FFFFFF"
        clip: true 
    }

    MouseArea {
        id: mouseTextInput
        anchors.fill: parent
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
