#include <QCoreApplication>
#include "MakeFolder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MakeFolder ftp;

    return a.exec();
}
