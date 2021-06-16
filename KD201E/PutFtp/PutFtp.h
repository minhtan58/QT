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

#include <Poco/Net/FTPClientSession.h>

using Poco::Exception;
using Poco::Net::SocketStream;
using Poco::Net::FTPClientSession;

using std::string;
using std::exception;

#define DLOG(msg, args...)  qDebug("[%s][Thread-%d][%s] " msg, QDateTime::currentDateTime().toString("HH:mm:ss:zzz").toStdString().c_str(), std::this_thread::get_id(), __PRETTY_FUNCTION__, ##args)
#define MCR_DEL_PTR(ptr)    if(!ptr) { \
                                delete ptr; \
                                ptr = NULL; \
                            }

#define FTP_IP      "103.56.156.55"
#define FTP_PORT    21
#define FTP_USER    "data@bestflashes.com"
#define FTP_PSWD    "i31tHo4W"
#define FILE_DIR    "/usr/KD201E/temp/"

class PutFtp : public QObject
{
    Q_OBJECT
public:
    explicit PutFtp(QObject *parent = nullptr);

signals:
    void putNewFile();

public slots:
    void putFtpNewFile();
    void ftpSessionError(QNetworkReply::NetworkError error);
    void ftpSessionPutFinished(QNetworkReply *reply);
    void ftpSessionUploadProgress(qint64 done, qint64 total);
    void ftpSessionUploadFinished();

private:
    QNetworkAccessManager *m_putFtpManager = nullptr;
    QNetworkReply *m_reply = nullptr;
    QFile *m_fileFtp = nullptr;
    QStringList m_listFile;

    void scanListFile(QString folder = FILE_DIR);
    bool removeFile(QFile *file);
    bool putFtp(QString fileName);
    bool mkdirFtpPoco(QString fileName);
};

#endif // PUTFTP_H
