#include <QCoreApplication>
#include "DConSimulator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DConSimulator dcon(&a);

    return a.exec();
}
