#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "CEMSSimulator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CEMSSimulator dcon(&app);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("SIM", &dcon);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
