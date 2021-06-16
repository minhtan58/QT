import QtQuick 2.0

Item {
    id: root

    // public
    property real value:    0
    property real minimum:  0
    property real maximum: 10

    // private
    width: 250;  height: 50  // Default size
    opacity: enabled? 1: 0.3 // Disabled state

    Repeater { // Left and right trays (so tray doesn't shine through pill in disabled state)
        model: 2

        Rectangle {
            x:     !index?               0: pill.x + pill.width - radius
            width: !index? pill.x + radius: root.width - x;  height: 0.1 * root.height
            radius: 0.5 * height
            color: 'black'
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle { // Pill
        id: pill
        x: (value - minimum) / (maximum - minimum) * (root.width - pill.width) // Pixels from value
        width: parent.height
        height: width
        border.width: 0.05 * root.height
        radius: 0.5 * height
    }

    MouseArea {
        anchors.fill: parent
        onPressed:          if (pill.x < mouse.x  &&  mouse.x < pill.x + pill.width) pill.opacity = 0.5 // Down state
        onReleased:           { pill.opacity = 1; setPixels(mouse.x) } // Tap
        onCanceled:            pill.opacity = 1
        onPositionChanged:  if (pill.opacity < 1) setPixels(mouse.x) // Drag pill
    }

    function setPixels(pixels) {
        var value = (maximum - minimum) / (root.width - pill.width) * (pixels - pill.width / 2) + minimum // value from pixels
        root.value = Math.min(Math.max(minimum, value), maximum)
    }
}
