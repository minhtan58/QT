/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: Defines
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef DEFINES_H
#define DEFINES_H
#include <QDateTime>
#include <thread>

#define DLOG_THREAD         qDebug()    << "[" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz") \
                                        << "][" << QThread::currentThreadId() << "][" \
                                        << Q_FUNC_INFO << "]"

#define DLOG(msg, args...)  qDebug("[%s][Thread-%d][%s] " msg, QDateTime::currentDateTime().toString("HH:mm:ss:zzz").toStdString().c_str(), std::this_thread::get_id(), __PRETTY_FUNCTION__, ##args)

#define DEL_PTR(ptr)        if(!ptr) { \
                                delete ptr; \
                                ptr = NULL; \
                            }

#define SETDP(DPID, VALUE)  DataManager::getInstance()->setData(DPID, VALUE)

#define GETDP(DPID)         DataManager::getInstance()->getData(DPID)

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


#define SENDEVENT(OBJECT, EVENTID, PARAM)   UIBridge::getInstance()->sendEvent(OBJECT, EVENTID, PARAM)



#ifdef __WIN32
#define INI_CONFIG_FILE "D://VinCAM/camfd.ini"
#elif __linux__
#define INI_CONFIG_FILE "/usr/VinCAM/camfd.ini"
#endif

#endif // DEFINES_H
