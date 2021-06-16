import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS

QBasePopup {
    id: popup_login
    objectName: "popup_logout"
    property string message: "Yêu Cầu Đăng Nhập"

    function setVisiblesCursor(isShow) {
        login_user.cursorVisible = false
        login_passwd.cursorVisible = false
        this.cursorVisible = isShow
    }

    Rectangle {
        id: qnBgr
        width: 500
        height: 300
        anchors.centerIn: parent
        color: "#315b7d"
//        opacity: 0.95
        border.color: "#FFFFFF"
        border.width: 1

        QText {
            z: 1
            text: popup_login.message
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
            x: 50
            y: 50
            width: 420
            height: 180
            text: "Chức năng cần đăng nhập để sử dụng"
        }

        QButton {
            width: parent.width/2 - 7
            height: 50
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 5
            text: "Đăng Nhập"
            eventID: HMIEvents.HMI_BUTTON_REQUEST_LOGIN_TO_CONTINUE
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
