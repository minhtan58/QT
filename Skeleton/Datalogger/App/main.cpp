#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Datalogger.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Datalogger logger;
    logger.exec();

    return app.exec();
}
