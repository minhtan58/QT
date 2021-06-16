#include "HMIEvents.h"
#include "DataManager.h"
#include "MonitoringHandler.h"

#include <fcntl.h>

#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "Palettes.h"
#include "SPI.h"
#include "Lepton_I2C.h"

MonitoringHandler::MonitoringHandler(QObject *parent)
    : QObject(parent)
{
    DLOG("Create");
    m_timResetSpi = new QTimer(this);
    m_timResetSpi->setInterval(3000);
    m_timResetSpi->start();
    m_timBlockTemp = new QTimer(this);
    m_timBlockTemp->setInterval(5000);
    m_timBlockTemp->setSingleShot(true);
    connect(m_timBlockTemp, SIGNAL(timeout()), this, SLOT(unBlockingTemp()));

    connect(Delivery::getInstance(), SIGNAL(hmiEvent(QString,int,QString)), this, SLOT(handleEvent(QString,int,QString)));
    connect(m_timResetSpi, SIGNAL(timeout()), this, SLOT(requestResetSpi()));
}

void MonitoringHandler::handleEvent(QString objectName, int eventId, QString params)
{
    switch (eventId) {
    case NOTIFY_THERMAL_IS_RUNNING:
        if(m_timResetSpi->isActive()) {
            m_timResetSpi->stop();
            m_timResetSpi->start();
        } else {
            m_timResetSpi->start();
        }
        break;
    default:
        break;
    }
}

void MonitoringHandler::requestResetSpi()
{
    DLOG("REQUEST_RESET_THERMAL_SPI");
    emit Delivery::getInstance()->hmiEvent("", REQUEST_RESET_THERMAL_SPI, "");

    DataManager::getInstance()->setBlockingTemp(true);
    m_timBlockTemp->start();
    lepton_restart();
}

void MonitoringHandler::unBlockingTemp()
{
    DataManager::getInstance()->setBlockingTemp(false);
}
