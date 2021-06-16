import QtQuick 2.0
import "qrc:/resources/Widget"

Item {
    id: delegate
    width: delegate.ListView.view.width
    height: 40
    QText {
        text: employeeid
        x: 5
        width: parent.width * 3/10 - x
        height: parent.height
        font.pixelSize: 20
        horizontalAlignment: Text.AlignLeft
        maximumLineCount: 1
        elide: Text.ElideRight
    }
    QText {
        text: fullname
        x: parent.width * 3/10
        width: parent.width * 4/10
        height: parent.height
        font.pixelSize: 20
        horizontalAlignment: Text.AlignLeft
        maximumLineCount: 1
        elide: Text.ElideRight
    }
    QText {
        text: username
        x: parent.width * 7/10
        width: parent.width * 3/10
        height: parent.height
        font.pixelSize: 20
        horizontalAlignment: Text.AlignLeft
//        font.bold: delegate.ListView.view.currentIndex === index
        maximumLineCount: 1
        elide: Text.ElideRight
    }
    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true
        onClicked: delegate.ListView.view.currentIndex = index
    }
}
