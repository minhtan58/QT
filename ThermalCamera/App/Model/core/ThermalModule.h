/****************************************************************************

    Copyright (C) 2018 by LGE
    File: ThermalModule.h
    Create: 30
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef THERMALMODULE_H
#define THERMALMODULE_H

#include <QTimer>
#include <QThread>
#include <QImage>
#include "Defines.h"

#ifdef __linux__
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#endif

#define PACKET_SIZE 164
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define PACKETS_PER_FRAME 60
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)

class ThermalModule : public QObject
{
    Q_OBJECT
public:
    explicit ThermalModule(QObject *parent = nullptr);
    void initThermalModule();
    void start();

public slots:
    QImage *readFrame();

private:
    QImage *m_thermalImage;
    uint8_t result[PACKET_SIZE*PACKETS_PER_FRAME];
    uint16_t *frameBuffer;
};

#endif // THERMALMODULE_H
