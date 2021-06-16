import QtQuick 2.0

Item {
    readonly property int sizeKeyNormal: 1      //normal character or number, special character
    readonly property int sizeKeyCtrl: 2        //delete, CAP or switch
    readonly property int sizeKeySpace: 3       //space

    readonly property int functionNormal: 0     //tap text normal
    readonly property int functionCtrl: 1       //tap control key

    property int keyState: 0
    property var keyTextList: []

    property color keyColor: "gray"

    property int keySize: sizeKeyNormal
    property int keyFunction: functionNormal
    property alias keyText: txtContent.text
    property alias keyImage: imgContent.source

    signal keyCtrlPressed
    signal keyCtrlClicked
    signal keyCtrlPressAndHold

    width: (keySize == sizeKeyCtrl) ? 120 : (keySize == sizeKeySpace ? 320 : 80)
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
            preventStealing: true
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

            onPressAndHold: keyCtrlPressAndHold()
        }
    }

    Image {
        id: imgContent
        anchors.centerIn: parent
        width: keySize === sizeKeyNormal ? 50 : 120
        height: keySize === sizeKeyNormal ? 35 : 58
    }

    QText {
        id: txtContent
        text: keyFunction === functionNormal ? String(keyTextList[keyState]) : ""
        z: 1
        anchors.centerIn: parent
        wrapMode: Text.WordWrap
    }
}
