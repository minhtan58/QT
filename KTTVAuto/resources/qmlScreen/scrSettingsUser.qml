import QtQuick 2.0
import QtQuick.Controls 1.4
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "qrc:/resources/qmlScreen/ListDelegate"
import "../Js/Constants.js" as CONSTANTS

Item {
    objectName: "scr_settings_general"

    QLeftTabView {
        currentIndex: 2
    }

    Item {
        x: CONSTANTS.LEFT_TAB_WIDTH + 5
        y: 10
        width: CONSTANTS.SCREEN_WIDTH - x - 5
        height: CONSTANTS.APP_HEIGHT - 20
        Rectangle {
            anchors.fill: parent
            radius: 10
            color: "#315b7d"
            opacity: 0.3
        }

        QTabWidget {
            id: tabs
            anchors.fill: parent

            Item {
                id: screenArea
                x: 0; y: 70
                property string title: "Thông Tin Người Dùng"

                QText {
                    x: 50; y: 0
                    width: 170; height: 40
                    text: "Mã Số"
                    color: "#ffffff"
                    wrapMode: Text.Wrap
                }

                QText {
                    x: 220; y: 0
                    width: 350
                    hasBorder: true
                    horizontalAlignment: Text.AlignHCenter
                    text: AppModel.isLogin ? AppModel.userCode : "Chưa Đăng Nhập"
                }

                QText {
                    x: 50; y: 70
                    width: 170; height: 40
                    text: "Tài Khoản"
                    color: "#ffffff"
                    wrapMode: Text.Wrap
                }

                QText {
                    x: 220; y: 70
                    width: 350
                    hasBorder: true
                    horizontalAlignment: Text.AlignHCenter
                    text: AppModel.isLogin ? AppModel.userAccount : ""
                }

                QText {
                    x: 50; y: 140
                    width: 170
                    height: 40
                    text: "Họ Tên"
                    color: "#ffffff"
                    wrapMode: Text.Wrap
                }

                QText {
                    x: 220; y: 140
                    width: 350
                    hasBorder: true
                    horizontalAlignment: Text.AlignHCenter
                    text: AppModel.isLogin ? AppModel.userFullName : ""
                }

                QText {
                    x: 50; y: 210
                    width: 170; height: 40
                    text: "Mô Tả"
                    color: "#ffffff"
                    wrapMode: Text.Wrap
                }

                QText {
                    x: 220; y: 210
                    width: 350; height: 250
                    hasBorder: true
                    horizontalAlignment: Text.AlignHCenter
                    text: AppModel.isLogin ? AppModel.userDescription : ""
                }

                QImage {
                    x: 650; y: 0
                    width: 200
                    height: 200
                    emptyText: "No Image"
                    border.color: "#888888"
                }

                QButton {
                    x: 650; y: 220
                    width: 150; height: 40
                    text: "Đổi Mật Khẩu"
                    eventID: HMIEvents.HMI_REQUEST_SHOW_CHANGE_PASSWORD_POPUP
                    enabled: AppModel.isLogin
                }

                Component.onCompleted: UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_REQUEST_GET_CURRENT_USER_LOGIN_INFORMATION, "")
            }

            Loader {
                id: loaderLoginHistory
                anchors.fill: parent
                property string title: "Lịch Sử Làm Việc"
                sourceComponent: tabs.current == 1 ? historyComponent : undefined
                asynchronous: true
                onLoaded: {
                    UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_REQUEST_GET_LOGIN_HISTORY, AppModel.historySearchDateStart + "" + AppModel.historySearchDateEnd)
                }

                onSourceComponentChanged: {
                    if(sourceComponent == undefined)
                        UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_REQUEST_DELETE_LOGIN_LIST, "")
                }

                Component {
                    id: historyComponent
                    Item {
                        QText {
                            text: "Từ: "
                            width: 50; height: 40
                            x: 20; y: 15
                        }
                        QDatePicker {
                            id: dateStart
                            x: 70; y: 15; z: 1
                            width: 300; height: 40
                            datetime: AppModel.historySearchDateStart
                        }

                        QText {
                            text: "Đến: "
                            width: 50; height: 40
                            x: 400; y: 15
                        }

                        QDatePicker {
                            id: dateEnd
                            x: 460; y: 15; z: 1
                            width: 300; height: 40
                            datetime: AppModel.historySearchDateEnd
                        }

                        QButton {
                            x: 800; y: 15
                            width: 150; height: 40
                            text: "Lọc"
                            eventID: HMIEvents.HMI_REQUEST_GET_LOGIN_HISTORY
                            params: [dateStart.datetime, dateEnd.datetime]
                        }

                        QListView {
                            id: listLoginHistory
                            anchors.fill: parent
                            anchors {topMargin: 70; leftMargin: 20; rightMargin: 20; bottomMargin: 20}
                            delegate: LoginHistoryDelegate {}
                            snapMode: ListView.SnapOneItem
                            emptyText: "No History"
                            model: loginModel
                            header: LoginHistoryHeader {width: listLoginHistory.width}
                        }
                    }
                }
            }

            Loader {
                id: loaderAccount
                anchors.fill: parent
                property string title: "Quản Trị Tài Khoản"
                sourceComponent: tabs.current == 2 ? accountListComponent : undefined
                asynchronous: true
                enabled: AppModel.hasPermissionSettingAccount()
                onLoaded: {
                    UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_REQUEST_GET_ACCOUNT_LIST, "")
                }
                onSourceComponentChanged: {
                    if(sourceComponent == undefined)
                        UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_REQUEST_DELETE_ACCOUNT_LIST, "")
                }
                onEnabledChanged: UIBridge.log("hasPermissionSettingAccount = " + AppModel.hasPermissionSettingAccount())

                Connections {
                    target: AppModel
                    onUserPermissionChanged: loaderAccount.enabled = AppModel.hasPermissionSettingAccount()
                }

                Component {
                    id: accountListComponent
                    Item {
                        anchors.fill: parent
                        QListView {
                            id: listAccount
                            x: 20; y: 20
                            width: 500
                            height: parent.height - 80
                            delegate: AccountDelegate {}
                            snapMode: ListView.SnapOneItem
                            emptyText: "No History"
                            model: accountModel
                            header: AccountHeader {width: listAccount.width}
                            onCurrentIndexChanged: {
                                AppModel.selectedAccountUserCode = accountModel.data(accountModel.index(currentIndex, 0), 256 + 1)
                                AppModel.selectedAccountUserPermission = accountModel.data(accountModel.index(currentIndex, 0), 256 + 2)
                                AppModel.selectedAccountUserAccount = accountModel.data(accountModel.index(currentIndex, 0), 256 + 3)
                                AppModel.selectedAccountUserPassword = accountModel.data(accountModel.index(currentIndex, 0), 256 + 4)
                                AppModel.selectedAccountUserFullName = accountModel.data(accountModel.index(currentIndex, 0), 256 + 5)
                                AppModel.selectedAccountUserDescription = accountModel.data(accountModel.index(currentIndex, 0), 256 + 6)
                            }
                        }

                        QText {
                            x: 550; y: 20
                            width: 170; height: 40
                            text: "Mã Số"
                            color: "#ffffff"
                            wrapMode: Text.Wrap
                            font.pixelSize: 20
                        }
                        QTextInput {
                            id: txtUserCode
                            objectName: "txtUserCode"
                            x: 650; y: 20
                            width: 300; height: 40
                            isTextCenter: false
                            text: AppModel.selectedAccountUserCode
                            font.pixelSize: 20
                        }
                        QText {
                            x: 550
                            y: 90
                            width: 170
                            height: 40
                            text: "Tài Khoản"
                            color: "#ffffff"
                            wrapMode: Text.Wrap
                            font.pixelSize: 20
                        }
                        QTextInput {
                            id: txtUsername
                            objectName: "txtUsername"
                            x: 650; y: 90
                            width: 300; height: 40
                            isTextCenter: false
                            text: AppModel.selectedAccountUserAccount
                            font.pixelSize: 20
                            textInputEnabled: false
                        }
                        QText {
                            x: 550; y: 160
                            width: 170; height: 40
                            text: "Họ Tên"
                            color: "#ffffff"
                            wrapMode: Text.Wrap
                            font.pixelSize: 20
                        }
                        QTextInput {
                            id: txtFullname
                            objectName: "txtFullname"
                            x: 650; y: 160
                            width: 300; height: 40
                            isTextCenter: false
                            text: AppModel.selectedAccountUserFullName
                            font.pixelSize: 20
                        }
                        QText {
                            x: 550; y: 230
                            width: 170; height: 40
                            text: "Mật Khẩu"
                            color: "#ffffff"
                            wrapMode: Text.Wrap
                            font.pixelSize: 20
                        }
                        QTextInputPassword {
                            id: txtPassword
                            objectName: "txtPassword"
                            x: 650; y: 230
                            width: 300; height: 40
                            isTextCenter: false
                            textInputEnabled: false
                            text: AppModel.selectedAccountUserPassword
                            font.pixelSize: 20
                        }
                        QText {
                            x: 550; y: 300
                            width: 170; height: 40
                            text: "Mô Tả"
                            color: "#ffffff"
                            wrapMode: Text.Wrap
                            font.pixelSize: 20
                        }
                        QTextEdit {
                            id: txtDescription
                            objectName: "txtDescription"
                            x: 650; y: 300
                            width: 300; height: 220
                            verticalAlignment: Text.AlignTop
                            text: AppModel.selectedAccountUserDescription
                            font.pixelSize: 20
                        }
                        QButton {
                            x: 200; y: 540
                            width: 150; height: 40
                            text: "Thêm Tài Khoản"
                            eventID: HMIEvents.HMI_REQUEST_SHOW_CREATE_ACCOUNT_POPUP
                        }
                        QButton {
                            x: 370; y: 540
                            width: 150; height: 40
                            text: "Xóa Tài Khoản"
                            eventID: HMIEvents.HMI_REQUEST_SHOW_DELETE_ACCOUNT_CONFIRM_POPUP
                            params: [txtUsername.text]
                        }
                        QButton {
                            x: 800; y: 540
                            width: 150; height: 40
                            text: "Lưu Thay Đổi"
                            eventID: HMIEvents.HMI_REQUEST_DB_SAVE_CHANGE_ACCOUNT
                            params: [
                                txtUserCode.text,
                                txtUsername.text,
                                txtFullname.text,
                                txtDescription.text
                            ]
                        }
                    }
                }
            }
        }
    }
}
