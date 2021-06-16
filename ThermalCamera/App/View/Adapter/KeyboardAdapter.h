/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: KeyboardAdapter.h
    Create: 05/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef KEYBOARDADAPTER_H
#define KEYBOARDADAPTER_H

#include "Common.h"

#include <QObject>
#include <QQuickItem>

class KeyboardAdapter : public QObject
{
    Q_OBJECT
public:
    enum KeyBoardMode{
        KB_MODE_NUMBER_ONLY,
        KB_MODE_FULLKEY
    };

    enum KeyboardState {
        KB_STATE_SMALL,
        KB_STATE_CAP,
        KB_STATE_NUMBER,
        KB_STATE_SPECIAL
    };

    explicit KeyboardAdapter(QQuickItem *container, QObject *parent = nullptr);
    void showKeyboard(int mode = KB_MODE_NUMBER_ONLY);
    void hideKeyboard();
    void setCurrentTextInput(QObject *textInput);
    bool isKeyboardShow();
    bool isKeyboardNumberOnly();

public slots:
    void keyboardKeyHandle(int keyType, QString keyValue);

private:
    QObject *m_keyboardView = nullptr;
    QQuickItem *m_keyboardContainer = nullptr;
    QObject *m_currentTextInput = nullptr;

    bool m_tempIsShiftHold = false;
    void createKeyboard(int mode);
};

#endif // KEYBOARDADAPTER_H
