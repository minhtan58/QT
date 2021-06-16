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
    property alias verticalAlignment: txtInp.verticalAlignment
    property string placeholderText: ""
    property alias font: txtInp.font
    property alias textInputEnabled: txtInp.enabled

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
        width: visible ? parent.height - 4 : 0
        height: parent.height - 4
        anchors.left: parent.left
        anchors.margins: 2
        border.color: readOnly ? "gray" : "#FFFFFF"
        border.width: 2
        visible: icon.source != ""
        Image {
            id: icon
            width: 40
            height: 40
            anchors.centerIn: parent
            source: ""
            fillMode: Image.PreserveAspectFit
        }
    }

    TextInput {
        id: txtInp
        anchors.left: rectIcon.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: rectShowPasswd.left
        anchors.margins: 3
        anchors.leftMargin: 10
        cursorVisible: false
        echoMode: mouseShowPasswd.containsMouse ? TextInput.Normal : TextInput.Password
        horizontalAlignment: isTextCenter ? Text.AlignHCenter : Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 23
        color: readOnly ? "gray" : "#FFFFFF"
        clip: true

        Text {
            text: placeholderText
            color: "#888888"
            font.pixelSize: 20
            anchors.verticalCenter: txtInp.verticalCenter
            opacity: 0.5
            visible: txtInp.text == "" && text != "" && !txtInp.cursorVisible
        }
    }

    Rectangle {
        id: rectShowPasswd
        y: 2
        width: parent.height - 4
        height: parent.height - 4
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.margins: 2
        opacity: readOnly || mouseShowPasswd.containsMouse ? 1 : 0.3
        color: "transparent"
        Image {
            id: iconPasswd
            width: 30
            height: 30
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            source: "qrc:/resources/Image/showPassword.png"
        }
        MouseArea {
            id: mouseShowPasswd
            anchors.fill: parent
        }
    }

    MouseArea {
        id: mouseTextInput
        anchors.fill: txtInp
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
