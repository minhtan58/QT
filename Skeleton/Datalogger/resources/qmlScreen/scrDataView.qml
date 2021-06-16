import QtQuick 2.0
import CEMSEnum 1.0
import "../Widget"

Item {
    id: dataViewScreen
    objectName: "scr_dataview"
    anchors.fill: parent

    property int modeViewAir: 0
    property int modeViewCO: 0  //0 - standard, 1 - ppm
    property int modeViewNO: 0
    property int modeViewNOX: 0
    property int modeViewSO2: 0
    readonly property string unitAirPpm: "ppm"
    readonly property string unitAirSTD: "mg/Nm\u00B3"

    readonly property int viewX: 10
    readonly property int viewSpacing: 7

    QViewWidget {
        id: viewO2
        objectName: "viewO2"
        x: viewX
        y: viewSpacing
        textName: "O\u2082"
        textUnit: "%V"
    }

    QViewWidget {
        id: viewCO
        objectName: "viewCO"
        x: viewX
        y: viewO2.y + viewO2.height + viewSpacing
        textName: "CO"
        textUnit: !modeViewCO ? unitAirSTD : unitAirPpm
        onViewClicked: {
            Delivery.hmiEvent(this.objectName, CEMSEnum.HMI_DATAVIEW_SWITCH_UNIT, 1 - modeViewCO)
        }
    }

    QViewWidget {
        id: viewNO
        objectName: "viewNO"
        x: viewX
        y: viewCO.y + viewCO.height + viewSpacing
        textName: "NO"
        textUnit: !modeViewNO ? unitAirSTD : unitAirPpm
        onViewClicked: {
            Delivery.hmiEvent(this.objectName, CEMSEnum.HMI_DATAVIEW_SWITCH_UNIT, 1 - modeViewNO)
        }
    }

    QViewWidget {
        id: viewNOX
        objectName: "viewNOX"
        x: viewX
        y: viewNO.y + viewNO.height + viewSpacing
        textName: "NOx"
        textUnit: !modeViewNOX ? unitAirSTD : unitAirPpm
        onViewClicked: {
            Delivery.hmiEvent(this.objectName, CEMSEnum.HMI_DATAVIEW_SWITCH_UNIT, 1 - modeViewNOX)
        }
    }

    QViewWidget {
        id: viewSO2
        objectName: "viewSO2"
        x: viewX
        y: viewNOX.y + viewNOX.height + viewSpacing
        textName: "SO\u2082"
        textUnit: !modeViewSO2 ? unitAirSTD : unitAirPpm
        onViewClicked: {
            Delivery.hmiEvent(this.objectName, CEMSEnum.HMI_DATAVIEW_SWITCH_UNIT, 1 - modeViewSO2)
        }
    }

    QViewWidget {
        id: viewTEMP
        objectName: "viewTEMP"
        x: viewO2.x + viewO2.width + viewSpacing
        y: viewO2.y
        textName: "Temperature"
        textUnit: "\u00B0C"
    }

    QViewWidget {
        id: viewOPP
        objectName: "viewOPP"
        x: viewTEMP.x
        y: viewCO.y
        textName: "Oppacity"
        textUnit: "%"
    }

    QViewWidget {
        id: viewDUSTPM
        objectName: "viewDUSTPM"
        x: viewTEMP.x
        y: viewNO.y
        textName: "Dust PM"
        textUnit: "mg/Nm\u00B3"
    }

    QViewWidget {
        id: viewVEL
        objectName: "viewVEL"
        x: viewTEMP.x
        y: viewNOX.y
        textName: "Velocity"
        textUnit: "m/s"
    }

    QViewWidget {
        id: viewFLOW
        objectName: "viewFLOW"
        x: viewTEMP.x
        y: viewSO2.y
        textName: "Flow"
        textUnit: "m\u00B3/s"
//        Image {
//            anchors.top: parent.top
//            anchors.right: parent.right
//            anchors.bottom: parent.bottom
//            width: parent.width/3
//            height: parent.height
//        }
//        onViewPressAndHold: Delivery.hmiEvent(this.objectName, CEMSEnum.HMI_DATAVIEW_SWITCH_UNIT, 1 - modeViewSO2)
    }
}
