/****************************************************************************

    Copyright (C) 2018 by LGE
    File: %{Cpp:License:FileName}
    Create: 15
    Author: Vuong Nguyen

 ****************************************************************************/

#include <QCoreApplication>
#include "CEMSMonitoring.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CEMSMonitoring monitoring;
    monitoring.startListen();

    return a.exec();
}
