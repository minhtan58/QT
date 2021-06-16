import QtQuick 2.5

Item {
    id: scrollBarWidget
    property Flickable flickable: null
    visible: indicatorBar.height < backGround.height

    readonly property int scrollUp: 0
    readonly property int scrollDown: 1

    function scroll(direction) {
        var moveStep = 800
        switch(direction) {
        case scrollUp:
            if(!flickable.atYBeginning) {
                flickable.flick(0, moveStep)
            }
            break
        case scrollDown:
            if(!flickable.atYEnd) {
                flickable.flick(0, -moveStep)
            }
            break
        default:
            break
        }
    }

    Rectangle {
        id: backGround
        width: 15
        height: scrollBarWidget.height - btnUp.height * 2
        color: "#ffffff"
        opacity: 0.5
        anchors.horizontalCenter: scrollBarWidget.horizontalCenter
    }

    Rectangle {
        id: btnUp
        anchors.top: backGround.bottom
        width: scrollBarWidget.width
        height: scrollBarWidget.width
        anchors.margins: 5
        color: "#2c2c2e"
        border.color: "#ffffff"
        border.width: 1
        opacity: mouseUp.containsMouse ? 0.5 : 1
        QText {
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            text: "▲"
            font.pixelSize: 30
        }
        MouseArea {
            id: mouseUp
            anchors.fill: parent
            onPressed: scroll(scrollUp)
            onPressAndHold: scrollTimer.start()
            onReleased: {
                if(scrollTimer.running)
                    scrollTimer.stop()
            }
        }
    }

    Rectangle {
        id: btnDown
        anchors.top: btnUp.bottom
        width: scrollBarWidget.width
        height: scrollBarWidget.width
        anchors.margins: 5
        color: "#2c2c2e"
        border.color: "#ffffff"
        border.width: 1
        opacity: mouseDown.containsMouse ? 0.5 : 1
        QText {
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            text: "▼"
            font.pixelSize: 30
        }
        MouseArea {
            id: mouseDown
            anchors.fill: parent
            onPressed: scroll(scrollDown)
            onPressAndHold: scrollTimer.start()
            onReleased: {
                if(scrollTimer.running)
                    scrollTimer.stop()
            }
        }
    }

    Rectangle {
        id: indicatorBar
        anchors.horizontalCenter: scrollBarWidget.horizontalCenter
        width: 15
        height: Math.round(flickable.visibleArea.heightRatio * parent.height) < 5 ? 5: flickable.visibleArea.heightRatio * parent.height
        color: indicatorBarMouseArea.containsMouse ? "#888888" : "#ffffff"
        border.color: "#000000"
        border.width: 1
        MouseArea {
            id: indicatorBarMouseArea
//            anchors.top: scrollBarWidget.top
//            anchors.left: scrollBarWidget.left
//            anchors.right: scrollBarWidget.right
//            anchors.bottom: btnUp.top
            anchors.fill: parent
            z: 1
            drag {
                target: indicatorBar
                axis: Drag.YAxis
                minimumY: backGround.y
                maximumY: backGround.y + backGround.height - indicatorBar.height
            }
        }
        onYChanged: {
            if (y <= backGround.y) {
                y = backGround.y
            } else if (y >= backGround.y + backGround.height - indicatorBar.height) {
                y = backGround.y + backGround.height - indicatorBar.height
            }
        }
    }

    Binding {
        target: indicatorBar
        property: "y"
        value: flickable.visibleArea.yPosition * backGround.height
        when: flickable.moving || flickable.flicking
    }

    Binding {
        target: flickable
        property: "contentY"
        value: indicatorBar.y /indicatorBarMouseArea.drag.maximumY * (flickable.contentHeight - flickable.height) + flickable.originY
        when: indicatorBarMouseArea.drag.active
    }

    Timer {
        id: scrollTimer
        onTriggered: scroll(mouseUp.containsMouse ? scrollUp: scrollDown)
        interval: 500
        repeat: true
    }

//    SmoothedAnimation {
//        target: flickable
//        properties: "contentY"
//        running: flickable.flicking
//    }
}

