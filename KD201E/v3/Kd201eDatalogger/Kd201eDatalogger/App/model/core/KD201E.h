#ifndef KD201E_H
#define KD201E_H

#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkSession>
#include <QNetworkConfiguration>
#include <QDir>
#include <QTextStream>
#include <QTimer>

#include "common.h"
#include "DBManager.h"
#include "Datapool.h"
#include "SettingsLoader.h"

#ifdef __linux__
    #include <Poco/Net/FTPClientSession.h>
    using Poco::Net::SocketStream;
    using Poco::Net::FTPClientSession;
    using Poco::Exception;
#endif

using std::exception;
using std::string;

#define FTP_PORT        21

#ifdef __linux__
#define TEMP_FOLDER     "/usr/KD201E/temp/"
#elif _WIN32
#define TEMP_FOLDER     "D://KD201E/temp/"
#endif

#define SEP QDir::separator()

class KD201E : public QObject
{
    Q_OBJECT

public:
    explicit KD201E(QObject *parent = nullptr);
    ~KD201E();

    void start(int interval);
    bool isRunning();
    void stop();

    const QHash<QString, QString> mapMonth = {
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

    /**
     * @brief changeTimeFormat
     * @param timeValue
     * @param from - time format of source time
     * @param to - time format will change
     * @return time after format
     */
    static QString changeTimeFormat(QString timeValue, QString from, QString to);

signals:
    /**
     * @brief event from KD201E
     * @param code event code
     * @param data
     */
    void request(int code, void *data);

public slots:
    /**
     * @brief send read request to html source logger
     */
    void fetchRequest();

    /**
     * @brief read html data from source logger after request sent
     */
    void readHtmlSourcePage(QNetworkReply* reply);

    /**
     * @brief when put FTP file finished from Network Manager
     */
    void ftpSessionPutFinished(QNetworkReply* reply);

    /**
     * @brief update upload progress when uploading file
     */
    void ftpSessionUploadProgress(qint64, qint64);

    /**
     * @brief when upload file finished from reply
     */
    void ftpSessionUploadFinished();

    /**
     * @brief occur error when upload file
     * @param error code
     */
    void ftpSessionError(QNetworkReply::NetworkError error);

    /**
     * @brief start KD201E
     */
    void start();

private:
#ifdef __linux__
    /**
     * @brief mkdirFtpPoco
     * @param fileName
     * @return
     */
    bool mkdirFtpPoco(QString fileName);

    /**
     * @brief mkdirPoco
     * @param dir
     * @return
     */
    bool mkdirPoco(QString dir);
#endif

    /**
     * @brief parse html data and save to datapool
     * @param data is html string
     */
    void parseData(QString data);

    /**
     * @brief get current time of KD201E
     * @param format is format of time
     * @return current timer with format
     */
    QString getLoggerCurrentTime(QString format = FORMAT_TIME_STD);

    /**
     * @brief get time using for put file to FPT Server
     * @param format of time
     * @return current timer with format for put file
     */
    QString getFtpPutTime(QString format = FORMAT_TIME_STD);

    /**
     * @brief saveDataFile
     * @param data
     * @param fileName
     * @param path
     * @return
     */
    bool saveDataFile(QString content, QString fileName, QString path);

    /**
     * @brief putFtp
     * @param row
     * @return
     */
    bool putFtp(DataRow &row);

    /**
     * @brief createTempFileFromRow
     * @param row
     * @return
     */
    QString createTempFileFromRow(DataRow &row);

    /**
     * @brief resetCurrentWorkingRow
     */
    void resetCurrentWorkingRow();

    /**
     * @brief isWorkingRowEmpty
     * @return
     */
    bool isWorkingRowEmpty();

    /**
     * @brief getFullFileNameFromRow
     * @param row
     * @return
     */
    QString getFullFileNameFromRow(DataRow row);

    /**
     * @brief removeSentFile
     * @param file
     */
    void removeSentFile(QFile *file);

    /**
     * @brief contains
     * @param row
     * @param list
     * @return
     */
    bool contains(DataRow &row, QList<DataRow> &list);

    /**
     * @brief remove
     * @param row
     * @param list
     */
    void remove(DataRow &row, QList<DataRow> &list);

private:
    QNetworkAccessManager *m_readHtmlManager = nullptr;
    QNetworkAccessManager *m_putFtpManager = nullptr;
    QTimer *m_timerUpdate = nullptr;
    QNetworkReply *m_reply = nullptr;
    QFile *m_fileFtp = nullptr;
    DataRow m_currentWorkingRow;
    QList<DataRow> m_missingList;
};

#endif // KD201E_H
