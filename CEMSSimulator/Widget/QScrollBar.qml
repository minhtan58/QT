import QtQuick 2.0

Rectangle { // ScrollBar to be placed as a direct child of a ListView or GridView (ScrollBar won't run by itself and gives errors)
    color: 'black'
    width: 0.01 * parent.width;  radius: width / 2 // size controlled by width
    anchors{right: parent.right;  margins: radius}

    height:  Math.max(parent.height / parent.contentHeight * parent.height - 2 * radius, 20) // minimum height for large lists
    y:       parent.contentY / parent.contentHeight * parent.height + radius
    visible: parent.height   < parent.contentHeight
}
