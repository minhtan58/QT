#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Window.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Window logger;
    logger.start();

    return app.exec();
}
