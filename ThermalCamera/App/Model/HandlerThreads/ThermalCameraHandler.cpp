#include "ThermalCameraHandler.h"
#include "HMIEvents.h"
#include <fcntl.h>

#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "Palettes.h"
#include "SPI.h"
#include "Lepton_I2C.h"
#include "DataManager.h"

ThermalCameraHandler::ThermalCameraHandler(QObject *parent)
    : QObject(parent)
{
    DLOG("Create");
    initThermalModule();
}

static int raw [120][160];

void ThermalCameraHandler::initThermalModule()
{
    //create the initial image
    m_thermalImage = new QImage(160, 120, QImage::Format_RGB888);

    //open spi port
    SpiOpenPort(0);

//    lepton_restart();
}

void ThermalCameraHandler::readFrame()
{
    int resets = 0;
    int segmentNumber = 0;
    for(int i = 0; i < NUMBER_OF_SEGMENTS; i++){
        for(int j=0;j<PACKETS_PER_SEGMENT;j++) {

            //read data packets from lepton over SPI
            read(spi_cs0_fd, result+sizeof(uint8_t)*PACKET_SIZE*(i*PACKETS_PER_SEGMENT+j), sizeof(uint8_t)*PACKET_SIZE);
            int packetNumber = result[((i*PACKETS_PER_SEGMENT+j)*PACKET_SIZE)+1];
            //printf("packetNumber: 0x%x\n", packetNumber);
            //if it's a drop packet, reset j to 0, set to -1 so he'll be at 0 again loop
            if(packetNumber != j) {
                j = -1;
                resets += 1;
                usleep(1000);
                continue;
                if(resets == 100) {
                    SpiClosePort(0);
                    DLOG("restarting spi...");
                    usleep(5000);
                    SpiOpenPort(0);
                }
            } else
                if(packetNumber == 20) {
                    //reads the "ttt" number
                    segmentNumber = result[(i*PACKETS_PER_SEGMENT+j)*PACKET_SIZE] >> 4;
                    //if it's not the segment expected reads again
                    //for some reason segment are shifted, 1 down in result
                    //(i+1)%4 corrects this shifting
                    if(segmentNumber != (i+1)%4){
                        j = -1;
                        //resets += 1;
                        //usleep(1000);
                    }
                }
        }
        usleep(1000/106);
    }

    frameBuffer = (uint16_t *)result;
    int row, column;
    uint16_t value;
    uint16_t minValue = 65535;
    uint16_t maxValue = 0;


    for(int i=0;i<FRAME_SIZE_UINT16;i++) {
        //skip the first 2 uint16_t's of every packet, they're 4 header bytes
        if(i % PACKET_SIZE_UINT16 < 2) {
            continue;
        }

        //flip the MSB and LSB at the last second
        int temp = result[i*2];
        result[i*2] = result[i*2+1];
        result[i*2+1] = temp;

        value = frameBuffer[i];
        if(value> maxValue) {
            maxValue = value;
        }
        if(value < minValue) {
            if(value != 0)
                minValue = value;
        }
    }

//    DLOG("Minima: %f °C", raw2Celsius(minValue));
//    DLOG("Maximo: %f °C", raw2Celsius(maxValue));
    //max temperature
    m_maxTemperature = raw2Celsius((float)maxValue);

    float diff = maxValue - minValue;
    float scale = 255/diff;
    QRgb color;

    for(int k=0; k<FRAME_SIZE_UINT16; k++) {
        if(k % PACKET_SIZE_UINT16 < 2) {
            continue;
        }

        value = (frameBuffer[k] - minValue) * scale;

        const int *colormap = colormap_ironblack;
        color = qRgb(colormap[3*value], colormap[3*value+1], colormap[3*value+2]);

        if((k/PACKET_SIZE_UINT16) % 2 == 0){//1
            column = (k % PACKET_SIZE_UINT16 - 2);
            row = (k / PACKET_SIZE_UINT16)/2;
        }
        else{//2
            column = ((k % PACKET_SIZE_UINT16 - 2))+(PACKET_SIZE_UINT16-2);
            row = (k / PACKET_SIZE_UINT16)/2;
        }
        raw[row][column] = frameBuffer[k];

        m_thermalImage->setPixel(column, row, color);

    }

    if(!DataManager::getInstance()->isBlockingTemp()) {
        SETDP(DPID::DP_THERMAL_TEMPERATURE, MCR_DPDATA_DOUBLE_STD(m_maxTemperature, 2));
        emit Delivery::getInstance()->dataTransfer(DATA_THERMAL_TEMPERATURE, &m_maxTemperature);
    } else {
        DLOG("Blocking temp");
    }
    emit Delivery::getInstance()->dataTransfer(DATA_THERMAL_IMAGE, m_thermalImage);
    emit Delivery::getInstance()->hmiEvent("" , NOTIFY_THERMAL_IS_RUNNING, "");
}
