#ifndef MODELHANDLER_H
#define MODELHANDLER_H

#include <QObject>
#include "common.h"
#include "KD201E.h"
#include "SettingsLoader.h"

class ModelHandler : public QObject
{
    Q_OBJECT
public:
    explicit ModelHandler(QObject *parent = nullptr);
    void start();

public slots:
    void updateData(int dpid, QString data);

private:
    KD201E *m_kd201e = nullptr;
    void configure();
    static void loadIniSettings();
};

#endif // MODELHANDLER_H
