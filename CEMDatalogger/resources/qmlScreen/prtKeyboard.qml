import QtQuick 2.0
import "../Widget"

Item {
    objectName: "keyboard_full_character"
    property int keyboardType: typeCap

    readonly property int typeSmall: 0
    readonly property int typeCap: 1
    readonly property int typeNumber: 2
    readonly property int typeSpecial: 3

    Rectangle {
        x: 0
        y: 240
        width: 800
        height: 240
        color: "#000000"
    }

    Item {
        QKeyWidget {
            id: ui_q_caps
            objectName: "ui_q_caps"
            x: 0
            y: 248
            keyTextList: ["q","Q","1","~"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_w_caps
            objectName: "ui_w_caps"
            x: 80
            y: 248
            keyTextList: ["w","W","2","`"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_e_caps
            objectName: "ui_e_caps"
            x: 160
            y: 248
            keyTextList: ["e","E","3","|"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_r_caps
            objectName: "ui_r_caps"
            x: 240
            y: 248
            keyTextList: ["r","R","4","•"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_t_caps
            objectName: "ui_t_caps"
            x: 320
            y: 248
            keyTextList: ["t","T","5","√"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_y_caps
            objectName: "ui_y_caps"
            x: 400
            y: 248
            keyTextList: ["y","Y","6","π"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_u_caps
            objectName: "ui_u_caps"
            x: 480
            y: 248
            keyTextList: ["u","U","7","÷"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_i_caps
            objectName: "ui_i_caps"
            x: 560
            y: 248
            keyTextList: ["i","I","8","×"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_o_caps
            objectName: "ui_o_caps"
            x: 640
            y: 248
            keyTextList: ["o","O","9","¶"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_p_caps
            objectName: "ui_p_caps"
            x: 720
            y: 248
            keyTextList: ["p","P","0","∆"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_a_caps
            objectName: "ui_a_caps"
            x: 40
            y: 306
            keyTextList: ["a","A","@","€"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_s_caps
            objectName: "ui_s_caps"
            x: 120
            y: 306
            keyTextList: ["s","S","#","¥"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_d_caps
            objectName: "ui_d_caps"
            x: 200
            y: 306
            keyTextList: ["d","D","£","$"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_f_caps
            objectName: "ui_f_caps"
            x: 280
            y: 306
            keyTextList: ["f","F","%","¢"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_g_caps
            objectName: "ui_g_caps"
            x: 360
            y: 306
            keyTextList: ["g","G","&","^"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_h_caps
            objectName: "ui_h_caps"
            x: 440
            y: 306
            keyTextList: ["h","H","-","°"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_j_caps
            objectName: "ui_j_caps"
            x: 520
            y: 306
            keyTextList: ["j","J","+","="]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_k_caps
            objectName: "ui_k_caps"
            x: 600
            y: 306
            keyTextList: ["k","K","(","{"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_l_caps
            objectName: "ui_l_caps"
            x: 680
            y: 306
            keyTextList: ["l","L",")","}"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: img_keyboard_shiftkey_selector
            objectName: "img_keyboard_shiftkey_selector"
            x: 0
            y: 364
            keyFunction: functionCtrl
            keySize: sizeKeyCtrl
            keyImage: "qrc:/resources/Image/" + (keyboardType === typeCap ? "shift_press" : "shift_normal") + ".png"
            onKeyCtrlClicked: {
                UIBridge.keyboardEvent(1, "shift_clicked")
            }
            onKeyCtrlPressAndHold: {
                UIBridge.keyboardEvent(1, "shift_hold")
            }
        }
        QKeyWidget {
            id: ui_z_caps
            objectName: "ui_z_caps"
            x: 120
            y: 364
            keyTextList: ["z","Z","*","\\"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_x_caps
            objectName: "ui_x_caps"
            x: 200
            y: 364
            keyTextList: ["x","X","\"","©"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_c_caps
            objectName: "ui_c_caps"
            x: 280
            y: 364
            keyTextList: ["c","C","\'","®"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_v_caps
            objectName: "ui_v_caps"
            x: 360
            y: 364
            keyTextList: ["v","V",":","™"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_b_caps
            objectName: "ui_b_caps"
            x: 440
            y: 364
            keyTextList: ["b","B",";","℅"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_n_caps
            objectName: "ui_n_caps"
            x: 520
            y: 364
            keyTextList: ["n","N","!","["]
            keyState: keyboardType
        }
        QKeyWidget {
            id: ui_m_caps
            objectName: "ui_m_caps"
            x: 600
            y: 364
            keyTextList: ["m","M","?","]"]
            keyState: keyboardType
        }
        QKeyWidget {
            id: img_keyboard_backspace
            objectName: "img_keyboard_backspace"
            x: 680
            y: 364
            keyFunction: functionCtrl
            keySize: sizeKeyCtrl
            keyImage: "qrc:/resources/Image/backspace_normal.png"
            onKeyCtrlClicked: {
                UIBridge.keyboardEvent(1, "delete_clicked")
            }
            onKeyCtrlPressAndHold: {
                UIBridge.keyboardEvent(1, "delete_hold")
            }
        }
        QKeyWidget {
            id: ui_qn123
            objectName: "ui_qn123"
            property int kbType: typeCap
            x: 0
            y: 422
            keyFunction: functionCtrl
            keySize: sizeKeyCtrl
            keyText: "123"
            onKeyCtrlClicked: {
                if(keyboardType == typeCap || keyboardType == typeSmall)
                    keyboardType = typeNumber
                else if(keyboardType == typeNumber || keyboardType == typeSpecial)
                    keyboardType = typeCap
            }
        }
        QKeyWidget {
            id: img_globe_icon
            objectName: "img_globe_icon"
            x: 120
            y: 422
            keySize: sizeKeyNormal
            keyText: ","
        }
        QKeyWidget {
            id: img_space_icon
            objectName: "img_space_icon"
            x: 200
            y: 422
            keySize: sizeKeySpace
            keyText: " "
        }
        QKeyWidget {
            id: img_keyboard_period_key
            objectName: "img_keyboard_period_key"
            x: 520
            y: 422
            keySize: sizeKeyNormal
            keyText: "."
        }
        QKeyWidget {
            id: img_keyboard_minimize_key
            objectName: "img_keyboard_minimize_key"
            x: 600
            y: 422
            keySize: sizeKeyNormal
            keyFunction: functionCtrl
            keyImage: "qrc:/resources/Image/hidekeyboard.png"
            onKeyCtrlClicked: {
                UIBridge.keyboardEvent(1, "hide")
            }
        }
        QKeyWidget {
            id: ui_save
            objectName: "ui_save"
            x: 680
            y: 422
            keySize: sizeKeyCtrl
            keyFunction: functionCtrl
            keyText: "Save"
            keyColor: "green"
            onKeyCtrlClicked: {
                UIBridge.keyboardEvent(1, "done")
            }
        }
    }
}
