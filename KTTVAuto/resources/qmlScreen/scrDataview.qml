import QtQuick 2.0
import QtQuick.Controls 1.4
import HMIEvents 1.0
import "qrc:/resources/Widget"
import "qrc:/resources/qmlScreen/ListDelegate"
import "../Js/Constants.js" as CONSTANTS

Item {
    width: CONSTANTS.SCREEN_WIDTH
    height: CONSTANTS.APP_HEIGHT
    objectName: "scr_dataview"
    QText {
        text: "Từ: "
        width: 50; height: 40
        x: 20; y: 15
    }
    QDatePicker {
        id: dateStart
        x: 70; y: 15; z: 1
        width: 300; height: 40
        datetime: AppModel.dataviewSearchDateStart
    }

    QText {
        text: "Đến: "
        width: 50; height: 40
        x: 400; y: 15
    }

    QDatePicker {
        id: dateEnd
        x: 460; y: 15; z: 1
        width: 300; height: 40
        datetime: AppModel.dataviewSearchDateEnd
    }

    QButton {
        x: 800; y: 15
        width: 150; height: 40
        text: "Lọc"
        eventID: HMIEvents.HMI_REQUEST_GET_DATAVIEW_LIST
        params: [dateStart.datetime, dateEnd.datetime]
    }

    QListView {
        id: listDataview
        anchors.fill: parent
        anchors {topMargin: 70; leftMargin: 20; rightMargin: 20; bottomMargin: 20}
        delegate: DataviewDelegate {}
        snapMode: ListView.SnapOneItem
        emptyText: "No History"
        model: dataviewModel
        header: DataviewHeader {width: listDataview.width}
    }
    Component.onCompleted: UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_REQUEST_GET_DATAVIEW_LIST, AppModel.dataviewSearchDateStart + "" + AppModel.dataviewSearchDateEnd)
    Component.onDestruction: UIBridge.hmiEvent(this.objectName, HMIEvents.HMI_REQUEST_DELETE_DATAVIEW_LIST, "")
}
