import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"

Item {
    objectName: "scr_work_haivan"
    width: 1280; height: 1000

    Flickable {
        id: work_haivan
        anchors.fill: parent
        contentHeight: 1000
        flickableDirection: Flickable.VerticalFlick
        clip: true

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
            width: 600; height: 220
            groupTitle: "Thông Tin Hải Văn"

            QTextInputWidget {
                id: work_haivan_wind_ff
                objectName: "work_haivan_wind_ff"
                x: 50; y: 40
                name: "ff (m/s)"
                onTextChanged: AppModel.work_haivan_wind_ff = text
                text: AppModel.work_haivan_wind_ff
            }

            QTextInputWidget {
                id: work_haivan_wind_dd
                objectName: "work_haivan_wind_dd"
                x: 220; y: 40
                name: "dd"
                onTextChanged: AppModel.work_haivan_wind_dd = text
                text: AppModel.work_haivan_wind_dd
            }
            QTextInputWidget {
                id: work_haivan_mucnuoc
                objectName: "work_haivan_mucnuoc"
                x: 50; y: 120
                name: "Mực nước (m)"
                onTextChanged: AppModel.work_haivan_mucnuoc = text
                text: AppModel.work_haivan_mucnuoc
            }
            QTextInputWidget {
                id: work_haivan_nhietmuoi
                objectName: "work_haivan_nhietmuoi"
                x: 220; y: 120
                name: "Nhiệt muối (°C)"
                onTextChanged: AppModel.work_haivan_nhietmuoi = text
                text: AppModel.work_haivan_nhietmuoi
            }
            QTextInputWidget {
                id: work_haivan_song
                objectName: "work_haivan_song"
                x: 390; y: 120
                name: "Sóng (Ω.m)"
                onTextChanged: AppModel.work_haivan_song = text
                text: AppModel.work_haivan_song
            }
        }

        QGroupItem {
            x: 620; y: 160
            width: 590; height: 220
            groupTitle: "Mã Điện"

            QTextInputWidget {
                id: work_haivan_wind_ecode_ff
                objectName: "work_haivan_wind_ecode_ff"
                x: 50; y: 40
                name: "ff (m/s)"
                onTextChanged: AppModel.work_haivan_wind_ecode_ff = text
                text: AppModel.work_haivan_wind_ecode_ff
            }

            QTextInputWidget {
                id: work_haivan_wind_ecode_dd
                objectName: "work_haivan_wind_ecode_dd"
                x: 220; y: 40
                name: "dd"
                onTextChanged: AppModel.work_haivan_wind_ecode_dd = text
                text: AppModel.work_haivan_wind_ecode_dd
            }
            QTextInputWidget {
                id: work_haivan_ecode_mucnuoc
                objectName: "work_haivan_ecode_mucnuoc"
                x: 50; y: 120
                name: "Mực nước (m)"
                onTextChanged: AppModel.work_haivan_ecode_mucnuoc = text
                text: AppModel.work_haivan_ecode_mucnuoc
            }
            QTextInputWidget {
                id: work_haivan_ecode_nhietmuoi
                objectName: "work_haivan_ecode_nhietmuoi"
                x: 220; y: 120
                name: "Nhiệt muối (°C)"
                onTextChanged: AppModel.work_haivan_ecode_nhietmuoi = text
                text: AppModel.work_haivan_ecode_nhietmuoi
            }
            QTextInputWidget {
                id: work_haivan_ecode_song
                objectName: "work_haivan_ecode_song"
                x: 390; y: 120
                name: "Sóng (Ω.m)"
                onTextChanged: AppModel.work_haivan_ecode_song = text
                text: AppModel.work_haivan_ecode_song
            }
        }

        QGroupItem {
            x: 20; y: 390
            width: 1190; height: 430
            groupTitle: "Dữ Liệu"

            QTextEdit {
                id: work_haivan_send_text
                objectName: "work_haivan_send_text"
                x: 50; y: 50
                width: 1090
                height: 300
                verticalAlignment: Text.AlignTop
                text: AppModel.work_haivan_send_text
                onTextChanged: AppModel.work_haivan_send_text = text
            }

            QButton {
                x: 50; y: 360
                width: 150; height: 50
                text: "Gửi"
//                eventID: HMIEvents.HMI_BUTTON_WORK_SIMPLE_SEND
            }
        }
    }

    QScrollBar {
        id: work_scroll
        flickable: work_haivan
        x: flickable.width - 65; y: 20
        width: 60; height: flickable.height - 40
    }
}
