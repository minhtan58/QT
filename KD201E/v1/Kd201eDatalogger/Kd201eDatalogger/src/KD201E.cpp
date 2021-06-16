#include "KD201E.h"

KD201E::KD201E(QObject *parent)
    :QObject(parent)
{
    m_readHtmlManager = new QNetworkAccessManager(this);
    m_putFtpManager = new QNetworkAccessManager(this);
    m_timerUpdate = new QTimer(this);
    m_ftpUrl = new QUrl();
    m_fileWrite = new QFile(this);
    m_writeStream = new QTextStream();
    m_dir = new QDir();
    m_timerScanUnsendFile = new QTimer(this);
    m_timerScanStorageFile = new QTimer(this);

    connect(m_timerUpdate, SIGNAL(timeout()), this, SLOT(slt_fetch()));
    connect(m_timerScanUnsendFile, SIGNAL(timeout()), this, SLOT(slt_updateUnsendListFile()));
    connect(m_timerScanStorageFile, SIGNAL(timeout()), this, SLOT(slt_updateStorageListFile()));
    connect(m_readHtmlManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slt_readPage(QNetworkReply*)));

    m_timerScanUnsendFile->start(TIME_LOAD_UNSEND);
    m_timerScanStorageFile->start(TIME_LOAD_STORAGE);
    slt_fetch();
}

QString KD201E::getDataString()
{
    QString time;
    if (GETDPDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML).toInt() == 0) {
        time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    } else {
        QString year, month, day, hour, minute, second;
        QString tempValue = GETDPDATA(Kd201eEnum::DP_VARIABLES_TIME);
        try {
            second = tempValue.mid(18, 2);
            minute = tempValue.mid(15, 2);
            hour = tempValue.mid(12, 2);
            year = tempValue.mid(7, 4);
            month = mapMonth.value(tempValue.mid(3, 3).toLower());
            day = tempValue.mid(0, 2);
            time = QString("%1%2%3%4%5%6").arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second);
        } catch(exception ex) {
            time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
        }
    }

    return  //IDS01.pH
            QString("pH\t%1\t\t%2\t00\r\n")
            .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_PH))
            .arg(time) +

            //oC
            QString("Temp\t%1\toC\t%2\t00\r\n")
            .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_OC))
            .arg(time) +

            //IDS02.TSS
            QString("TSS\t%1\tmg/L\t%2\t00\r\n")
            .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_TSS))
            .arg(time) +

            //IDS03.Flow
            QString("Flow\t%1\tm3/h\t%2\t00\r\n")
            .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_FLOW))
            .arg(time) +

            //IDS04.CODto
            QString("COD\t%1\tmg/L\t%2\t00\r\n")
            .arg(GETDPDATA(Kd201eEnum::DP_VARIABLES_COD))
            .arg(time);
}

bool KD201E::saveDataFile(QString data, QString fileName, QString path)
{
    QString tempPath = path + fileName;
    m_fileWrite->setFileName(tempPath);
    if(m_fileWrite->open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_writeStream->setDevice(m_fileWrite);
        *m_writeStream << data;
        m_fileWrite->close();
        DLOG("Write Successful to %s", m_fileWrite->fileName().toStdString().data());
        return true;
    }
    DLOG("Can't Open");
    return false;
}

void KD201E::saveDataFileStandardFormat(QString data)
{
    if (!QDir().exists(TEMP_FOLDER))
        if(!QDir().mkpath(QFileInfo(TEMP_FOLDER).absolutePath()))
            return;     //can't mkdir

    QString fileName = createFileNameWithStandardFormat();
    saveDataFile(data, fileName, TEMP_FOLDER);
    SETDPDATA(Kd201eEnum::DP_COMMON_CURRENT_WORKINGFILE, TEMP_FOLDER + fileName);
    putFtp(fileName);
}

bool KD201E::saveToStorageFolder(QString fileName)
{
    QString stationName, stationType, year, month, day;
    stationName = GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME);
    stationType = GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE);

    QStringList elements = fileName.split('_');
    if(elements.size() < 3)
        return false;

    //_yyyyMMddhhmmss
    //x01234567
    year = elements[3].mid(0, 4);
    month = elements[3].mid(4, 2);
    day = elements[3].mid(6, 2);

    QString storageFolder = QString("%1VIETHUNG/%2/%3/%4/%5/").arg(STORAGE_FOLDER, stationType, year, month, day);
    if(!QDir().exists(storageFolder)) {
        if(!QDir().mkpath(QFileInfo(storageFolder).absolutePath())) {
            DLOG("can't create storage folder %s", storageFolder.toStdString().data());
            return false;
        }
    }

    if (m_fileFtp->isOpen()) {
        m_fileFtp->close();
    }

    QFile tmpFile(fileName);

    if (tmpFile.exists())
        if(tmpFile.rename(fileName.replace(TEMP_FOLDER, storageFolder)))
            DLOG("Moved %s", fileName.toStdString().data());
        else
            DLOG("Can't moved %s", fileName.toStdString().data());
    else
        DLOG("Not exists %s", fileName.toStdString().data());
    return true;
}

bool KD201E::putFtp(QString fileName)
{
    uint8_t settingsState = GETDPDATA(Kd201eEnum::DP_COMMON_SETTINGS_STATE).toUInt();
    if (    !(settingsState & STATE_VALID_STATION_NAME) ||
            !(settingsState & STATE_VALID_STATION_TYPE) ||
            !(settingsState & STATE_VALID_FTP_SERVER) ||
            !(settingsState & STATE_VALID_FTP_USER)   ||
            !(settingsState & STATE_VALID_FTP_PASSWD) ) {
        DLOG("Setting FTP error");
        return false;
    }

    QString stationType, year, month, day;
    stationType = GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE).toUpper();
    QStringList elements = fileName.split('_');
    if (elements.size() < 3)
        return false;

    //_yyyyMMddhhmmss
    //x01234567
    year = elements[3].mid(0, 4);
    month = elements[3].mid(4, 2);
    day = elements[3].mid(6, 2);

    QString ftpUrl = GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP);
    if (ftpUrl.size() >= 8 && (!ftpUrl.contains("ftp://")) && (!ftpUrl.contains("ftps://"))) {             //1.1.1.1
        ftpUrl = QString("ftp://%1/").arg(ftpUrl);
    }

    m_ftpUrl->setUrl(QString("%1VIETHUNG/%2/%3/%4/%5/%6")
                     .arg(ftpUrl)
                     .arg(stationType)
                     .arg(year)
                     .arg(month)
                     .arg(day)
                     .arg(fileName));
    m_ftpUrl->setUserName(GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_USER));
    m_ftpUrl->setPassword(GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW));
    m_ftpUrl->setPort(FTP_PORT);

    DLOG("FTP URL: %s", m_ftpUrl->url().toStdString().data());

    m_fileFtp = new QFile(TEMP_FOLDER + fileName);
    if (m_fileFtp->open(QIODevice::ReadOnly)) {
        DLOG("Open %s", m_fileFtp->fileName().toStdString().data());

#ifdef __linux__
        if(!mkdirFtpPoco(fileName)) {
            DLG_THR << "Can't run mkdirFtpPoco";
            return false;
        }
#else
        DLOG("Can't run mkdir poco");
#endif

        try {
            m_reply = m_putFtpManager->put(QNetworkRequest(*m_ftpUrl), m_fileFtp);

            DLOG("Sending... %s", fileName.toStdString().data());

            //CONNECT
            QObject::connect(m_putFtpManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(slt_ftpRequestFinished(QNetworkReply*)), Qt::UniqueConnection);
            QObject::connect(m_reply, SIGNAL(uploadProgress(qint64, qint64)), SLOT(slt_ftpUploadProgress(qint64, qint64)), Qt::UniqueConnection);
            QObject::connect(m_reply, SIGNAL(finished()), SLOT(slt_ftpUploadDone()), Qt::UniqueConnection);
            QObject::connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slt_ftpPutError(QNetworkReply::NetworkError)), Qt::UniqueConnection);

            m_reply->waitForBytesWritten(10);

            return true;
        }
        catch(exception ex) {
            if (m_fileFtp->isOpen()) {
                m_fileFtp->close();
            }
            return false;
        }
    }

    DLOG("Could not open file send to FTP");
    return false;
}

#ifdef __linux__
bool KD201E::mkdirFtpPoco(QString fileName)
{
    uint8_t state = (uint8_t)GETDPDATA(Kd201eEnum::DP_COMMON_SETTINGS_STATE).toUInt();
    if( !(state & STATE_VALID_STATION_NAME) ||
        !(state & STATE_VALID_COMPANY_NAME) ||
        !(state & STATE_VALID_STATION_TYPE) ||
        !(state & STATE_VALID_FTP_SERVER) ||
        !(state & STATE_VALID_FTP_USER) ||
        !(state & STATE_VALID_FTP_PASSWD)){
        DLOG("State invalid");
        return false;
    }

    QString stationName, stationType, year, month, day;
    stationName = "VIETHUNG";
    stationType = GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONTYPE);

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

    string ftpHost = GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_SERVERIP).remove("ftp://").remove("/").toStdString();
    string ftpUser = GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_USER).toStdString();
    string ftpPsw = GETDPDATA(Kd201eEnum::DP_SETTINGS_FTP_PSW).toStdString();

    try {
        ftpClient = new FTPClientSession(ftpHost, FTP_PORT);
    } catch(exception ex) {
        DLOG("Can't create FTPClientSession");
        if(ftpClient != nullptr) {
            delete ftpClient;
            ftpClient = nullptr;
        }
        return false;
    }

    try {
        if (!ftpClient->isLoggedIn()) {
            ftpClient->login(ftpUser, ftpPsw);
            DLOG("FTP Login successful");
        }
    } catch (exception ex) {
        DLOG("FTP can't login");
        if(ftpClient != nullptr) {
            delete ftpClient;
            ftpClient = nullptr;
        }
        return false;
    }

    try {
        if (!ftpClient->isLoggedIn()) {
            if(ftpClient != nullptr) {
                delete ftpClient;
                ftpClient = nullptr;
            }
            return false;
        }
        ftpClient->createDirectory(stationName.toStdString());
        DLOG("created %s", stationName.toStdString().data());
    } catch(exception ex){}

    try {
        if (!ftpClient->isLoggedIn()) {
            if(ftpClient != nullptr) {
                delete ftpClient;
                ftpClient = nullptr;
            }
            return false;
        }
        ftpClient->createDirectory(QString(stationName + SEP + stationType).toStdString());
        DLOG("created %s", QString(stationName + SEP + stationType).toStdString().data());
    } catch(exception ex){}

    try {
        if (!ftpClient->isLoggedIn()) {
            if(ftpClient != nullptr) {
                delete ftpClient;
                ftpClient = nullptr;
            }
            return false;
        }
        ftpClient->createDirectory(QString(stationName + SEP + stationType + SEP + year).toStdString());
        DLOG("created %s", QString(stationName + SEP + stationType + SEP + year).toStdString().data());
    } catch(exception ex){}

    try {
        if (!ftpClient->isLoggedIn()) {
            if(ftpClient != nullptr) {
                delete ftpClient;
                ftpClient = nullptr;
            }
            return false;
        }
        ftpClient->createDirectory(QString(stationName + SEP + stationType + SEP + year + SEP + month).toStdString());
        DLOG("created %s", QString(stationName + SEP + stationType + SEP + year + SEP + month).toStdString().data());
    } catch(exception ex){}

    try {
        if (!ftpClient->isLoggedIn()) {
            DLG_THR << "Can't login ftp";
            if(ftpClient != nullptr) {
                delete ftpClient;
                ftpClient = nullptr;
            }
            return false;
        }
        ftpClient->createDirectory(QString(stationName + SEP + stationType + SEP + year + SEP + month + SEP + day).toStdString());
        DLOG("created %s", QString(stationName + SEP + stationType + SEP + year + SEP + month + SEP + day).toStdString().data());
    } catch(exception ex){}

    try {
        if (ftpClient->isOpen())
            ftpClient->close();
        if(ftpClient != nullptr) {
            delete ftpClient;
            ftpClient = nullptr;
        }
    } catch(exception ex) {}

    return true;
}
#endif

QString KD201E::createFileNameWithStandardFormat()
{
    if (GETDPDATA(Kd201eEnum::DP_SETTINGS_IS_USING_TIMEHTML).toInt() == 0) {
        return QString("QN_%1_%2_%3.txt")
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME))
                .arg(GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME).toUpper())
                .arg(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));
    }

    if(GETDPDATA(Kd201eEnum::DP_VARIABLES_TIME).isEmpty())
        return "TimeStationError";

    //10/Jun/2017 09:54:53
    QRegExp rx("(\\:|\\/|\\ )");
    QString stationID, stationName, year, month, day, hour, minute, second;
    stationID = GETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME);
    stationName = GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME).toUpper();
    QStringList time = GETDPDATA(Kd201eEnum::DP_VARIABLES_TIME).split(rx);
    if(time.size() > 5) {
        year = time.at(2);
        month = mapMonth.value(time.at(1).toLower());
        day = time.at(0);
        hour = time.at(3);
        minute = time.at(4);
        second = time.at(5);

        return QString("QN_%1_%2_%3%4%5%6%7%8.txt")
                .arg(stationID)
                .arg(stationName)
                .arg(year)
                .arg(month)
                .arg(day)
                .arg(hour)
                .arg(minute)
                .arg(second);
    }
    else {
        return "TimeStationError";
    }
}

void KD201E::start(int interval)
{
    if (m_timerUpdate->isActive())
        m_timerUpdate->stop();
    m_timerUpdate->start(interval);
    DLOG("Start auto update with interval %d", m_timerUpdate->interval());
}

bool KD201E::isRunning()
{
    if (m_timerUpdate->isActive()) {
        return true;
    }
    return false;
}

void KD201E::stop()
{
    if(m_timerUpdate->isActive())
        m_timerUpdate->stop();
}

void KD201E::slt_readPage(QNetworkReply *reply)
{
    DLOG("bytesAvailable: %d", reply->bytesAvailable());
    if(reply->bytesAvailable() <= 0) {
        SETDPDATA(Kd201eEnum::DP_COMMON_IS_STATION_CONNETED, QString("0"));
        DLOG("Not connect station");
        return;
    }

    SETDPDATA(Kd201eEnum::DP_COMMON_IS_STATION_CONNETED, QString("1"));

    QString data = reply->readAll();
    parseData(data);
    if (WRITE_FILE) {
        saveDataFileStandardFormat(getDataString());
    }

    emit sgn_readHtmlFinish();
}

void KD201E::slt_fetch()
{
    if((uint8_t)GETDPDATA(Kd201eEnum::DP_COMMON_SETTINGS_STATE).toUInt() & STATE_VALID_STATION_LINK)
        m_readHtmlManager->get(QNetworkRequest(QUrl(GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONLINK))));
}

void KD201E::slt_ftpRequestFinished(QNetworkReply *reply)
{
    DLOG("Send Finished");
    DLOG("%s",reply->errorString().toStdString().data());
}

void KD201E::slt_ftpUploadProgress(qint64 done, qint64 total)
{
    double percent = 0;
    if(done > 0 && total > 0)
        percent = (done*100)/total;
    DLOG("Sent: %d/%d %d%", done, total, percent);
    if (percent == 100) {
        SETDPDATA(Kd201eEnum::DP_COMMON_IS_FTP_CONNETED, QString("1"));
        if (m_fileFtp->isOpen()) {
            m_fileFtp->close();
        }

        //saved to storage folder
        saveToStorageFolder(GETDPDATA(Kd201eEnum::DP_COMMON_CURRENT_WORKINGFILE));
    }
    else {
        SETDPDATA(Kd201eEnum::DP_COMMON_IS_FTP_CONNETED, QString("0"));
    }
}

void KD201E::slt_ftpUploadDone()
{
    if (m_fileFtp->isOpen()) {
        m_fileFtp->close();
    }
}

void KD201E::slt_ftpPutError(QNetworkReply::NetworkError error)
{
    DLOG("Put ftp error %d", error);
}

void KD201E::slt_updateUnsendListFile()
{
    QStringList unsendList;
    DLOG("Update unsend list file");
    QDir dir(TEMP_FOLDER);
    QStringList allFile = dir.entryList(QDir::Files);
    foreach (QString element, allFile) {
        if (element.contains(GETDPDATA(Kd201eEnum::DP_SETTINGS_STATIONNAME))
                && element.contains(GETDPDATA(Kd201eEnum::DP_SETTINGS_COMPANYNAME))
                && element.contains(".txt"))
        {
            unsendList << element;
        }
    }

    if(unsendList.size() > 0) {
        SETDPDATA(Kd201eEnum::DP_COMMON_CURRENT_WORKINGFILE, TEMP_FOLDER + unsendList.at(0));
        if(putFtp(unsendList.at(0)))
            unsendList.removeFirst();
    }

    if(unsendList.size() > 0) {
        DLOG("List File Unsend: ");
        for (int i = 0; i < unsendList.size() ; ++i) {
            DLOG("%s", unsendList.at(i).toStdString().data());
        }
    }
}

void KD201E::slt_updateStorageListFile()
{
    QStringList storageList;
    QDirIterator it(STORAGE_FOLDER, QStringList() << "*.txt", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        storageList << it.next();
    }

    qSort(storageList.begin(), storageList.end());
    DLOG("Update storage list file after sort, size %d", storageList.size());
    for (int i = 0; i < storageList.size(); ++i) {
        DLOG("%s", storageList.at(i).toStdString().data());
    }

    int removeListLenght;
    if(storageList.size() > MAX_FILE_SAVED) {
        removeListLenght = storageList.size() - MAX_FILE_SAVED;
        for (int i = 0; i < removeListLenght; ++i) {
            QString rmFile = storageList.at(i);
            if(QFile::exists(rmFile))
                if(QFile::remove(rmFile)) {
                    DLOG("Remove storage file %s", rmFile.toStdString().data());
                    storageList.removeAt(i);
                }
        }
    }
}

void KD201E::parseData(QString data)
{
    QStringList list = data.split("\n", QString::SkipEmptyParts);
    QRegExp rx("(\\ |\\:|\\<|\\>|\\\")");
    QStringList subList;

    for(int i = 0; i < list.size(); i++) {
        if (list.at(i).contains("Controller:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(Kd201eEnum::DP_VARIABLES_CONTROLLER, subList.at(1));
        }
        else if (list.at(i).contains("Serial:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(Kd201eEnum::DP_VARIABLES_SERIAL, subList.at(1));
        }
        else if (list.at(i).contains("Software:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(Kd201eEnum::DP_VARIABLES_SOFTWARE, subList.at(1));
        }
        else if (list.at(i).contains("Time:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            QString time = QString(
                        subList.at(1) + "/" +
                        subList.at(2) + "/" +
                        subList.at(3) + " " +
                        subList.at(4) + ":" +
                        subList.at(5) + ":" +
                        subList.at(6)).trimmed();
            SETDPDATA(Kd201eEnum::DP_VARIABLES_TIME, time);
        }

        //data
        if (list.at(i).contains("MVAL1")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(Kd201eEnum::DP_VARIABLES_PH, subList.at(4));
        }
        if (list.at(i).contains("SVAL1")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(Kd201eEnum::DP_VARIABLES_OC, subList.at(4));
        }
        if (list.at(i).contains("MVAL2")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(Kd201eEnum::DP_VARIABLES_TSS, subList.at(4));
        }
        if (list.at(i).contains("MVAL3")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(Kd201eEnum::DP_VARIABLES_FLOW, subList.at(4));
        }
        if (list.at(i).contains("MVAL4")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            SETDPDATA(Kd201eEnum::DP_VARIABLES_COD, subList.at(4));
        }
    }
}
