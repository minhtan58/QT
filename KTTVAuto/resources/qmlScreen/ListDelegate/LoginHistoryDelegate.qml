import QtQuick 2.0
import "qrc:/resources/Widget"

Item {
    id: delegate
    width: delegate.ListView.view.width
    height: 40
    QText {
        text: employeeid
        width: parent.width * 1/4
        height: parent.height
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        font.bold: delegate.ListView.view.currentIndex === index
    }
    QText {
        text: fullname
        x: parent.width * 1/4
        width: parent.width * 1/4
        height: parent.height
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        font.bold: delegate.ListView.view.currentIndex === index
    }
    QText {
        text: login
        x: parent.width * 2/4
        width: parent.width * 1/4
        height: parent.height
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        font.bold: delegate.ListView.view.currentIndex === index
    }
    QText {
        text: logout
        x: parent.width * 3/4
        width: parent.width * 1/4
        height: parent.height
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        font.bold: delegate.ListView.view.currentIndex === index
    }
    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true
        onClicked: {
            delegate.ListView.view.currentIndex = index
        }
    }
}
