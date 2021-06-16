/****************************************************************************

    Copyright (C) 2018 by LGE
    File: %{Cpp:License:FileName}
    Create: 11
    Author: Vuong Nguyen

 ****************************************************************************/

#include <QApplication>
#include "FireWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FireWindow window(&app);
    return app.exec();
}
