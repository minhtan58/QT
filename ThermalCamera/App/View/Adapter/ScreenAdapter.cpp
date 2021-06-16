#include "ScreenAdapter.h"
#include "Delivery.h"
#include "HMIEvents.h"

ScreenAdapter::ScreenAdapter(QObject *appContainer, QObject *parent)
    : QObject(parent)
    , m_appContainer(appContainer)
    , m_screenId(-1)
{
    DLOG("Create");
    connect(Delivery::getInstance(), SIGNAL(dataTransfer(int,void*)), this, SLOT(updateData(int,void*)));
}

ScreenAdapter::~ScreenAdapter()
{}

void ScreenAdapter::createScreen(int screenId)
{
    m_screenId = screenId;
    DLOG("load screen starting");
    m_appContainer->setProperty("source", screenList.value(m_screenId));
    m_screenView = qvariant_cast<QObject*>(m_appContainer->property("item"));
    initAppData();
    DLOG("load screen %d finished", m_screenId);
}

int ScreenAdapter::currentScreenId()
{
    return m_screenId;
}

void ScreenAdapter::initAppData()
{
    switch (m_screenId) {
    case SCR_THERMAL_NORMAL: {
        break;
    }
    default:
        break;
    }
}

void ScreenAdapter::updateAppData(int dpid, QString value)
{
    switch (dpid) {
    case 1: {
        break;
    }
    default:
        break;
    }
}

void ScreenAdapter::updateData(int eventId, void *data)
{
    switch (eventId) {
    case DATA_THERMAL_IMAGE: {
        QImage *frame = static_cast<QImage*>(data);
        SETPROPERTY("thermal_image", "image", *frame);
        break;
    }
    case DATA_THERMAL_TEMPERATURE: {
        float *temperature = static_cast<float*>(data);
        SETPROPERTY("thermal_temperature", "maxTemp", *temperature);
        break;
    }
    case DATA_NORMAL_IMAGE: {
        QImage *frame = static_cast<QImage*>(data);
        SETPROPERTY("normal_image", "image", *frame);
        break;
    }
    default:
        break;
    }
}
