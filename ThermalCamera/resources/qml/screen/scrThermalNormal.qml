import QtQuick 2.0
import QtQuick.Window 2.2
import QtMultimedia 5.0
import QQuickImage 1.0
import "qrc:/resources/qml/widget"

Item {
    id: root
    width: Screen.width
    height: Screen.height

    Text {
        objectName: "thermal_temperature"
        property string maxTemp: ""
        text: "Max Temp: " + maxTemp + " °C"
        font.pixelSize: 24
        color: "#ffffff"
        anchors.centerIn: parent
        z: 5
    }

    CameraImage {
        id: thermal_image
        objectName: "thermal_image"
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        border.width: 1
        border.color: "#FFFFFF"
        anchors.margins: 5
        anchors.centerIn: parent
    }
}
