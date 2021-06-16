import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "../Js/Constants.js" as CONSTANTS
import "../Js/Defines.js" as DEFINES
import "../Js/Translations.js" as TRANS

Item {
    id: dataViewScreen
    objectName: "scr_home"
    width: CONSTANTS.SCREEN_WIDTH
    height: CONSTANTS.SCREEN_HEIGHT

    property bool isShowTopBar: false
    property bool isShowStatusBar: false

    Flickable {
        id: flickable
        width: parent.width
        height: parent.height
        contentWidth: parent.width * 2
        contentHeight: parent.height
        maximumFlickVelocity: 0
        contentX: currentPageIndex * CONSTANTS.SCREEN_WIDTH
//        flickDeceleration: 99999
        flickableDirection: Flickable.HorizontalFlick

        property int currentContentX: 0
        property int currentPageIndex: AppModel.historyHomePage

        Item {
            id: page0
            width: flickable.width
            height: flickable.height
            QAnalogClock {
                anchors.centerIn: parent
                width: 450
                height: 450
                secondImgSrc: "qrc:/resources/Image/AnalogClock/secondHand.png"
                faceClockImgSrc: "qrc:/resources/Image/AnalogClock/clockFace.png"
                hours: AppModel.systemHour
                minutes: AppModel.systemMinute
                seconds: AppModel.systemSecond
                asynchronous: true
            }
        }

        Item {
            id: page1
            x: flickable.width
            width: flickable.width
            height: flickable.height

            QHomeViewWidget {
                x: 190
                y: 0
                width: 300
                height: 300
                textContent: TRANS.STR_HOME_WORK
                onAppClick: UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_HOME_WORK_MAIN, "")
                normalSource: "qrc:/resources/Image/work.png"
            }

            QHomeViewWidget {
                x: 500
                y: 0
                width: 300
                height: 300
                textContent: TRANS.STR_HOME_SETTINGS
                onAppClick: UIBridge.hmiEvent("", HMIEvents.HMI_HOME_SETTING, "")
                normalSource: "qrc:/resources/Image/home_settings.png"
            }

            QHomeViewWidget {
                x: 810
                y: 0
                width: 300
                height: 300
                onAppClick: UIBridge.hmiEvent("", HMIEvents.HMI_HOME_DATAVIEW, "")
                normalSource: "qrc:/resources/Image/database.png"
                textContent: TRANS.STR_HOME_DATAVIEW
            }

            QHomeViewWidget {
                x: 190
                y: 310
                width: 300
                height: 300
                textContent: TRANS.STR_HOME_ABOUT
                normalSource: "qrc:/resources/Image/InfoIco.png"
            }
        }

        Behavior on contentX {
            NumberAnimation {
                duration: 100
            }
        }

        onDragStarted: currentContentX = flickable.contentX
        onDragEnded: {
            var balanceVelocity = 800
            if (flickable.contentX - currentContentX < CONSTANTS.SCREEN_WIDTH / 4
                    && flickable.contentX - currentContentX > -CONSTANTS.SCREEN_WIDTH / 4
                    && Math.abs(horizontalVelocity) < balanceVelocity) {
            } else {
                if (flickable.contentX > currentContentX) {
                    if(currentPageIndex < 1)
                        currentPageIndex++
                }
                else if (currentContentX >= CONSTANTS.SCREEN_WIDTH) {
                    if(currentPageIndex > 0)
                        currentPageIndex--
                }
            }
        }

        onMovementEnded: updateFlickableContentX()

        onCurrentPageIndexChanged: AppModel.historyHomePage = currentPageIndex

        function updateFlickableContentX() {
            contentX = currentPageIndex * CONSTANTS.SCREEN_WIDTH
        }
    }

    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10
        Rectangle {
            width: 10
            height: 10
            radius: 5
            border.width: 1
            border.color: "#FFFFFF"
            color: flickable.currentPageIndex == 0 ? "#FFFFFF" : "#000000"
        }
        Rectangle {
            width: 10
            height: 10
            radius: 5
            border.width: 1
            border.color: "#FFFFFF"
            color: flickable.currentPageIndex == 1 ? "#FFFFFF" : "#000000"
        }
    }
}
