/****************************************************************************

    Copyright (C) 2018 by King Kong JSC
    File: main.cpp
    Create: 28
    Author: Vuong Nguyen

 ****************************************************************************/

#include <QGuiApplication>
#include "Window.h"
#include "WebServer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Window window;
    window.show();
    
    WebServer webServer(&app);
    webServer.startService();
    
    return app.exec();
}
