import QtQuick 2.0
import QtQuick.Controls 1.4
import HMIEvents 1.0

TextEdit {
    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: 23
    readOnly: false
    color: readOnly ? "gray" : "#FFFFFF"
    clip: true
    wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
    textMargin: 10

    property bool isFullKey: true
    property int doneEventID: -1
    property string doneEventParams: ""

    signal textInputClicked

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true
        z: -1
        onClicked: mouse.accepted = false
        onPressed: {
            if(!readOnly)
                UIBridge.hmiEvent(parent.objectName, HMIEvents.HMI_TEXTINPUT_FOCUS_CHANGED, isFullKey ? "1" : "0")
            UIBridge.log("pressed")
            mouse.accepted = false
        }
        onReleased: mouse.accepted = false
        onDoubleClicked: mouse.accepted = false
        onPositionChanged: mouse.accepted = false
        onPressAndHold: mouse.accepted = false
    }

    /* background */
    Rectangle {
        anchors.fill: parent
        color: "#000000"
        opacity: 0.5
        z: -1
    }

    /* border */
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: readOnly ? "gray" : "#FFFFFF"
        border.width: 2
    }

    function doneInput() {
        if(doneEventID != -1)
            UIBridge.hmiEvent(this.objectName, doneEventID, doneEventParams)
    }
}
