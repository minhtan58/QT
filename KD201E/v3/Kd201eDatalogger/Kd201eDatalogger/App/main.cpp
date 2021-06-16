#include <QCoreApplication>
#include "WebServer.h"
#include "ModelHandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ModelHandler handler;
    handler.start();

    WebServer webServer(&app);
    webServer.startService();

    return app.exec();
}
