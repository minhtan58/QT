import QtQuick 2.0
import "../Js/Constants.js" as CONSTANTS

Item {
    property int pages: 2
    property int currentPage: 0
    Item {
        width: parent.width
        height: 70
    }
    Flickable {
        contentWidth: pages * width
        contentHeight: height
    }
}
