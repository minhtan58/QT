import QtQuick 2.0
import "qrc:/resources/Widget"

Item {
    width: delegate.ListView.view.width
    height: 40
    z: 2
    QText {
        text: "Thời Gian"
        width: parent.width * 1/6
        height: parent.height
        anchors.leftMargin: 20
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
        font.pixelSize: 20
    }
    QText {
        text: "ff"
        x: parent.width * 1/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
        font.pixelSize: 20
    }
    QText {
        text: "dd"
        x: parent.width * 2/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
        font.pixelSize: 20
    }
    QText {
        text: "Khí Áp"
        x: parent.width * 3/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
        font.pixelSize: 20
    }
    QText {
        text: "Mưa 1h"
        x: parent.width * 4/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
        font.pixelSize: 20
    }
    QText {
        text: "Mưa 24h"
        x: parent.width * 5/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        backgroundColor: "steelblue"
        font.bold: true
        font.pixelSize: 20
    }
}
