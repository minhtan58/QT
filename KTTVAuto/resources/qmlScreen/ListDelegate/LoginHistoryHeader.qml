import QtQuick 2.0
import "qrc:/resources/Widget"

Item {
    width: delegate.ListView.view.width
    height: 40
    z: 2
    QText {
        text: "Mã NV"
        width: parent.width * 1/4
        height: parent.height
        anchors.leftMargin: 20
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
    }
    QText {
        text: "Họ Tên"
        x: parent.width * 1/4
        width: parent.width * 1/4
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
    }
    QText {
        text: "Đăng Nhập"
        x: parent.width * 2/4
        width: parent.width * 1/4
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
    }
    QText {
        text: "Đăng Xuất"
        x: parent.width * 3/4
        width: parent.width * 1/4
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
    }
}
