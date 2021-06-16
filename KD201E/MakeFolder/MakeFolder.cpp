#include "MakeFolder.h"

MakeFolder::MakeFolder(QObject *parent)
    : QObject(parent)
{
    scanListFile();
    makeFolderTree(m_listFile);
}

void MakeFolder::scanListFile(QString folder)
{
    DLOG("Update list file");
    QDir dir(folder);
    QStringList allFile = dir.entryList(QDir::Files);
    foreach (QString element, allFile) {
        if (element.contains("VTHG_NUOVTH") && element.contains(".txt"))
        {
            m_listFile << element;
            DLOG("%s", element.toStdString().data());
        }
    }
    DLOG("Scan detect %d file(s)", m_listFile.size());
}

void MakeFolder::makeFolderTree(QStringList &list)
{
    QString fileName;
    for (int i = 0; i < m_listFile.size(); ++i) {
        fileName = FILE_DIR + m_listFile.at(i);
        m_fileFtp = new QFile(FILE_DIR + fileName);
        QString stationName, stationType, year, month, day;
        stationName = "VIETHUNG";
        stationType = "NUOCTHAI";

        QStringList elements = fileName.split('_');
        if(elements.size() < 3)
            return;

        //_yyyyMMddhhmmss
        //x01234567
        year = elements[3].mid(0, 4);
        month = elements[3].mid(4, 2);
        day = elements[3].mid(6, 2);

        QString storageFolder = QString("%1VIETHUNG/%2/%3/%4/%5/").arg(FILE_DIR, stationType, year, month, day);
        if(!QDir().exists(storageFolder)) {
            if(!QDir().mkpath(QFileInfo(storageFolder).absolutePath())) {
                DLOG("can't create storage folder %s", storageFolder.toStdString().data());
                return;
            }
        }

        if (m_fileFtp->isOpen()) {
            m_fileFtp->close();
        }

        QFile tmpFile(fileName);

        if (tmpFile.exists())
            if(tmpFile.rename(fileName.replace(FILE_DIR, storageFolder)))
                DLOG("Moved %s", fileName.toStdString().data());
            else
                DLOG("Can't moved %s", fileName.toStdString().data());
        else
            DLOG("Not exists %s", fileName.toStdString().data());
    }
}
