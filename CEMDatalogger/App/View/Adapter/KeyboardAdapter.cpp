/****************************************************************************

    Copyright (C) 2018 by KingkongJSC
    File: KeyboardAdapter.cpp
    Create: 05/01/2018
    Author: Minh Tan

 ****************************************************************************/

#include "KeyboardAdapter.h"

KeyboardAdapter::KeyboardAdapter(QQuickItem *container, QObject *parent)
    : QObject(parent)
    , m_keyboardContainer(container)
{}

void KeyboardAdapter::createKeyboard(int mode)
{
    m_keyboardContainer->setProperty("source", QVariant::fromValue(screenList.value(mode == KB_MODE_NUMBER_ONLY ? PRT_KEYBOARD_NUMBER_ONLY : PRT_KEYBOARD)));
    m_keyboardView = qvariant_cast<QObject*>(m_keyboardContainer->property("item"));
}

void KeyboardAdapter::showKeyboard(int mode)
{
    createKeyboard(mode);
}

void KeyboardAdapter::hideKeyboard()
{
    m_keyboardContainer->setProperty("source", "");
}

void KeyboardAdapter::setCurrentTextInput(QObject *textInput)
{
    m_currentTextInput = textInput;
}

bool KeyboardAdapter::isKeyboardShow()
{
    return m_keyboardContainer && !m_keyboardContainer->property("source").toString().isEmpty();
}

bool KeyboardAdapter::isKeyboardNumberOnly()
{
    return !m_keyboardView->objectName().compare("keyboard_number_only");
}

void KeyboardAdapter::keyboardKeyHandle(int keyType, QString keyValue)
{
    switch (keyType) {
    case CEMS_KEYBOARD_KEY_TYPE_CHARACTER: {
        if(m_currentTextInput) {
            QString currentText = m_currentTextInput->property("text").toString();
            int cursorPosition = m_currentTextInput->property("cursorPosition").toInt();
            m_currentTextInput->setProperty("text", currentText.insert(cursorPosition, keyValue));
            m_currentTextInput->setProperty("cursorPosition", cursorPosition + 1);
        }
        int keyboardType = m_keyboardView->property("keyboardType").toInt();
        if(keyboardType == KB_STATE_CAP)
            if(!m_tempIsShiftHold)
                m_keyboardView->setProperty("keyboardType", QVariant::fromValue((int)KB_STATE_SMALL));
        break;
    }
    case CEMS_KEYBOARD_KEY_TYPE_CTRL: {
        if(keyValue == "hide")
            hideKeyboard();
        else if(keyValue == "delete_clicked") {
            int cursorPosition = m_currentTextInput->property("cursorPosition").toInt();
            if(cursorPosition > 0) {
                QString currentText = m_currentTextInput->property("text").toString();
                m_currentTextInput->setProperty("text", currentText.remove(cursorPosition - 1, 1));
                m_currentTextInput->setProperty("cursorPosition", cursorPosition - 1);
            }
        }
        else if(keyValue == "delete_hold") {
            m_currentTextInput->setProperty("text", "");
        }
        else if(keyValue == "shift_clicked") {
            int keyboardType = m_keyboardView->property("keyboardType").toInt();
            if(keyboardType == KB_STATE_CAP || keyboardType == KB_STATE_SMALL)
                if(m_tempIsShiftHold)
                    m_tempIsShiftHold = false;

            switch (keyboardType) {
            case KB_STATE_CAP:
                m_keyboardView->setProperty("keyboardType", QVariant::fromValue((int)KB_STATE_SMALL));
                break;
            case KB_STATE_SMALL:
                m_keyboardView->setProperty("keyboardType", QVariant::fromValue((int)KB_STATE_CAP));
                break;
            case KB_STATE_NUMBER:
                m_keyboardView->setProperty("keyboardType", QVariant::fromValue((int)KB_STATE_SPECIAL));
                break;
            case KB_STATE_SPECIAL:
                m_keyboardView->setProperty("keyboardType", QVariant::fromValue((int)KB_STATE_NUMBER));
                break;
            default:
                break;
            }
        }
        else if(keyValue == "shift_hold") {
            int keyboardType = m_keyboardView->property("keyboardType").toInt();
            if(keyboardType == KB_STATE_CAP || keyboardType == KB_STATE_SMALL) {
                m_keyboardView->setProperty("keyboardType", QVariant::fromValue((int)(m_tempIsShiftHold ? KB_STATE_SMALL : KB_STATE_CAP)));
                m_tempIsShiftHold = !m_tempIsShiftHold;
            }
        }
        else if(keyValue == "done") {
            if(m_currentTextInput) {
                QMetaObject::invokeMethod(m_currentTextInput, "doneInput");
                hideKeyboard();
            }
        }
        else {}
        break;
    }
    default:
        break;
    }
}
