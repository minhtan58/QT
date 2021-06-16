import QtQuick 2.0
import "qrc:/resources/Widget"

Item {
    id: delegate
    width: delegate.ListView.view.width
    height: 40

    QText {
        text: date
        width: parent.width * 1/6
        height: parent.height
        x: 20
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        font.bold: delegate.ListView.view.currentIndex === index
    }
    QText {
        text: ff
        x: parent.width * 1/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
        font.bold: delegate.ListView.view.currentIndex === index
    }
    QText {
        text: dd
        x: parent.width * 2/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
        font.bold: delegate.ListView.view.currentIndex === index
    }
    QText {
        text: khiap
        x: parent.width * 3/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
        font.bold: delegate.ListView.view.currentIndex === index
    }
    QText {
        text: rain1h
        x: parent.width * 4/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
        font.bold: delegate.ListView.view.currentIndex === index
    }
    QText {
        text: rain24h
        x: parent.width * 5/6
        width: parent.width * 1/6
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
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
