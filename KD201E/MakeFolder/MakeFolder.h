#ifndef PUTFTP_H
#define PUTFTP_H

#include <QThread>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkSession>
#include <QNetworkConfiguration>
#include <QDir>
#include <QTextStream>
#include <QTimer>
#include <thread>

#define DLOG(msg, args...)  qDebug("[%s][Thread-%d][%s] " msg, QDateTime::currentDateTime().toString("HH:mm:ss:zzz").toStdString().c_str(), std::this_thread::get_id(), __PRETTY_FUNCTION__, ##args)

#define FILE_DIR    "d://KD201E/temp/"

class MakeFolder : public QObject
{
    Q_OBJECT
public:
    explicit MakeFolder(QObject *parent = nullptr);

private:
    QFile *m_fileFtp = nullptr;
    QStringList m_listFile;

    void scanListFile(QString folder = FILE_DIR);
    void makeFolderTree(QStringList &list);
};

#endif // PUTFTP_H
