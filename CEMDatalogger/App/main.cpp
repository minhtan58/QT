#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "CEMSDatalogger.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CEMSDatalogger logger;
    logger.exec();

    return app.exec();
}
