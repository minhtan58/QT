import QtQuick 2.0
import HMIEvents 1.0
import "../Js/Constants.js" as CONSTANTS

Item {
    id: popup
    property int hideTimeout: 0
    property bool isAutoClose: false
    property bool enabledCloseWhenClicked: false
    property int type: _TYPE_POPUP

    readonly property int _TYPE_POPUP: HMIEvents.HMI_REQUEST_HIDE_POPUP
    readonly property int _TYPE_QUICKNOTE: HMIEvents.HMI_REQUEST_HIDE_QN

    width: CONSTANTS.SCREEN_WIDTH
    height: CONSTANTS.SCREEN_HEIGHT

    function runTimerHidePopup() {
        if(isAutoClose && hideTimeout > 0)
            tim.start()
    }

    Rectangle {
        anchors.fill: parent
        color: "#000000"
        opacity: 0.5
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(enabledCloseWhenClicked)
                UIBridge.hmiEvent(this.objectName, type, type == _TYPE_QUICKNOTE ? CONSTANTS.Z_QUICKNOTES : CONSTANTS.Z_POPUP)
        }
    }

    Timer {
        id: tim
        interval: hideTimeout
        repeat: false
        onTriggered: UIBridge.hmiEvent(this.objectName, type, type == _TYPE_QUICKNOTE ? CONSTANTS.Z_QUICKNOTES : CONSTANTS.Z_POPUP)
    }

    onHideTimeoutChanged: runTimerHidePopup()
    onIsAutoCloseChanged: runTimerHidePopup()
    Component.onCompleted: runTimerHidePopup()
}
