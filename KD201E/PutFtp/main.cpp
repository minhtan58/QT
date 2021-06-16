#include <QCoreApplication>
#include "PutFtp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PutFtp ftp;

    return a.exec();
}
