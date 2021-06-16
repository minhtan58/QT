/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: Defines
    Create: 04/01/2018
    Author: Minh Tan

 ****************************************************************************/

#ifndef DEFINES_H
#define DEFINES_H

#define DLOG_THREAD             qDebug()    << "[" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz") \
                                            << "][" << QThread::currentThreadId() << "][" \
                                            << Q_FUNC_INFO << "]"

#define DLOG(msg, args...)  qDebug("[%s][Thread-%d][%s] " msg, QDateTime::currentDateTime().toString("HH:mm:ss:zzz").toStdString().c_str(), std::this_thread::get_id(), __PRETTY_FUNCTION__, ##args)

#define MCR_DEL_PTR(ptr)        if(!ptr) { \
                                    delete ptr; \
                                    ptr = NULL; \
                                }

#define SETDPDATA(DPID, VALUE)  DataManager::getInstance()->setData(DPID, VALUE)

#define GETDPDATA(DPID)         DataManager::getInstance()->getData(DPID)

#define MCR_DOUBLE_ROUND(NUMBER, PREC)          floor(NUMBER * pow(10., PREC) + .5) / pow(10., PREC)

#define MCR_DPDATA_DOUBLE_STD(NUMBER, PREC)     QString::number(NUMBER, 'f', PREC)

#define SETPROPERTY(OBJECT, PROPERTY, VALUE)    { \
                                                    if((!strcmp(OBJECT, ""))||(!m_screenView->objectName().compare(OBJECT))) {\
                                                        m_screenView->setProperty(PROPERTY, VALUE); \
                                                    } \
                                                    else { \
                                                        QList<QObject*> _uiObjects = m_screenView->findChildren<QObject*>(OBJECT); \
                                                        if (m_screenView->objectName() == OBJECT) \
                                                            m_screenView->setProperty(PROPERTY, VALUE); \
                                                        foreach (QObject* _uiObject, _uiObjects) {\
                                                            if (_uiObject) _uiObject->setProperty(PROPERTY, VALUE); \
                                                        } \
                                                    } \
                                                }


#define SERIAL_PORT_COM(IDX)        QString("COM%1").arg(IDX)
#define SERIAL_PORT_TTY_USB(IDX)    QString("ttyUSB%1").arg(IDX)
#define EMPTY_STR                   QString("")

#define MCR_ISSCREEN(SCREENID)  (SCREENID > SCR_START) && (SCREENID < SCR_END)

#define SENDEVENT(OBJECT, EVENTID, PARAM)   UIBridge::getInstance()->sendEvent(OBJECT, EVENTID, PARAM)

#define DECLARE_VAR(TYPE, NAME) \
    private: \
        TYPE m_##NAME;\
    public: TYPE NAME() const \
    { \
        return m_##NAME; \
    } \
    void set##NAME(const TYPE &value) \
    { \
        m_##NAME = value; \
    }

#endif // DEFINES_H
