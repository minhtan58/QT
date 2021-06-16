import QtQuick 2.0

Item {
    readonly property int functionNormal: 0     //tap text normal
    readonly property int functionCtrl: 1       //tap control key

    property int keyFunction: functionNormal
    property alias keyText: txtContent.text
    property alias keyImage: imgContent.source
    property color keyColor: "gray"

    signal keyCtrlPressed
    signal keyCtrlClicked
    signal keyCtrlPressAndHold

    width: 80
    height: 58

    Rectangle {
        anchors.fill: parent
        anchors.margins: 3
        radius: 3
        color: keyColor
        opacity: keyArea.containsMouse ? 1 : 0.5

        MouseArea {
            id: keyArea
            anchors.fill: parent
            onPressed: {
                if(keyFunction == functionNormal)
                    UIBridge.keyboardEvent(0, keyText)
                else
                    keyCtrlPressed()
            }

            onClicked: {
                if(keyFunction == functionCtrl)
                    keyCtrlClicked()
            }

            onPressAndHold:
                if(keyFunction == functionCtrl)
                    keyCtrlPressAndHold()
        }
    }

    Image {
        id: imgContent
        anchors.centerIn: parent
        width: 50
        height: 35
    }

    Text {
        id: txtContent
        text: ""
        z: 1
        anchors.centerIn: parent
        wrapMode: Text.WordWrap
        color: "#ffffff"
        font.pixelSize: 25
    }
}
