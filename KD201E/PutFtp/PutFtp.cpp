#include "PutFtp.h"

PutFtp::PutFtp(QObject *parent)
    : QObject(parent)
{
    m_putFtpManager = new QNetworkAccessManager(this);
    connect(this, &PutFtp::putNewFile, this, &PutFtp::putFtpNewFile);
    scanListFile();
}

void PutFtp::putFtpNewFile()
{
    if(m_listFile.size() == 0) {
        DLOG("List file empty");
    } else {
        putFtp(m_listFile.at(0));
    }
}

/* put file to FTP Server */
bool PutFtp::putFtp(QString fileName)
{
    /* create FTP put link from saved file name */
    QStringList elements = fileName.split('_');
    if (elements.size() < 3)
        return false;

    //_yyyyMMddhhmmss
    //x01234567
    QString year = elements[3].mid(0, 4);
    QString month = elements[3].mid(4, 2);
    QString day = elements[3].mid(6, 2);

    QString ftpLink = FTP_IP;
    if (ftpLink.size() >= 8 && (!ftpLink.contains("ftp://")) && (!ftpLink.contains("ftps://"))) {             //1.1.1.1
        ftpLink = QString("ftp://%1/").arg(ftpLink);
    }

    QUrl ftpUrl;
    ftpUrl.setUrl(QString("%1VIETHUNG/NuocThai/%2/%3/%4/%5")
                     .arg(ftpLink)
                     .arg(year)
                     .arg(month)
                     .arg(day)
                     .arg(fileName));
    ftpUrl.setUserName(FTP_USER);
    ftpUrl.setPassword(FTP_PSWD);
    ftpUrl.setPort(FTP_PORT);

    DLOG("FTP URL %s", ftpUrl.url().toStdString().data());

    /* sending file to server */
    m_fileFtp = new QFile(FILE_DIR + fileName);
    if (m_fileFtp->open(QIODevice::ReadOnly)) {
        /* create folder in server before put file if it not exist */
        if(!mkdirFtpPoco(fileName)) {
            DLOG("Can't run mkdirFtpPoco");
            return false;
        }
        /* put file to FTP Server */
        m_reply = m_putFtpManager->put(QNetworkRequest(ftpUrl), m_fileFtp);
        DLOG("Sending %s", fileName.toStdString().data());

        /* connect to get send result */
        connect(m_putFtpManager, SIGNAL(finished(QNetworkReply*)),           this, SLOT(ftpSessionPutFinished(QNetworkReply*)),        Qt::UniqueConnection);
        connect(m_reply,         SIGNAL(uploadProgress(qint64, qint64)),     this, SLOT(ftpSessionUploadProgress(qint64, qint64)),     Qt::UniqueConnection);
        connect(m_reply,         SIGNAL(finished()),                         this, SLOT(ftpSessionUploadFinished()),                   Qt::UniqueConnection);
        connect(m_reply,         SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(ftpSessionError(QNetworkReply::NetworkError)), Qt::UniqueConnection);
        m_reply->waitForBytesWritten(100);
        return true;
    }
    DLOG("Could not open file send to FTP");
    return false;
}

bool PutFtp::mkdirFtpPoco(QString fileName)
{
    QString stationName, stationType, year, month, day;
    stationName = "VIETHUNG";
    stationType = "NuocThai";

    QStringList elements = fileName.split('_');
    if(elements.size() < 3) {
        return false;
    }

    //_yyyyMMddhhmmss
    //x01234567
    year = elements[3].mid(0, 4);
    month = elements[3].mid(4, 2);
    day = elements[3].mid(6, 2);

    FTPClientSession *ftpClient = nullptr;

    string folder = "";

    /* Create ftp session object */
    try {
        ftpClient = new FTPClientSession(FTP_IP);
    } catch(Exception ex) {
        DLOG("Can't create FTPClientSession %s", ex.displayText().data());
        MCR_DEL_PTR(ftpClient);
        return false;
    }

    /* ftp login */
    try {
        if (!ftpClient->isLoggedIn()) {
            ftpClient->login(FTP_USER, FTP_PSWD);
            DLOG("FTP Login successful");
        }
    } catch (exception ex) {
        Q_UNUSED(ex)
        DLOG("FTP can't login");
        MCR_DEL_PTR(ftpClient);
        return false;
    }

    /* try create station folder */
    try {
        folder = stationName.toStdString();
        ftpClient->createDirectory(folder);
        DLOG("created %s", folder.data());
    } catch(exception ex){Q_UNUSED(ex)}

    /* try create folder */
    try {
        std::string folder = QString("%1/%2").arg(stationName).arg(stationType).toStdString();
        ftpClient->createDirectory(folder);
        DLOG("created %s", folder.data());
    } catch(exception ex){Q_UNUSED(ex)}

    try {
        std::string folder = QString("%1/%2/%3").arg(stationName).arg(stationType).arg(year).toStdString();
        ftpClient->createDirectory(folder);
        DLOG("created %s", folder.data());
    } catch(exception ex){Q_UNUSED(ex)}

    try {
        folder = QString("%1/%2/%3/%4").arg(stationName).arg(stationType).arg(year).arg(month).toStdString();
        ftpClient->createDirectory(folder);
        DLOG("created %s", folder.data());
    } catch(exception ex){Q_UNUSED(ex)}

    try {
        folder = QString("%1/%2/%3/%4/%5").arg(stationName).arg(stationType).arg(year).arg(month).arg(day).toStdString();
        ftpClient->createDirectory(folder);
        DLOG("created %s", folder.data());
    } catch(exception ex){Q_UNUSED(ex)}

    /* create done, close session */
    try {
        if (ftpClient->isOpen())
            ftpClient->close();
        MCR_DEL_PTR(ftpClient);
    } catch(exception ex){Q_UNUSED(ex)}

    return true;
}

void PutFtp::ftpSessionPutFinished(QNetworkReply *reply)
{
    if(reply != nullptr) {
        DLOG("put finished with err %s", reply->errorString().toStdString().data());
    }
    if(m_listFile.size() > 0)
        emit putFtpNewFile();
}

void PutFtp::ftpSessionUploadProgress(qint64 done, qint64 total)
{
    int percent = 0;
    if(done > 0 && total > 0) {
        percent = (done*100)/total;
    }
    DLOG("Sent: %d/%d %d%", done, total, percent);

    /* when put FTP file done, update send status for DB */
    if (percent == 100) {
        if (m_fileFtp->isOpen()) {
            m_fileFtp->close();
        }

        /* remove when send finished */
        removeFile(m_fileFtp);
        if(m_listFile.contains(m_fileFtp->fileName())) {
            m_listFile.removeAll(m_fileFtp->fileName());
            qDebug() << m_listFile;
        }
    }
    else {
    }
}

void PutFtp::ftpSessionUploadFinished()
{
    if (m_fileFtp->isOpen()) {
        m_fileFtp->close();
    }
}

void PutFtp::scanListFile(QString folder)
{
    DLOG("Update list file");
    QDir dir(folder);
    QStringList allFile = dir.entryList(QDir::Files);
    foreach (QString element, allFile) {
        if (element.contains("VIETHUNG") && element.contains(".txt"))
        {
            m_listFile << element;
        }
    }
    DLOG("Scan detect %d file(s)", m_listFile.size());
    qDebug() << m_listFile;
    if(m_listFile.size() > 0)
        emit putFtpNewFile();
}

bool PutFtp::removeFile(QFile *file)
{
    if(file->exists()) {
        if(file->remove()) {
            DLOG("Remove storage file %s", file->fileName().toStdString().data());
            return true;
        } else {
            DLOG("Can't remove file %s", file->fileName().toStdString().data());
        }
    } else {
        DLOG("File %s not exist", file->fileName().toStdString().data());
    }
    return false;
}

void PutFtp::ftpSessionError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error)
    DLOG("Put ftp error");
    if (m_fileFtp->isOpen()) {
        m_fileFtp->close();
    }
}
