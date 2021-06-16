import QtQuick 2.0
import QQuickImage 1.0

QQuickImage {
    property alias border: rectBorder.border
    Rectangle {
        id: rectBorder
        anchors.fill: parent
        color: "transparent"
    }
}
