import QtQuick 2.3
import QtQuick.Window 2.2
import HMIEvents 1.0
import "Widget"
import "Js/Constants.js" as CONSTANTS
import "Js/Defines.js" as DEFINES

Window {
    visible: true
    //width: Screen.width
    //height: Screen.height
    width: CONSTANTS.SCREEN_WIDTH
    height: CONSTANTS.SCREEN_HEIGHT
    color: "#000000"

    property bool isShowBorder: false
    property bool isScreenShotEnable: true

    FontLoader {source: "qrc:/resources/fonts/segoeuil.ttf"}
    FontLoader {source: "qrc:/resources/fonts/seguisb.ttf"}
    FontLoader {source: "qrc:/resources/fonts/segoeui.ttf"}
    FontLoader {source: "qrc:/resources/fonts/segoeuib.ttf"}

    Item {
        id: screenArea
        anchors.centerIn: parent
        width: CONSTANTS.SCREEN_WIDTH
        height: CONSTANTS.SCREEN_HEIGHT

        /* Border */
        Rectangle {
            anchors.fill: parent
            border.color: "#FFFFFF"
            border.width: 1
            color: "transparent"
            z: 10
            visible: isShowBorder
        }

        /* Background */
        Image {
            id: name
            source: "qrc:/resources/Image/background.png"
            width: CONSTANTS.SCREEN_WIDTH
            height: CONSTANTS.SCREEN_HEIGHT
            z: CONSTANTS.Z_BACKGROUND
        }

        Loader {
            id: topBar
            objectName: "topbarContainer"
            x: 0
            y: 0
            z: CONSTANTS.Z_TOPBAR
            width: CONSTANTS.SCREEN_WIDTH
            height: CONSTANTS.TOPBAR_HEIGHT
            source: DEFINES.PTR_TOPBAR
        }

        Loader {
            id: statusBar
            objectName: "statusbarContainer"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            z: CONSTANTS.Z_TOPBAR
            width: CONSTANTS.SCREEN_WIDTH
            height: CONSTANTS.TOPBAR_HEIGHT
            source: DEFINES.PTR_STATUSBAR
        }

        Loader {
            objectName: "overlayContainer"
            x: 0
            y: 0
            z: CONSTANTS.Z_POPUP
            width: CONSTANTS.SCREEN_WIDTH
            height: CONSTANTS.SCREEN_HEIGHT
        }

        Loader {
            objectName: "quicknotesContainer"
            x: 0
            y: 0
            z: CONSTANTS.Z_POPUP
            width: CONSTANTS.SCREEN_WIDTH
            height: CONSTANTS.SCREEN_HEIGHT
        }

        Loader {
            id: mainScreen
            objectName: "appContainer"
            x: 0
            y: CONSTANTS.TOPBAR_HEIGHT
            z: CONSTANTS.Z_APPMAIN
            width: CONSTANTS.SCREEN_WIDTH
            height: CONSTANTS.APP_HEIGHT
        }

        Loader {
            id: keyboard
            objectName: "keyboardContainer"
            x: 0
            y: 0
            z: CONSTANTS.Z_KEYBOARD
            width: CONSTANTS.SCREEN_WIDTH
            height: CONSTANTS.SCREEN_HEIGHT
        }

        Item {
            id: saveScreenshotButton
            width: 70
            height: 70
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            z: 9999
            MouseArea {
                anchors.fill: parent
                enabled: isScreenShotEnable
                onClicked: UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_BUTTON_DEVELOPER_SAVE_SCREENSHOT, "")
            }
        }
    }
}

