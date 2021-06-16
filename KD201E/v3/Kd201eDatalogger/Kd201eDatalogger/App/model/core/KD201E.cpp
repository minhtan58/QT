#include "KD201E.h"

KD201E::KD201E(QObject *parent)
    : QObject(parent)
{
    m_readHtmlManager = new QNetworkAccessManager(this);
    m_putFtpManager = new QNetworkAccessManager(this);
    m_timerUpdate = new QTimer(this);

    /* send request read html source data with timer */
    connect(m_timerUpdate, SIGNAL(timeout()), this, SLOT(fetchRequest()), Qt::QueuedConnection);

    /* response read finished when above request sent */
    connect(m_readHtmlManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(readHtmlSourcePage(QNetworkReply*)), Qt::QueuedConnection);

    /* fetch request in first time */
    fetchRequest();
}

KD201E::~KD201E()
{}

bool KD201E::saveDataFile(QString content, QString fileName, QString path)
{
    QString tempPath = path + fileName;
    if(path.endsWith("/")) {
        tempPath = path.append(fileName);
    } else {
        tempPath = path.append("/").append(fileName);
    }

    QFile fileWriter;
    QTextStream writeStream;
    fileWriter.setFileName(tempPath);
    if(fileWriter.open(QIODevice::WriteOnly | QIODevice::Text)) {
        writeStream.setDevice(&fileWriter);
        writeStream << content;
        fileWriter.close();
        if(fileWriter.exists()) {
            DLOG("Write successful %s", fileWriter.fileName().toStdString().data());
            return true;
        } else {
            DLOG("Error when write %s", fileWriter.fileName().toStdString().data());
            return false;
        }
    }
    DLOG("Can't Open");
    return false;
}

bool KD201E::putFtp(DataRow &row)
{
    uint16_t state = (uint16_t)GETDPDATA(KD201EEnum::DP_COMMON_SETTINGS_STATE).toInt();
    if ((state & STATE_VALID_STATION_NAME)
            && (state & STATE_VALID_STATION_TYPE)
            && (state & STATE_VALID_FTPSERVER_IP)
            && (state & STATE_VALID_FTPSERVER_PORT)
            && (state & STATE_VALID_FTPSERVER_USER)
            && (state & STATE_VALID_FTPSERVER_PASSWD)) {
        DLOG("Setting FTP valid, continue");
    } else {
        DLOG("Setting FTP invalid, terminated");
        return false;
    }

    m_currentWorkingRow = row;

    DLOG("Put row: %d %s %s %s %s %s %s",
         m_currentWorkingRow.isSent,
         m_currentWorkingRow.time.toStdString().data(),
         m_currentWorkingRow.varPH.toStdString().data(),
         m_currentWorkingRow.varOC.toStdString().data(),
         m_currentWorkingRow.varTSS.toStdString().data(),
         m_currentWorkingRow.varFLOW.toStdString().data(),
         m_currentWorkingRow.varCOD.toStdString().data());

    QString fileName = createTempFileFromRow(row);

    QString ftpLink = GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_IP);
    if (ftpLink.size() >= 8 && (!ftpLink.contains("ftp://")) && (!ftpLink.contains("ftps://"))) {             //1.1.1.1
        ftpLink = QString("ftp://%1/").arg(ftpLink);
    }

    QUrl ftpUrl;
    ftpUrl.setUrl(QString("%1%2/%3/%4/%5")
                  .arg(ftpLink)
                  .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_NAME))
                  .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_TYPE))
                  .arg(changeTimeFormat(m_currentWorkingRow.time, FORMAT_TIME_DB, "yyyy/MM/dd"))
                  .arg(fileName));
    ftpUrl.setUserName(GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_USER));
    ftpUrl.setPassword(GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PASSWD));
    ftpUrl.setPort(GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PORT).toInt());

    //DLOG("FTP URL %s", ftpUrl.url().toStdString().data());

    /* sending file to server */
    m_fileFtp = new QFile(TEMP_FOLDER + fileName);
    if (m_fileFtp->open(QIODevice::ReadOnly)) {

        /* create folder in server before put file if it not exist */
#ifdef __linux__
        if(!mkdirFtpPoco(fileName)) {
            DLOG("Can't run mkdirFtpPoco");
            removeSentFile(m_fileFtp);
            return false;
        }
#else
        DLOG("Not is linux os, can't run mkdir poco");
        removeSentFile(m_fileFtp);
        return false;
#endif
        /* put file to FTP Server */
        m_reply = m_putFtpManager->put(QNetworkRequest(ftpUrl), m_fileFtp);
        DLOG("Sending %s", fileName.toStdString().data());

        /* connect to get send result */
        connect(m_putFtpManager, SIGNAL(finished(QNetworkReply*)),           this, SLOT(ftpSessionPutFinished(QNetworkReply*)),        Qt::UniqueConnection);
        connect(m_reply,         SIGNAL(uploadProgress(qint64, qint64)),     this, SLOT(ftpSessionUploadProgress(qint64, qint64)),     Qt::UniqueConnection);
        connect(m_reply,         SIGNAL(finished()),                         this, SLOT(ftpSessionUploadFinished()),                   Qt::UniqueConnection);
        connect(m_reply,         SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(ftpSessionError(QNetworkReply::NetworkError)), Qt::UniqueConnection);
        m_reply->waitForBytesWritten(500);
        return true;
    }
    DLOG("Could not open file send to FTP");
    return false;
}

QString KD201E::createTempFileFromRow(DataRow &row)
{
    /* create temp file from row */
    if (!QDir().exists(TEMP_FOLDER))
        if(!QDir().mkpath(QFileInfo(TEMP_FOLDER).absolutePath()))
            return "";

    QString currTime = changeTimeFormat(row.time, FORMAT_TIME_DB, FORMAT_TIME_STD);
    QString fileName = QString("%1_%2_%3_%4.txt")
            .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_PROVINCE_CODE))
            .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_CODE))
            .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_CODE))
            .arg(currTime);
    QString fileContent =
            QString("pH\t%1\t\t%2\t00\r\n").arg(row.varPH).arg(currTime) +
            QString("Temp\t%1\toC\t%2\t00\r\n").arg(row.varOC).arg(currTime) +
            QString("TSS\t%1\tmg/L\t%2\t00\r\n").arg(row.varTSS).arg(currTime) +
            QString("Flow\t%1\tm3/h\t%2\t00\r\n").arg(row.varFLOW).arg(currTime) +
            QString("COD\t%1\tmg/L\t%2\t00\r\n").arg(row.varCOD).arg(currTime);
    saveDataFile(fileContent, fileName, TEMP_FOLDER);
    return fileName;
}

void KD201E::resetCurrentWorkingRow()
{
    m_currentWorkingRow = {0, "", "", "", "", "", ""};
}

bool KD201E::isWorkingRowEmpty()
{
    return !(m_currentWorkingRow.time.isEmpty()
             && m_currentWorkingRow.varPH.isEmpty()
             && m_currentWorkingRow.varOC.isEmpty()
             && m_currentWorkingRow.varTSS.isEmpty()
             && m_currentWorkingRow.varFLOW.isEmpty()
             && m_currentWorkingRow.varCOD.isEmpty());
}

QString KD201E::getFullFileNameFromRow(DataRow row)
{
    QString fileName = QString("%1_%2_%3_%4.txt")
            .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_PROVINCE_CODE))
            .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_COMPANY_CODE))
            .arg(GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_CODE))
            .arg(changeTimeFormat(row.time, FORMAT_TIME_DB, FORMAT_TIME_STD));
    return TEMP_FOLDER + fileName;
}

#ifdef __linux__
bool KD201E::mkdirFtpPoco(QString fileName)
{
    uint16_t state = (uint16_t)GETDPDATA(KD201EEnum::DP_COMMON_SETTINGS_STATE).toUInt();
    if(
            (state & STATE_VALID_STATION_NAME) &&
            (state & STATE_VALID_STATION_CODE) &&
            (state & STATE_VALID_STATION_TYPE) &&
            (state & STATE_VALID_FTPSERVER_IP) &&
            (state & STATE_VALID_FTPSERVER_PORT) &&
            (state & STATE_VALID_FTPSERVER_USER) &&
            (state & STATE_VALID_FTPSERVER_PASSWD))
    {
        DLOG("");
    } else {
        DLOG("State invalid");
        return false;
    }

    QString stationName = GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_NAME);
    QString stationType = GETDPDATA(KD201EEnum::DP_SETTINGS_STATION_TYPE);

    QStringList elements = fileName.split('_');
    if(elements.size() < 3) {
        return false;
    }

    //_yyyyMMddhhmmss
    //x01234567
    QString year = elements[3].mid(0, 4);
    QString month = elements[3].mid(4, 2);
    QString day = elements[3].mid(6, 2);

    FTPClientSession *ftpClient = nullptr;

    string ftpHost = GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_IP).remove("ftp://").remove("/").toStdString();
    string ftpUser = GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_USER).toStdString();
    string ftpPsw = GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PASSWD).toStdString();
    int ftpPort = GETDPDATA(KD201EEnum::DP_SETTINGS_FTPSERVER_PORT).toInt();
    string folder = "";

    /* Create ftp session object */
    try {
        ftpClient = new FTPClientSession(ftpHost, ftpPort);
    } catch(exception ex) {
        Q_UNUSED(ex)
        DLOG("Can't create FTPClientSession");
        MCR_DEL_PTR(ftpClient);
        return false;
    }

    /* ftp login */
    try {
        if (!ftpClient->isLoggedIn()) {
            ftpClient->login(ftpUser, ftpPsw);
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
    } catch(Exception ex){Q_UNUSED(ex)}

    return true;
}
#endif

void KD201E::start(int interval)
{
    if (m_timerUpdate->isActive())
        m_timerUpdate->stop();
    m_timerUpdate->start(interval);
    DLG_THR << "Timer interval = " << m_timerUpdate->interval();
}

void KD201E::start()
{
    if(GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL).isEmpty()
            || GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL).toInt() <= 0) {
        DLOG("Interval invalid %d, KD201E stop", GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL).toInt());
        return;
    }

    if (m_timerUpdate->isActive()) {
        m_timerUpdate->stop();
    }

    m_timerUpdate->start(GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_READ_INTERVAL).toInt());
    DLG_THR << "Timer interval = " << m_timerUpdate->interval();
}

bool KD201E::contains(DataRow &row, QList<DataRow> &list)
{
    for (int idx = 0; idx < list.size(); ++idx) {
        if(row.time == list.at(idx).time)
            return true;
    }
    return false;
}

void KD201E::remove(DataRow &row, QList<DataRow> &list)
{
    for (int idx = 0; idx < list.size(); ++idx) {
        if(row.time == list.at(idx).time) {
            list.removeAt(idx);
            DLOG("Remove row at %d", idx);
        }
    }
}

void KD201E::removeSentFile(QFile *file)
{
    if(file == nullptr || !file->exists()) {
        //DLOG("File is null or not exist!");
    } else {
        if(file->isOpen()) {
            file->close();
        }
        DLOG("Remove file %s %s", file->fileName().toStdString().data(), file->remove() ? "successful" : "fail");
    }
}

bool KD201E::isRunning()
{
    return m_timerUpdate->isActive();
}

void KD201E::stop()
{
    if(m_timerUpdate->isActive())
        m_timerUpdate->stop();
}

void KD201E::fetchRequest()
{
    DLOG("Send request");
    if((uint16_t)GETDPDATA(KD201EEnum::DP_COMMON_SETTINGS_STATE).toUInt() & STATE_VALID_HTML_SOURCE)
        m_readHtmlManager->get(QNetworkRequest(QUrl(GETDPDATA(KD201EEnum::DP_SETTINGS_HTML_SOURCE))));
}

void KD201E::readHtmlSourcePage(QNetworkReply *reply)
{
    int bytesAvailable = reply->bytesAvailable();
    QString data = reply->readAll();
    DLOG("bytesAvailable: %d", bytesAvailable);
    /* reply empty, no connect to html source logger */
    if(bytesAvailable <= 0) {
        SETDPDATA(KD201EEnum::DP_COMMON_HTML_CONNETED, QString("0"));
        DLOG("Not connect station");

        /* reply, parse data save and put to FTP Server */
    } else {
        SETDPDATA(KD201EEnum::DP_COMMON_HTML_CONNETED, QString("1"));
        parseData(data);

        /* save to database - storage table */
        QString currTime = getFtpPutTime();
        DataRow row;
        row.isSent = 0;
        row.time = changeTimeFormat(currTime, FORMAT_TIME_STD, FORMAT_TIME_DB);
        row.varPH = GETDPDATA(KD201EEnum::DP_VARIABLES_PH);
        row.varOC = GETDPDATA(KD201EEnum::DP_VARIABLES_OC);
        row.varTSS = GETDPDATA(KD201EEnum::DP_VARIABLES_TSS);
        row.varCOD = GETDPDATA(KD201EEnum::DP_VARIABLES_COD);
        row.varFLOW = GETDPDATA(KD201EEnum::DP_VARIABLES_FLOW);
        DbManager::getInstance()->addHistoryDataRow(row);

        /* put to FTP Server */
        putFtp(row);
    }
}

void KD201E::ftpSessionPutFinished(QNetworkReply *reply)
{
    if(reply != nullptr) {
        DLOG("Finished with reply %s", reply->errorString().toStdString().data());
    }
}

void KD201E::ftpSessionUploadProgress(qint64 done, qint64 total)
{
    qint64 uploaded = done;
    qint64 count = total;
    int percent = 0;
    if(uploaded > 0 && count > 0) {
        percent = (uploaded*100)/count;
    }
    DLOG("Sent: %lld/%lld %d%", uploaded, count, percent);

    /* when put FTP file done, update send status for DB */
    if(percent == 100) {
        SETDPDATA(KD201EEnum::DP_COMMON_FTPSERVER_CONNETED, QString("1"));
        m_currentWorkingRow.isSent = 1;
        DbManager::getInstance()->updateHistoryDataRow(m_currentWorkingRow);

        /* when data sent from missing list */
        if(!m_missingList.isEmpty()) {
            if(contains(m_currentWorkingRow, m_missingList)) {
                remove(m_currentWorkingRow, m_missingList);
            }
        }
    } else {
        SETDPDATA(KD201EEnum::DP_COMMON_FTPSERVER_CONNETED, QString("0"));
    }
}

void KD201E::ftpSessionUploadFinished()
{
    DLOG("Upload finished");
    removeSentFile(m_fileFtp);
    if(GETDPDATA(KD201EEnum::DP_COMMON_FTPSERVER_CONNETED).toInt() == 0) {
        DLOG("Network unavaiable, stop send missing");
        return;
    } else if(!m_missingList.isEmpty()) {
        QThread::msleep(100);
        m_currentWorkingRow = m_missingList.first();
        DLOG("Send missing file");
        putFtp(m_currentWorkingRow);
    } else {
        QThread::msleep(100);
        QList<DataRow> tempList = DbManager::getInstance()->getMissingData();
        if(tempList.isEmpty()) {
            return;
        } else if(tempList.size() > 100) {
            for (int idx = 0; idx < 100; ++idx) {
                m_missingList.append(tempList.at(idx));
            }
        } else {
            m_missingList.append(tempList);
        }
    }
}

void KD201E::ftpSessionError(QNetworkReply::NetworkError error)
{
    DLOG("Put ftp error %d", error);
}

void KD201E::parseData(QString data)
{
    //    DLOG("Read data: %s", data.toStdString().data());
    QStringList list = data.split("\n", QString::SkipEmptyParts);
    QRegExp rx("(\\ |\\:|\\<|\\>|\\\")");
    QStringList subList;

    for(int i = 0; i < list.size(); i++) {
        /* Station information */
        if (list.at(i).contains("Controller:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(KD201EEnum::DP_VARIABLES_CONTROLLER, subList.at(1));
        } else if (list.at(i).contains("Serial:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(KD201EEnum::DP_VARIABLES_SERIAL, subList.at(1));
        } else if (list.at(i).contains("Software:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(KD201EEnum::DP_VARIABLES_SOFTWARE, subList.at(1));
        } else if (list.at(i).contains("Time:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            QString time = QString(subList.at(1) + "/" + subList.at(2) + "/" + subList.at(3) + " " + subList.at(4) + ":" + subList.at(5) + ":" + subList.at(6)).trimmed();
            SETDPDATA(KD201EEnum::DP_VARIABLES_TIME, time);
        }

        /* Data */
        if (list.at(i).contains("MVAL1")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(KD201EEnum::DP_VARIABLES_PH, subList.at(4));
        }
        if (list.at(i).contains("SVAL1")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(KD201EEnum::DP_VARIABLES_OC, subList.at(4));
        }
        if (list.at(i).contains("MVAL2")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(KD201EEnum::DP_VARIABLES_TSS, subList.at(4));
        }
        if (list.at(i).contains("MVAL3")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(KD201EEnum::DP_VARIABLES_FLOW, subList.at(4));
        }
        if (list.at(i).contains("MVAL4")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(KD201EEnum::DP_VARIABLES_COD, subList.at(4));
        }
    }
}

QString KD201E::getLoggerCurrentTime(QString format)
{
    return QDateTime::currentDateTime().toString(format);
}

QString KD201E::getFtpPutTime(QString format)
{
    if (GETDPDATA(KD201EEnum::DP_SETTINGS_TIME_USINGHTML).toInt() == 1) {
        //10/Jun/2017 09:54:53
        QRegExp rx("(\\:|\\/|\\ )");
        QStringList timeArr = GETDPDATA(KD201EEnum::DP_VARIABLES_TIME).split(rx);
        if(timeArr.size() > 5) {
            QString year = timeArr.at(2);
            QString month = mapMonth.value(timeArr.at(1).toLower());
            QString day = timeArr.at(0);
            QString hour = timeArr.at(3);
            QString minute = timeArr.at(4);
            QString second = timeArr.at(5);
            QString currTime = QString("%1%2%3%4%5%6").arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second);
            if(format == FORMAT_TIME_STD) {
                return currTime;
            }
            return QDateTime::fromString(currTime, FORMAT_TIME_STD).toString(format);
        }
    }
    return QDateTime::currentDateTime().toString(format);
}

QString KD201E::changeTimeFormat(QString timeValue, QString from, QString to)
{
    return QDateTime::fromString(timeValue, from).toString(to);
}
