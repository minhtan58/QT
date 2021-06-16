#include "ModelHandler.h"

ModelHandler::ModelHandler(QObject *parent)
    : QObject(parent)
{
    configure();
    m_kd201e = new KD201E(this);
    connect(Datapool::getInstance(), SIGNAL(dataChanged(int,QString)), this, SLOT(updateData(int,QString)), Qt::QueuedConnection);
}

void ModelHandler::start()
{
    m_kd201e->start();
}

void ModelHandler::updateData(int dpid, QString data)
{
    Q_UNUSED(data)
    switch (dpid) {
    case KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL:
        m_kd201e->start();
        break;
    default:
        break;
    }
}

void ModelHandler::configure()
{
    SettingsLoader::loadIniSettings();
}
