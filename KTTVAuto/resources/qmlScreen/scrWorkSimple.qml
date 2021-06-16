import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"

Item {
    objectName: "scr_work_simple"
    width: 1280; height: 660

    QGroupItem {
        x: 20; y: 10
        width: 600; height: 140
        groupTitle: "Thông Tin Quan Trắc"

        QTextInputWidget {
            id: work_station_matram
            objectName: "work_station_matram"
            x: 50; y: 40
            name: "Mã Trạm"
            text: AppModel.deviceCode
            readOnly: true
        }

        QTextInputWidget {
            id: work_station_quantracvien
            objectName: "work_station_quantracvien"
            x: 220; y: 40
            width: 320
            name: "Quan trắc viên"
            text: AppModel.userFullName
            readOnly: true
        }
    }

    QGroupItem {
        x: 620; y: 10; z: 1
        width: 590; height: 140
        groupTitle: ""

        QText {
            x: 50; y: 40
            width: 150; height: 40
            horizontalAlignment: Text.AlignHCenter
            text: "Obs (h)"
        }

        QComboBox {
            objectName: "work_station_obs"
            x: 50; y: 80; z: 1
            width: 150; height: 40
            model: ["01", "07", "13", "19"]
            currentValue: AppModel.work_station_obs.length > 0 ? AppModel.work_station_obs : model[0]
            onCurrentValueChanged: {
                if(AppModel.work_station_obs !== currentValue)
                    AppModel.work_station_obs = currentValue
            }
        }

        QTextInputWidget {
            id: work_station_ngay
            objectName: "work_station_ngay"
            x: 220; y: 40
            name: "Ngày"
            text: AppModel.systemDate
            width: 320
        }
    }

    QGroupItem {
        x: 20; y: 160
        width: 1190; height: 430
        groupTitle: "Dữ Liệu"

        QTextEdit {
            id: work_simple_text
            objectName: "work_simple_text"
            x: 50; y: 50
            width: 1090
            height: 300
            verticalAlignment: Text.AlignTop
            text: AppModel.workSimpleText
            onTextChanged: AppModel.workSimpleText = text
        }

        QButton {
            x: 50; y: 360
            width: 150; height: 50
            text: "Gửi"
            eventID: HMIEvents.HMI_BUTTON_WORK_SIMPLE_SEND
        }
    }
}
