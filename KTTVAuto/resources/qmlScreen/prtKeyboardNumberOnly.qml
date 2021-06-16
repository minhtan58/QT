import QtQuick 2.0
import "qrc:/resources/Widget"
import "../Js/Defines.js" as DEFINES

Item {
    objectName: "keyboard_number_only"
    property int keyboardType: 0

    Item {
        id: keyboardNumber
//        x: 240
        x: 0
        y: 568
        width: 320
        height: 232

        Rectangle {
            anchors.fill: parent
            color: "#000000"
            radius: 3
            MouseArea {
                anchors.fill: parent
            }
        }

        Rectangle {
            x: 300
            y: -50
            z: 1
            width: 60
            height: 60
            radius: 30
            border.color: "#ffffff"
            border.width: 2
            color: "#2c2c2e"

            Image {
                source: DEFINES.IMG_KEYBOARD_MOVE
                anchors.centerIn: parent
                width: 50
                height: 35
            }

            MouseArea {
                id: dragArea
                anchors.fill: parent
                drag.target: keyboardNumber
                drag.minimumX: 0
                drag.maximumX: 960
                drag.minimumY: 70
                drag.maximumY: 568
            }
        }

        QDigitKey {
            x: 0
            y: 0
            keyText: "1"
        }
        QDigitKey {
            x: 80
            y: 0
            keyText: "2"
        }
        QDigitKey {
            x: 160
            y: 0
            keyText: "3"
        }

//        Item {
//            x: 243
//            y: 3
//            width: 74
//            height: 52
//            Rectangle {
//                radius: 3
//                anchors.fill: parent
//                color: "gray"
//                opacity: dragArea.containsMouse ? 1 : 0.5
//                Drag.active: dragArea.drag.active

//            }
//            Image {
//                source: DEFINES.IMG_KEYBOARD_MOVE
//                anchors.centerIn: parent
//                width: 50
//                height: 35
//            }
//        }

        QDigitKey {
            x: 240
            y: 0
            keyFunction: functionCtrl
            keyImage: DEFINES.IMG_KEYBOARD_DELETE
            onKeyCtrlClicked: {
                UIBridge.keyboardEvent(1, "delete_clicked")
            }
            onKeyCtrlPressAndHold: {
                UIBridge.keyboardEvent(1, "delete_hold")
            }
        }

        QDigitKey {
            x: 0
            y: 58
            keyText: "4"
        }
        QDigitKey {
            x: 80
            y: 58
            keyText: "5"
        }
        QDigitKey {
            x: 160
            y: 58
            keyText: "6"
        }

        QDigitKey {
            x: 240
            y: 58
            keyText: ":"
        }

        QDigitKey {
            x: 0
            y: 116
            keyText: "7"
        }
        QDigitKey {
            x: 80
            y: 116
            keyText: "8"
        }
        QDigitKey {
            x: 160
            y: 116
            keyText: "9"
        }
        QDigitKey {
            x: 240
            width: 80
            height: 116
            y: 116
            keyText: "Enter"
            keyFunction: functionCtrl
            keyColor: "green"
            onKeyCtrlClicked: {
                UIBridge.keyboardEvent(1, "done")
            }
        }

        QDigitKey {
            x: 0
            y: 174
            keyText: "."
        }
        QDigitKey {
            x: 80
            y: 174
            keyText: "0"
        }
        QDigitKey {
            x: 160
            y: 174
            keyFunction: functionCtrl
            keyImage: DEFINES.IMG_KEYBOARD_HIDE
            onKeyCtrlClicked: {
                UIBridge.keyboardEvent(1, "hide")
            }
        }
    }
}
