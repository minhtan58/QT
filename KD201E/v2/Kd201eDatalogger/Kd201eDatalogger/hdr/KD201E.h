#ifndef KD201E_H
#define KD201E_H

#include "common.h"

#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkSession>
#include <QNetworkConfiguration>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QTimer>
#include <QDateTime>

#ifdef __linux__
    #include <Poco/Net/FTPClientSession.h>
    using Poco::Net::SocketStream;
    using Poco::Net::FTPClientSession;
#endif

using std::exception;

#define DLG qDebug()
#define FTP_PORT            21
#define FTP_IP              "103.56.156.55"

#ifdef __linux__
    #define TEMP_FOLDER     "/usr/KD201E/temp/"
#elif _WIN32
    #define TEMP_FOLDER     "D://KD201E/temp/"
#else
    #define TEMP_FOLDER     ""
#endif

#define SEP                 QDir::separator()

class KD201E : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *m_readHtmlManager;
    QNetworkAccessManager *m_putFtpManager;
    QTimer *m_timerUpdate;
    QNetworkReply *m_reply;
    QUrl *m_ftpUrl;
    QFile *m_fileWrite;
    QFile *m_fileFtp;
    QDir *m_dir;
    QTextStream *m_writeStream;
    QTimer *m_timerScanFile;

public:
    KD201E();
    ~KD201E();

    QString getDataString();                                                        //get html parsed as qstring                                          //get html parsed as map
    bool saveDataFile(QString data, QString fileName, QString path);                //save html data to file in local
    void saveDataFileStandardFormat(QString data);                                  //save html data to file STANDARD FORMAT
    bool putFtp(QString fileName);                                                  //put file data to FTP Server

#ifdef __linux__
    bool mkdirFtpPoco(QString fileName);
#endif

    QString createFileNameWithStandardFormat();

    void start(int interval);
    bool isRunning();
    void stop();

    QMap<QString, QString> mapMonth = {
        {"jan", "01"},
        {"feb", "02"},
        {"mar", "03"},
        {"apr", "04"},
        {"may", "05"},
        {"jun", "06"},
        {"jul", "07"},
        {"aug", "08"},
        {"sep", "09"},
        {"oct", "10"},
        {"nov", "11"},
        {"dec", "12"}
    };

protected:
    void run();

signals:
    void sgn_readHtmlFinish();
    void sgn_settingError();

public slots:
    void slt_readPage(QNetworkReply*);                                          //read html data
    void slt_fetch();                                                           //fetch request to html server
    void slt_ftpRequestFinished(QNetworkReply*);                                //when request finished
    void slt_ftpUploadProgress(qint64, qint64);                                 //status upload
    void slt_ftpUploadDone();                                                   //when upload done
    void slt_ftpPutError(QNetworkReply::NetworkError error);
    void slt_updateUnsendListFile();
private:
    void parseData(QString data);                                               //parse html data
};

#endif // KD201E_H
