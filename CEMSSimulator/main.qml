import QtQuick 2.0
import QtQuick.Window 2.0
import "Widget"

Window {
    visible: true
    width: 700
    height: 500
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
    color: "steelblue"

    readonly property int marginX: 350
    readonly property int headerWidth: 100


    Text {
        x: 30
        y: 50
        width: headerWidth
        height: 40
        text: "Sim Type"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QComboBox {
        id: simType
        x: 30 + headerWidth
        y: 50
        width: 150
        height: 40
        model: ["Random", "Fixed"]
        currentIndex: SIM.isFixed
        onCurrentIndexChanged: SIM.isFixed = (currentIndex == 1)
    }

    Text {
        x: 30
        y: 100
        width: headerWidth
        height: 40
        text: "COM:"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QComboBox {
        id: portName
        x: 30 + headerWidth
        y: 100
        width: 150
        height: 40
        model: ["COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9"]
        currentIndex: 0
    }

    Text {
        x: 30
        y: 150
        width: headerWidth
        height: 40
        text: "Baudrate:"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QComboBox {
        id: baudrare
        x: 30 + headerWidth
        y: 150
        width: 150
        height: 40
        model: ["4800", "9600", "19200", "38400", "57600", "115200"]
        currentIndex: 5
    }

    Text {
        x: 30
        y: 200
        width: headerWidth + 150
        height: 40
        text: "Status: " + (SIM.isConnected ? "Connected" : "No Connect")
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QButton {
        x: 30
        y: 250
        width: 250
        height: 40
        text: SIM.isConnected ? "Disconnect" : "Connect"
        onButtonClicked: SIM.connectSerialPort(portName.model[portName.currentIndex], Number(baudrare.model[baudrare.currentIndex]))
    }

    Text {
        x: marginX
        y: 50
        width: headerWidth
        height: 40
        text: "O\u2082"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QTextInput {
        id: componentO2
        x: marginX + headerWidth
        y: 50
        width: 200
        height: 40
        enabled: simType.currentIndex == 1
        text: SIM.componentO2
    }

    Text {
        x: marginX
        y: 100
        width: headerWidth
        height: 40
        text: "CO"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QTextInput {
        id: componentCO
        x: marginX + headerWidth
        y: 100
        width: 200
        height: 40
        enabled: simType.currentIndex == 1
        text: SIM.componentCO
    }

    Text {
        x: marginX
        y: 150
        width: headerWidth
        height: 40
        text: "NO"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QTextInput {
        id: componentNO
        x: marginX + headerWidth
        y: 150
        width: 200
        height: 40
        enabled: simType.currentIndex == 1
        text: SIM.componentNO
    }

    Text {
        x: marginX
        y: 200
        width: headerWidth
        height: 40
        text: "SO\u2082"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QTextInput {
        id: componentSO2
        x: marginX + headerWidth
        y: 200
        width: 200
        height: 40
        enabled: simType.currentIndex == 1
        text: SIM.componentSO2
    }

    Text {
        x: marginX
        y: 250
        width: headerWidth
        height: 40
        text: "Temperature"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        elide: Text.ElideRight
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QTextInput {
        id: componentTEMP
        x: marginX + headerWidth
        y: 250
        width: 200
        height: 40
        enabled: simType.currentIndex == 1
        text: SIM.componentTEMP
    }

    Text {
        x: marginX
        y: 300
        width: headerWidth
        height: 40
        text: "Oppacity"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QTextInput {
        id: componentOPP
        x: marginX + headerWidth
        y: 300
        width: 200
        height: 40
        enabled: simType.currentIndex == 1
        text: SIM.componentOPP
    }

    Text {
        x: marginX
        y: 350
        width: headerWidth
        height: 40
        text: "Velocity"
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 20
        wrapMode: Text.Wrap
    }

    QTextInput {
        id: componentVEL
        x: marginX + headerWidth
        y: 350
        width: 200
        height: 40
        enabled: simType.currentIndex == 1
        text: SIM.componentVEL
    }

    QButton {
        x: marginX
        y: 400
        width: 300
        height: 40
        text: "SAVE"
        isEnabled: simType.currentIndex == 1
        onButtonClicked: {
            SIM.componentO2 = componentO2.text
            SIM.componentCO = componentCO.text
            SIM.componentNO = componentNO.text
            SIM.componentSO2 = componentSO2.text
            SIM.componentTEMP = componentTEMP.text
            SIM.componentOPP = componentOPP.text
            SIM.componentVEL = componentVEL.text
        }
    }
}
