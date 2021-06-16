/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: UIBridge.h
    Create: 14/12/2017
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef UIBRIDGE_H
#define UIBRIDGE_H

#include "common.h"

/* delay event struct */
typedef struct {
    QString objectName;
    int eventId;
    QString param;
} EventElement;

class UIBridge : public QObject
{
    Q_OBJECT
public:
    explicit UIBridge(QObject *parent = nullptr);
    static UIBridge* getInstance();
    ~UIBridge();
    Q_INVOKABLE void log(QString msg);

    void sendEvent(QString objectName, int eventId, QString param);
    void setDelayEvent(QString objectName, int eventId, QString param);
    void resetDelayEvent();
    void emitDelayEvent();

signals:
    void hmiEvent(QString objectName, int eventId, QString param);
    void keyboardEvent(int keyType, QString keyValue);

    //----------QML List Signal------------//
    void loginHistoryListFetchFinished();

private:
    static UIBridge *m_uiBridge;
    EventElement *m_delayEvent = nullptr;
};

#endif // UIBRIDGE_H
