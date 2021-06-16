import QtQuick 2.3
import QtQuick.Window 2.2
import CEMSEnum 1.0
import "Widget"

Window {
    visible: true
    //    width: Screen.width
    //    height: Screen.height
    width: CEMSConstants.screenWidth
    height: CEMSConstants.screenHeight
    color: "#000000"

    readonly property int buttonMargin: 10

    property bool isShowBorder: true
    property bool isScreenShotEnable: false

    Item {
        id: screenArea
        anchors.centerIn: parent
        width: CEMSConstants.screenWidth
        height: CEMSConstants.screenHeight

        //border
        Rectangle {
            anchors.fill: parent
            border.color: "#FFFFFF"
            border.width: 1
            color: "transparent"
            z: 10
            visible: isShowBorder
        }

        Image {
            id: name
            source: "qrc:/resources/Image/background.png"
            z: CEMSConstants.backgroundZ
        }

        Loader {
            id: topBar
            objectName: "topbarContainer"
            x: 0
            y: 0
            z: CEMSConstants.topbarZ
            width: CEMSConstants.screenWidth
            height: CEMSConstants.topbarHeight
            source: "qrc:/resources/qmlScreen/prtTopBar.qml"
        }

        Loader {
            objectName: "overlayContainer"
            x: 0
            y: 0
            z: CEMSConstants.overlayZ
            width: CEMSConstants.screenWidth
            height: CEMSConstants.screenHeight
        }

        Loader {
            id: mainScreen
            objectName: "appContainer"
            x: 0
            y: CEMSConstants.topbarHeight
            z: CEMSConstants.appContainerZ
            width: CEMSConstants.screenWidth
            height: CEMSConstants.appHeight
        }

        Loader {
            id: keyboard
            objectName: "keyboardContainer"
            x: 0
            y: 0
            z: CEMSConstants.appContainerZ
            width: CEMSConstants.screenWidth
            height: CEMSConstants.screenHeight
        }

        Item {
            id: saveScreenshotButton
            width: 70
            height: 70
            anchors.top: parent.top
            anchors.right: parent.right
            z: 9999
            MouseArea {
                anchors.fill: parent
                enabled: isScreenShotEnable
                onClicked: UIBridge.hmiEvent(this.objectName, CEMSEnum.HMI_BUTTON_DEVELOPER_SAVE_SCREENSHOT, "")
            }
        }
    }
}

