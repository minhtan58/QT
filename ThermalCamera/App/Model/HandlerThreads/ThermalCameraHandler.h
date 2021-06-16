#ifndef THERMALCAMERAHANDLER_H
#define THERMALCAMERAHANDLER_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTimer>

#include "Delivery.h"
#include "Common.h"
#include "DataManager.h"

#include <QThread>
#include <QImage>
#include "Defines.h"

#define PACKET_SIZE 164  //Bytes
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define NUMBER_OF_SEGMENTS 4
#define PACKETS_PER_SEGMENT 60
#define PACKETS_PER_FRAME (PACKETS_PER_SEGMENT*NUMBER_OF_SEGMENTS)
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)

class ThermalCameraHandler : public QObject
{
    Q_OBJECT
public:
    explicit ThermalCameraHandler(QObject *parent = nullptr);
    void readFrame();

private:
    void initThermalModule();

private:
//    QTimer *m_updateFrame = nullptr;
    QImage *m_thermalImage = nullptr;
    float m_maxTemperature;

    uint8_t result[PACKET_SIZE*PACKETS_PER_FRAME];
    uint16_t *frameBuffer;
};

//thread define
class ThermalCameraHandlerThread : public QThread
{
    Q_OBJECT
public:
    ThermalCameraHandlerThread(QObject *parent = nullptr)
        : QThread(parent)
    {}

protected:
    void run() {
        DLOG("Start");
        ThermalCameraHandler handler;
        forever {
            handler.readFrame();
        }
        exec();
    }
};

#endif // THERMALCAMERAHANDLER_H
