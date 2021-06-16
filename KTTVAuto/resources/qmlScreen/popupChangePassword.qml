import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS

QBasePopup {
    id: popup_change_password
    objectName: "popup_change_password"
    property string message: ""

    Rectangle {
        id: qnBgr
        width: 500
        height: 350
        anchors.centerIn: parent
        color: "#315b7d"
//        opacity: 0.95
        border.color: "#FFFFFF"
        border.width: 1

        QText {
            z: 1
            text: "Đổi Mật Khẩu"
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

        QTextInputPassword {
            id: current_passwd
            objectName: "current_passwd"
            x: 100
            y: 90
            width: 300
            height: 50
            isTextCenter: false
            placeholderText: "Mật khẩu hiện tại...."
        }

        QTextInputPassword {
            id: new_passwd
            objectName: "new_passwd"
            x: 100
            y: 160
            width: 300
            height: 50
            isTextCenter: false
            placeholderText: "Mật khẩu mới...."
        }

        QTextInputPassword {
            id: renew_passwd
            objectName: "renew_passwd"
            x: 100
            y: 230
            width: 300
            height: 50
            isTextCenter: false
            placeholderText: "nhập lại mật khẩu mới...."
        }

        QButton {
            width: parent.width/2 - 7
            height: 50
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 5
            text: "Thay Đổi"
            eventID: HMIEvents.HMI_REQUEST_DB_CHANGE_PASSWORD
            params: [AppModel.userAccount, current_passwd.text, new_passwd.text, renew_passwd.text]
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
