import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS

QBasePopup {
    id: popup_create_Account
    objectName: "popup_create_Account"

    readonly property int textX: 170

    Rectangle {
        id: qnBgr
        width: 500
        height: 700
        anchors.centerIn: parent
        color: "#315b7d"
//        opacity: 0.95
        border.color: "#FFFFFF"
        border.width: 1

        QText {
            z: 1
            text: "Tạo Tài Khoản"
            width: parent.width
            height: 70
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.pixelSize: 23
        }

        Rectangle {
            width: parent.width
            height: 70
            color: "#000000"
            border.color: "#ffffff"
            border.width: 1
        }

        QText {
            x: 50; y: 90
            width: 170; height: 40
            text: "Mã Số"
            color: "#ffffff"
            wrapMode: Text.Wrap
        }

        QTextInput {
            objectName: "txtEmployeeid"
            id: txtEmployeeid
            x: textX; y: 90
            width: 300
            isTextCenter: false
        }

        QText {
            x: 50; y: 160
            width: 170; height: 40
            text: "Tài Khoản"
            color: "#ffffff"
            wrapMode: Text.Wrap
        }

        QTextInput {
            objectName: "txtUsername"
            id: txtUsername
            x: textX; y: 160
            width: 300
            isTextCenter: false
        }

        QText {
            x: 50; y: 230
            width: 170
            height: 40
            text: "Mật Khẩu"
            color: "#ffffff"
            wrapMode: Text.Wrap
        }

        QTextInputPassword {
            objectName: "txtPassword"
            id: txtPassword
            x: textX; y: 230
            width: 300
            isTextCenter: false
        }

        QText {
            x: 50; y: 300
            width: 170
            height: 40
            text: "Họ Tên"
            color: "#ffffff"
            wrapMode: Text.Wrap
        }

        QTextInput {
            objectName: "txtFullName"
            id: txtFullName
            x: textX; y: 300
            width: 300
            isTextCenter: false
        }

        QText {
            x: 50; y: 370
            width: 170; height: 40
            text: "Mô Tả"
            color: "#ffffff"
            wrapMode: Text.Wrap
        }

        QTextEdit {
            objectName: "txtDescription"
            id: txtDescription
            x: textX; y: 370
            width: 300; height: 250
            verticalAlignment: Text.AlignTop
        }

        QButton {
            width: parent.width/2 - 7
            height: 50
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 5
            text: "Tạo Tài Khoản"
            eventID: HMIEvents.HMI_REQUEST_DB_CREATE_NEW_ACCOUNT
            params: [txtEmployeeid.text, txtUsername.text, txtPassword.text, txtFullName.text, txtDescription.text]
        }

        QButton {
            width: parent.width/2 - 7
            height: 50
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 5
            text: "Hủy Bỏ"
            eventID: HMIEvents.HMI_REQUEST_HIDE_POPUP
            params: [CONSTANTS.Z_LOGIN]
        }
    }
}
