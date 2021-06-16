import QtQuick 2.0
import "qrc:/resources/Widget"

Item {
    width: delegate.ListView.view.width
    height: 40
    z: 2

    Rectangle {
        anchors.fill: parent
        color: "steelblue"
    }

    QText {
        text: "Mã NV"
        x: 5
        width: parent.width * 3/10 - x
        height: parent.height
        font.pixelSize: 20
        font.bold: true
    }
    QText {
        text: "Họ Tên"
        x: parent.width * 3/10
        width: parent.width * 4/10
        height: parent.height
        font.pixelSize: 20
        font.bold: true
    }
    QText {
        text: "Tài Khoản"
        x: parent.width * 7/10
        width: parent.width * 3/10
        height: parent.height
        font.pixelSize: 20
        font.bold: true
    }
}
