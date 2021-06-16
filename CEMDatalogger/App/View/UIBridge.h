/****************************************************************************

    Copyright (C) 2017 by KingKong JSC
    File: UIBridge.h
    Create: 14/12/2017
    Author: Minh Tan

 ****************************************************************************/

#ifndef UIBRIDGE_H
#define UIBRIDGE_H

#include "Common.h"
#include "DataManager.h"

class UIBridge : public QObject
{
    Q_OBJECT
public:
    explicit UIBridge(QObject *parent = nullptr);
    static UIBridge* getInstance();
    ~UIBridge();
    Q_INVOKABLE QString getDPData(int dpid);
    Q_INVOKABLE void setDPData(int dpid, QVariant value);
    Q_INVOKABLE void log(QString msg);

    void sendEvent(QString objectName, int eventId, QString param);

signals:
    void hmiEvent(QString objectName, int eventId, QString param);
    void keyboardEvent(int keyType, QString keyValue);

private:
    static UIBridge *m_uiBridge;
};

#endif // UIBRIDGE_H
