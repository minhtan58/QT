import QtQuick 2.0

Item {
    id : clock
    property int hours: 0
    property int minutes: 0
    property int seconds: 0

    property alias faceClockImgSrc: faceClock.source
    property alias centerClockImgSrc: centerClock.source
    property alias hourImgSrc: hourHand.source
    property alias minuteImgSrc: minuteHand.source
    property alias secondImgSrc: secondHand.source
    property bool asynchronous: true

    visible: faceClock.status == Image.Ready && hourHand.status == Image.Ready && minuteHand.status == Image.Ready && secondHand.status == Image.Ready && centerClock.status == Image.Ready

    Image {
        id: faceClock
        width: parent.width
        height: parent.height
        z: 0
        fillMode: Image.PreserveAspectFit
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        source: "qrc:/resources/Image/AnalogClock/clockFace.png"
        asynchronous: parent.asynchronous
        antialiasing: true
    }

    Image {
        id: hourHand
        width: parent.width
        height: parent.height
        z: 1
        fillMode: Image.PreserveAspectFit
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        source: "qrc:/resources/Image/AnalogClock/hour.png"
        asynchronous: parent.asynchronous
        antialiasing: true
        transform: Rotation {
            id: hourRotation
            origin.x: width/2
            origin.y: height/2
            angle: (clock.hours * 30) + (clock.minutes * 0.5)
            Behavior on angle {
                SpringAnimation {
                    spring: 2
                    damping: 0.2
                    modulus: 360
                }
            }
        }
    }

    Image {
        id: minuteHand
        width: parent.width
        height: parent.height
        z: 2
        fillMode: Image.PreserveAspectFit
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        source: "qrc:/resources/Image/AnalogClock/minute.png"
        asynchronous: parent.asynchronous
        antialiasing: true
        transform: Rotation {
            id: minuteRotation
            origin.x: width/2
            origin.y: height/2
            angle: (clock.minutes * 6) + (clock.seconds * 0.1)
            Behavior on angle {
                SpringAnimation {
                    spring: 2
                    damping: 0.2
                    modulus: 360
                }
            }
        }
    }

    Image {
        id: secondHand
        width: parent.width
        height: parent.height
        z: 3
        fillMode: Image.PreserveAspectFit
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        source: "qrc:/resources/Image/AnalogClock/second.png"
        asynchronous: parent.asynchronous
        antialiasing: true
        transform: Rotation {
            id: secondRotation
            origin.x: width/2
            origin.y: height/2
            angle: clock.seconds * 6
            Behavior on angle {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                    modulus: 360
                }
            }
        }
    }

    Image {
        id: centerClock
        width: parent.width
        height: parent.height
        z: 4
        fillMode: Image.Pad
        verticalAlignment: Image.AlignVCenter
        horizontalAlignment: Image.AlignHCenter
        source: "qrc:/resources/Image/AnalogClock/center.png"
        asynchronous: parent.asynchronous
        antialiasing: true
    }
}
