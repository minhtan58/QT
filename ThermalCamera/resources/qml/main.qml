import QtQuick 2.0
import QtQuick.Window 2.2

Window {
    visible: true
//    width: Screen.width
//    height: Screen.height
    width: Screen.width
    height: Screen.height
    title: qsTr("Thermal Camera")
    Item {
        anchors.fill: parent
//        Image {
//            anchors.fill: parent
//            source: "qrc:/resources/images/background.png"
//            z: Constants.backgroundZ
//        }

        Rectangle {
            anchors.fill: parent
            color: "#000000"
            z: Constants.backgroundZ
        }

        Loader {
            id: mainScreen
            objectName: "appContainer"
            anchors.fill: parent
            z: Constants.appContainerZ
        }
    }
}
