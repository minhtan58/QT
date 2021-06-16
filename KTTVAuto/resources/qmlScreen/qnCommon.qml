import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"

QBasePopup {
    id: toast
    property alias message: textContent.text
    type: _TYPE_QUICKNOTE
    isAutoClose: true
    enabledCloseWhenClicked: true

    Rectangle {
        id: qnBgr
        width: 600
        height: 100
        anchors.horizontalCenter: parent.horizontalCenter
        y: 550
        color: "#315b7d"
        opacity: 0.95
        border.color: "#FFFFFF"
        border.width: 1
        radius: 10
    }

    QText {
        id: textContent
        anchors.fill: qnBgr
        text: "Save Successful"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 25
        wrapMode: Text.Wrap
    }
}
