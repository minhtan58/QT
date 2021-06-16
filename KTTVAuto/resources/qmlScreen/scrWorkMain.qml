import QtQuick 2.0
import HMIEvents 1.0
import "qrc:/resources/Widget"

Item {
    objectName: "scr_work_main"
    width: 1280; height: 660

    Connections {
        target: AppModel
    }

    Flickable {
        id: work_main
        width: 1280; height: 660
        contentHeight: 2200
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
            width: 600; height: 140
            groupTitle: "Hiện Tượng Thời Tiết"

            QTextInputWidget {
                id: work_weather_kyhieu
                objectName: "work_weather_kyhieu"
                x: 50; y: 40
                name: "Ký hiệu"
                onTextChanged: AppModel.work_weather_kyhieu = text
                text: AppModel.work_weather_kyhieu
            }

            QTextInputWidget {
                id: work_weather_batdau
                objectName: "work_weather_batdau"
                x: 220; y: 40
                name: "Bắt Đầu"
                onTextChanged: AppModel.work_weather_batdau = text
                text: AppModel.work_weather_batdau
            }

            QTextInputWidget {
                id: work_weather_ketthuc
                objectName: "work_weather_ketthuc"
                x: 390; y: 40
                name: "Kết thúc"
                onTextChanged: AppModel.work_weather_ketthuc = text
                text: AppModel.work_weather_ketthuc
            }
        }

        QGroupItem {
            x: 620; y: 160
            width: 590; height: 140
            groupTitle: "Mã Điện"

            QTextInputWidget {
                id: work_weather_ecode_hientuong1
                objectName: "work_weather_ecode_hientuong1"
                x: 50; y: 40
                name: "Hiện Tượng 1"
                onTextChanged: AppModel.work_weather_ecode_hientuong1 = text
                text: AppModel.work_weather_ecode_hientuong1
            }

            QTextInputWidget {
                id: work_weather_ecode_hientuong2
                objectName: "work_weather_ecode_hientuong2"
                x: 220; y: 40
                name: "Hiện Tượng 2"
                onTextChanged: AppModel.work_weather_ecode_hientuong2 = text
                text: AppModel.work_weather_ecode_hientuong2
            }

            QTextInputWidget {
                id: work_weather_ecode_hientuong3
                objectName: "work_weather_ecode_hientuong3"
                x: 390; y: 40
                name: "Hiện Tượng 3"
                onTextChanged: AppModel.work_weather_ecode_hientuong3 = text
                text: AppModel.work_weather_ecode_hientuong3
            }
        }

        QGroupItem {
            x: 20; y: 310
            width: 600; height: 140
            groupTitle: "Tầm Nhìn"

            QTextInputWidget {
                id: work_view_tieudiem
                objectName: "work_view_tieudiem"
                x: 50; y: 40
                name: "Tiêu Điểm"
                onTextChanged: AppModel.work_view_tieudiem = text
                text: AppModel.work_view_tieudiem
            }

            QTextInputWidget {
                id: work_view_khoangcach
                objectName: "work_view_khoangcach"
                x: 220; y: 40
                name: "Khoảng cách"
                onTextChanged: AppModel.work_view_khoangcach = text
                text: AppModel.work_view_khoangcach
            }

            QTextInputWidget {
                id: work_view_maso
                objectName: "work_view_maso"
                x: 390; y: 40
                name: "Mã Số"
                onTextChanged: AppModel.work_view_maso = text
                text: AppModel.work_view_maso
            }
        }

        QGroupItem {
            x: 620; y: 310
            width: 590; height: 140
            groupTitle: "Mã Điện"

            QTextInputWidget {
                id: work_view_ecode_tamnhin
                objectName: "work_view_ecode_tamnhin"
                x: 50; y: 40
                width: 500
                name: "Tầm Nhìn"
                onTextChanged: AppModel.work_view_ecode_tamnhin = text
                text: AppModel.work_view_ecode_tamnhin
            }
        }

        QGroupItem {
            x: 20; y: 460
            width: 600; height: 220
            groupTitle: "Mây"

            QTextInputWidget {
                id: work_cloud_tongquan
                objectName: "work_cloud_tongquan"
                x: 50; y: 40
                width: 320
                name: "Tổng quan"
                onTextChanged: AppModel.work_cloud_tongquan = text
                text: AppModel.work_cloud_tongquan
            }

            QTextInputWidget {
                id: work_cloud_mayduoi
                objectName: "work_cloud_mayduoi"
                x: 390; y: 40
                name: "Mây Dưới"
                onTextChanged: AppModel.work_cloud_mayduoi = text
                text: AppModel.work_cloud_mayduoi
            }
            QTextInputWidget {
                id: work_cloud_docao
                objectName: "work_cloud_docao"
                x: 50; y: 120
                width: 320
                name: "Độ Cao (m)"
                onTextChanged: AppModel.work_cloud_docao = text
                text: AppModel.work_cloud_docao
            }
        }

        QGroupItem {
            x: 620; y: 460
            width: 590; height: 220
            groupTitle: "Mã Điện"

            QTextInputWidget {
                id: work_cloud_ecode_nhom1
                objectName: "work_cloud_ecode_nhom1"
                x: 50; y: 40
                width: 320
                name: "Nhóm 1"
                onTextChanged: AppModel.work_cloud_ecode_nhom1 = text
                text: AppModel.work_cloud_ecode_nhom1
            }

            QTextInputWidget {
                id: work_cloud_ecode_nhom3lop1
                objectName: "work_cloud_ecode_nhom3lop1"
                x: 390; y: 40
                name: "Nhóm 3 (Lớp 1)"
                onTextChanged: AppModel.work_cloud_ecode_nhom3lop1 = text
                text: AppModel.work_cloud_ecode_nhom3lop1
            }
            QTextInputWidget {
                id: work_cloud_ecode_nhom3lop3
                objectName: "work_cloud_ecode_nhom3lop3"
                x: 50; y: 120
                name: "Nhóm 3 (Lớp 3)"
                onTextChanged: AppModel.work_cloud_ecode_nhom3lop3 = text
                text: AppModel.work_cloud_ecode_nhom3lop3
            }
            QTextInputWidget {
                id: work_cloud_ecode_nhom3lop5
                objectName: "work_cloud_ecode_nhom3lop5"
                x: 220; y: 120
                name: "Nhóm 3 (Lớp 5)"
                onTextChanged: AppModel.work_cloud_ecode_nhom3lop5 = text
                text: AppModel.work_cloud_ecode_nhom3lop5
            }
            QTextInputWidget {
                id: work_cloud_ecode_nhom3lop7
                objectName: "work_cloud_ecode_nhom3lop7"
                x: 390; y: 120
                name: "Nhóm 3 (Lớp 7)"
                onTextChanged: AppModel.work_cloud_ecode_nhom3lop7 = text
                text: AppModel.work_cloud_ecode_nhom3lop7
            }
        }

        QGroupItem {
            x: 20; y: 690
            width: 600; height: 140
            groupTitle: "Nhiệt Độ & Độ Ẩm Không Khí & Khí Áp"

            QTextInputWidget {
                id: work_thb_nhietdo
                objectName: "work_thb_nhietdo"
                x: 50; y: 40
                name: "Nhiệt Độ (°C)"
                onTextChanged: AppModel.work_thb_nhietdo = text
                text: AppModel.work_thb_nhietdo
            }

            QTextInputWidget {
                id: work_thb_doam
                objectName: "work_thb_doam"
                x: 220; y: 40
                name: "Độ Ẩm (%)"
                onTextChanged: AppModel.work_thb_doam = text
                text: AppModel.work_thb_doam
            }

            QTextInputWidget {
                id: work_thb_khiap
                objectName: "work_thb_khiap"
                x: 390; y: 40
                name: "Khí Áp (hPa)"
                onTextChanged: AppModel.work_thb_khiap = text
                text: AppModel.work_thb_khiap
            }
        }

        QGroupItem {
            x: 620; y: 690
            width: 590; height: 140
            groupTitle: "Mã Điện"

            QTextInputWidget {
                id: work_thb_ecode_nhietdo
                objectName: "work_thb_ecode_nhietdo"
                x: 50; y: 40
                name: "Nhiệt Độ"
                onTextChanged: AppModel.work_thb_ecode_nhietdo = text
                text: AppModel.work_thb_ecode_nhietdo
            }

            QTextInputWidget {
                id: work_thb_ecode_doam
                objectName: "work_thb_ecode_doam"
                x: 220; y: 40
                name: "Độ Ẩm"
                onTextChanged: AppModel.work_thb_ecode_doam = text
                text: AppModel.work_thb_ecode_doam
            }

            QTextInputWidget {
                id: work_thb_ecode_khiap
                objectName: "work_thb_ecode_khiap"
                x: 390; y: 40
                name: "Khí Áp"
                onTextChanged: AppModel.work_thb_ecode_khiap = text
                text: AppModel.work_thb_ecode_khiap
            }
        }

        QGroupItem {
            x: 20; y: 840
            width: 600; height: 140
            groupTitle: "Nhiệt Kế"

            QTextInputWidget {
                id: work_thermometer_nhietdokho
                objectName: "work_thermometer_nhietdokho"
                x: 50; y: 40
                name: "Nhiệt Độ Khô"
                onTextChanged: AppModel.work_thermometer_nhietdokho = text
                text: AppModel.work_thermometer_nhietdokho
            }

            QTextInputWidget {
                id: work_thermometer_tgnmatruou
                objectName: "work_thermometer_tgnmatruou"
                x: 220; y: 40
                name: "Tgn.mắt rượu"
                onTextChanged: AppModel.work_thermometer_tgnmatruou = text
                text: AppModel.work_thermometer_tgnmatruou
            }

            QTextInputWidget {
                id: work_thermometer_tgxmathg
                objectName: "work_thermometer_tgxmathg"
                x: 390; y: 40
                name: "Tgx.mặt Hg"
                onTextChanged: AppModel.work_thermometer_tgxmathg = text
                text: AppModel.work_thermometer_tgxmathg
            }
        }

        QGroupItem {
            x: 620; y: 840
            width: 590; height: 140
            groupTitle: "Mã Điện"

            QTextInputWidget {
                id: work_thermometer_ecode_nhietdokho
                objectName: "work_thermometer_ecode_nhietdokho"
                x: 50; y: 40
                name: "Nhiệt Độ Khô"
                onTextChanged: AppModel.work_thermometer_ecode_nhietdokho = text
                text: AppModel.work_thermometer_ecode_nhietdokho
            }

            QTextInputWidget {
                id: work_thermometer_ecode_tgnmatruou
                objectName: "work_thermometer_ecode_tgnmatruou"
                x: 220; y: 40
                name: "Tgn.mắt rượu"
                onTextChanged: AppModel.work_thermometer_ecode_tgnmatruou = text
                text: AppModel.work_thermometer_ecode_tgnmatruou
            }

            QTextInputWidget {
                id: work_thermometer_ecode_tgxmathg
                objectName: "work_thermometer_ecode_tgxmathg"
                x: 390; y: 40
                name: "Tgx.mặt Hg"
                onTextChanged: AppModel.work_thermometer_ecode_tgxmathg = text
                text: AppModel.work_thermometer_ecode_tgxmathg
            }
        }

        QGroupItem {
            x: 20; y: 990
            width: 600; height: 300
            groupTitle: "Khí Áp Kế"

            QTextInputWidget {
                id: work_gauge_nhietkephu
                objectName: "work_gauge_nhietkephu"
                x: 50; y: 40
                name: "Nhiệt kế phụ"
                onTextChanged: AppModel.work_gauge_nhietkephu = text
                text: AppModel.work_gauge_nhietkephu
            }

            QTextInputWidget {
                id: work_gauge_apkesodoc
                objectName: "work_gauge_apkesodoc"
                x: 220; y: 40
                name: "P Kế.số đọc"
                onTextChanged: AppModel.work_gauge_apkesodoc = text
                text: AppModel.work_gauge_apkesodoc
            }

            QTextInputWidget {
                id: work_gauge_apkehieuchinh
                objectName: "work_gauge_apkehieuchinh"
                x: 390; y: 40
                name: "P Kế.H/C"
                onTextChanged: AppModel.work_gauge_apkehieuchinh = text
                text: AppModel.work_gauge_apkehieuchinh
            }

            QTextInputWidget {
                id: work_gauge_apkemattram
                objectName: "work_gauge_apkemattram"
                x: 50; y: 120
                name: "P Kế.mặt trạm"
                onTextChanged: AppModel.work_gauge_apkemattram = text
                text: AppModel.work_gauge_apkemattram
            }

            QTextInputWidget {
                id: work_gauge_bienthien3h
                objectName: "work_gauge_bienthien3h"
                x: 220; y: 120
                name: "Biến thiên 3 giờ"
                onTextChanged: AppModel.work_gauge_bienthien3h = text
                text: AppModel.work_gauge_bienthien3h
            }

            QTextInputWidget {
                id: work_gauge_mbhieuchinh
                objectName: "work_gauge_mbhieuchinh"
                x: 390; y: 120
                name: "MB.hiệu chính"
                onTextChanged: AppModel.work_gauge_mbhieuchinh = text
                text: AppModel.work_gauge_mbhieuchinh
            }

            QTextInputWidget {
                id: work_gauge_mbdahieuchinh
                objectName: "work_gauge_mbdahieuchinh"
                x: 50; y: 200
                name: "MB.đãHiệuChính"
                onTextChanged: AppModel.work_gauge_mbdahieuchinh = text
                text: AppModel.work_gauge_mbdahieuchinh
            }

            QTextInputWidget {
                id: work_gauge_apky
                objectName: "work_gauge_apky"
                x: 220; y: 200
                name: "Áp ký"
                onTextChanged: AppModel.work_gauge_apky = text
                text: AppModel.work_gauge_apky
            }

            QTextInputWidget {
                id: work_gauge_p24h
                objectName: "work_gauge_p24h"
                x: 390; y: 200
                name: "P24h"
                onTextChanged: AppModel.work_gauge_p24h = text
                text: AppModel.work_gauge_p24h
            }
        }

        QGroupItem {
            x: 620; y: 990
            width: 590; height: 300
            groupTitle: "Mã Điện"

            QTextInputWidget {
                id: work_gauge_ecode_nhietkephu
                objectName: "work_gauge_ecode_nhietkephu"
                x: 50; y: 40
                name: "Nhiệt kế phụ"
                onTextChanged: AppModel.work_gauge_ecode_nhietkephu = text
                text: AppModel.work_gauge_ecode_nhietkephu
            }

            QTextInputWidget {
                id: work_gauge_ecode_apkesodoc
                objectName: "work_gauge_ecode_apkesodoc"
                x: 220; y: 40
                name: "P Kế.số đọc"
                onTextChanged: AppModel.work_gauge_ecode_apkesodoc = text
                text: AppModel.work_gauge_ecode_apkesodoc
            }

            QTextInputWidget {
                id: work_gauge_ecode_apkehc
                objectName: "work_gauge_ecode_apkehc"
                x: 390; y: 40
                name: "P Kế.H/C"
                onTextChanged: AppModel.work_gauge_ecode_apkehc = text
                text: AppModel.work_gauge_ecode_apkehc
            }

            QTextInputWidget {
                id: work_gauge_ecode_apkemattram
                objectName: "work_gauge_ecode_apkemattram"
                x: 50; y: 120
                name: "P Kế.mặt trạm"
                onTextChanged: AppModel.work_gauge_ecode_apkemattram = text
                text: AppModel.work_gauge_ecode_apkemattram
            }

            QTextInputWidget {
                id: work_gauge_ecode_bienthien3h
                objectName: "work_gauge_ecode_bienthien3h"
                x: 220; y: 120
                name: "Biến thiên 3 giờ"
                onTextChanged: AppModel.work_gauge_ecode_bienthien3h = text
                text: AppModel.work_gauge_ecode_bienthien3h
            }

            QTextInputWidget {
                id: work_gauge_ecode_mbhieuchinh
                objectName: "work_gauge_ecode_mbhieuchinh"
                x: 390; y: 120
                name: "MB.hiệu chính"
                onTextChanged: AppModel.work_gauge_ecode_mbhieuchinh = text
                text: AppModel.work_gauge_ecode_mbhieuchinh
            }

            QTextInputWidget {
                id: work_gauge_ecode_mbdahieuchinh
                objectName: "work_gauge_ecode_mbdahieuchinh"
                x: 50; y: 200
                name: "MB.đãHiệuChính"
                onTextChanged: AppModel.work_gauge_ecode_mbdahieuchinh = text
                text: AppModel.work_gauge_ecode_mbdahieuchinh
            }

            QTextInputWidget {
                id: work_gauge_ecode_apky
                objectName: "work_gauge_ecode_apky"
                x: 220; y: 200
                name: "Áp ký"
                onTextChanged: AppModel.work_gauge_ecode_apky = text
                text: AppModel.work_gauge_ecode_apky
            }

            QTextInputWidget {
                id: work_gauge_ecode_p24h
                objectName: "work_gauge_ecode_p24h"
                x: 390; y: 200
                name: "P24h"
                onTextChanged: AppModel.work_gauge_ecode_p24h = text
                text: AppModel.work_gauge_ecode_p24h
            }
        }

        QGroupItem {
            x: 20; y: 1300
            width: 600
            height: 140
            groupTitle: "Gió"

            QTextInputWidget {
                id: work_wind_ff
                objectName: "work_wind_ff"
                x: 50; y: 40
                name: "ff (m/s)"
                onTextChanged: AppModel.work_wind_ff = text
                text: AppModel.work_wind_ff
            }

            QTextInputWidget {
                id: work_wind_dd
                objectName: "work_wind_dd"
                x: 220; y: 40
                name: "dd"
                onTextChanged: AppModel.work_wind_dd = text
                text: AppModel.work_wind_dd
            }

            QTextInputWidget {
                id: work_wind_dacdiem
                objectName: "work_wind_dacdiem"
                x: 390; y: 40
                name: "Đặc điểm"
                onTextChanged: AppModel.work_wind_dacdiem = text
                text: AppModel.work_wind_dacdiem
            }
        }

        QGroupItem {
            x: 620; y: 1300
            width: 590; height: 140
            groupTitle: "Mã Điện"

            QTextInputWidget {
                id: work_wind_ecode_ff
                objectName: "work_wind_ecode_ff"
                x: 50; y: 40
                name: "ff"
                onTextChanged: AppModel.work_wind_ecode_ff = text
                text: AppModel.work_wind_ecode_ff
            }

            QTextInputWidget {
                id: work_wind_ecode_dd
                objectName: "work_wind_ecode_dd"
                x: 220; y: 40
                name: "dd"
                onTextChanged: AppModel.work_wind_ecode_dd = text
                text: AppModel.work_wind_ecode_dd
            }

            QTextInputWidget {
                id: work_wind_ecode_dacdiem
                objectName: "work_wind_ecode_dacdiem"
                x: 390; y: 40
                name: "Đặc điểm"
                onTextChanged: AppModel.work_wind_ecode_dacdiem = text
                text: AppModel.work_wind_ecode_dacdiem
            }
        }

        QGroupItem {
            x: 20; y: 1450
            width: 600; height: 140
            groupTitle: "Mưa"

            QTextInputWidget {
                id: work_rain_1h
                objectName: "work_rain_1h"
                x: 50; y: 40
                name: "Mưa 1h (mm)"
                onTextChanged: AppModel.work_rain_1h = text
                text: AppModel.work_rain_1h
            }

            QTextInputWidget {
                id: work_rain_24h
                objectName: "work_rain_24h"
                x: 220; y: 40
                name: "Mưa 24h (mm)"
                onTextChanged: AppModel.work_rain_24h = text
                text: AppModel.work_rain_24h
            }
        }

        QGroupItem {
            x: 620; y: 1450
            width: 590; height: 140
            groupTitle: "Mã Điện"

            QTextInputWidget {
                id: work_rain_ecode_1h
                objectName: "work_rain_ecode_1h"
                x: 50; y: 40
                name: "Mưa 1h (mm)"
                onTextChanged: AppModel.work_rain_ecode_1h = text
                text: AppModel.work_rain_ecode_1h
            }

            QTextInputWidget {
                id: work_rain_ecode_24h
                objectName: "work_rain_ecode_24h"
                x: 220; y: 40
                name: "Mưa 24h (mm)"
                onTextChanged: AppModel.work_rain_ecode_24h = text
                text: AppModel.work_rain_ecode_24h
            }
        }

        QGroupItem {
            x: 20; y: 1600
            width: 1190; height: 430
            groupTitle: "Dữ Liệu"

            QTextEdit {
                id: work_ecode_final
                objectName: "work_ecode_final"
                x: 50; y: 50
                width: 1090
                height: 300
                verticalAlignment: Text.AlignTop
                onTextChanged: AppModel.workMainText = text
                text: AppModel.workMainText
            }

            QButton {
                x: 210; y: 360
                width: 150; height: 50
                text: "Tạo Bản Tin"
                eventID: HMIEvents.HMI_BUTTON_GENERATE_WORK_MAIN_TEXT
            }

            QButton {
                x: 50; y: 360
                width: 150; height: 50
                text: "Gửi"
                eventID: HMIEvents.HMI_BUTTON_WORK_MAIN_SEND
            }
        }
    }

    QScrollBar {
        id: work_scroll
        flickable: work_main
        x: flickable.width - 65; y: 20
        width: 60; height: flickable.height - 40
    }
}
