#include "KD201E.h"

KD201E::KD201E()
{
    DLG_THR << "Create html read";
    m_readHtmlManager = new QNetworkAccessManager();
    m_putFtpManager = new QNetworkAccessManager();
    m_timerUpdate = new QTimer();
    m_ftpUrl = new QUrl();
    m_fileWrite = new QFile();
    m_writeStream = new QTextStream();
    m_dir = new QDir();
    m_timerScanFile = new QTimer();

    QObject::connect(m_timerUpdate, SIGNAL(timeout()), this, SLOT(slt_fetch()));
    QObject::connect(m_timerScanFile, SIGNAL(timeout()), this, SLOT(slt_updateUnsendListFile()));
    QObject::connect(m_readHtmlManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slt_readPage(QNetworkReply*)));

    m_timerScanFile->start(TIME_LOAD_UNSEND);
    slt_fetch();
}

KD201E::~KD201E()
{
    delete m_readHtmlManager;
    delete m_putFtpManager;
    delete m_timerUpdate;
    delete m_ftpUrl;
    delete m_fileWrite;
    delete m_writeStream;
    delete m_dir;
    delete m_timerScanFile;
}

QString KD201E::getDataString()
{
    QString time;
    DLG << "Time server: " << QString::fromStdString(kd201eVariant.m_time);
    if (!kd201eSetting.m_useTimeHtml)
        time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    else {
        QString year, month, day, hour, minute, second;
        QString tempValue = QString::fromStdString(kd201eVariant.m_time);
        try {
            second = tempValue.mid(18, 2);
            minute = tempValue.mid(15, 2);
            hour = tempValue.mid(12, 2);
            year = tempValue.mid(7, 4);
            month = mapMonth.value(tempValue.mid(3, 3).toLower());
            day = tempValue.mid(0, 2);
            time = QString("%1%2%3%4%5%6").arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second);
        } catch(exception ex) {time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");}
    }

    return  QString("%1_%2\t%3\n")
            .arg(QString::fromStdString(kd201eSetting.m_stationID))
            .arg(QString::fromStdString(kd201eSetting.m_stationName))
            .arg(QString::fromStdString(kd201eSetting.m_stationType)) +

            //IDS01.pH
            //VALUE1
            QString("%1\tIDS01.pH\t%2\tpH\n")
            .arg(time)
            .arg(QString::fromStdString(kd201eVariant.m_id01Val1)) +

            //VALUE2
            QString("%1\tIDS01.pH\t%2\t°C\n")
            .arg(time)
            .arg(QString::fromStdString(kd201eVariant.m_id01Val2)) +

            //IDS02.TSS
            //VALUE1
            QString("%1\tIDS02.TSS\t%2\tmg/l\n")
            .arg(time)
            .arg(QString::fromStdString(kd201eVariant.m_id02Val1)) +

            //VALUE2
            QString("%1\tIDS02.TSS\t%2\tmg/l\n")
            .arg(time)
            .arg(QString::fromStdString(kd201eVariant.m_id02Val2)) +

            //IDS03.Mau
            //VALUE1
            QString("%1\tIDS03.Mau\t%2\tPT/C\n")
            .arg(time)
            .arg(QString::fromStdString(kd201eVariant.m_id03Val1)) +

            //VALUE2
            QString("%1\tIDS03.Mau\t%2\tPT/C\n")
            .arg(time)
            .arg(QString::fromStdString(kd201eVariant.m_id03Val2)) +

            //IDS04.CODto
            //VALUE1
            QString("%1\tIDS04.CODto\t%2\tmg/l\n")
            .arg(time)
            .arg(QString::fromStdString(kd201eVariant.m_id04Val1)) +

            //VALUE2
            QString("%1\tIDS04.CODto\t%2\tmg/l\n")
            .arg(time)
            .arg(QString::fromStdString(kd201eVariant.m_id04Val2));
}

bool KD201E::saveDataFile(QString data, QString fileName, QString path)
{
    QString tempPath = path + fileName;
    m_fileWrite->setFileName(tempPath);
    if(m_fileWrite->open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_writeStream->setDevice(m_fileWrite);
        *m_writeStream << data;
        m_fileWrite->close();
        DLG << "Write Successful to " + m_fileWrite->fileName();
        return true;
    }
    DLG << "Can't Open";
    return false;
}

void KD201E::saveDataFileStandardFormat(QString data)
{
    if (!QDir().exists(TEMP_FOLDER))
        if(QDir().mkpath(QFileInfo(TEMP_FOLDER).absolutePath()))
            return;     //can't mkdir

    QString fileName = createFileNameWithStandardFormat();
    saveDataFile(data, fileName, TEMP_FOLDER);
    kd201eCommon.m_currentWorkingFile = TEMP_FOLDER + fileName.toStdString();
    putFtp(fileName);
}

bool KD201E::putFtp(QString fileName)
{
    if (    !(kd201eCommon.m_settingsState & STATE_VALID_STATION_NAME) ||
            !(kd201eCommon.m_settingsState & STATE_VALID_STATION_TYPE) ||
            !(kd201eCommon.m_settingsState & STATE_VALID_FTP_SERVER) ||
            !(kd201eCommon.m_settingsState & STATE_VALID_FTP_USER)   ||
            !(kd201eCommon.m_settingsState & STATE_VALID_FTP_PASSWD) ) {
        DLG << "Setting FTP error";
        return false;
    }

    QString stationName, stationType, year, month, day;
    stationName = QString::fromStdString(kd201eSetting.m_stationName);
    stationType = QString::fromStdString(kd201eSetting.m_stationType);
    QStringList elements = fileName.split('_');
    if (elements.size() < 3)
        return false;

    //_yyyyMMddhhmmss
    //x01234567
    year = elements[2].mid(0, 4);
    month = elements[2].mid(4, 2);
    day = elements[2].mid(6, 2);

    QString ftpUrl = QString::fromStdString(kd201eSetting.m_ftpServerIP);
    if (ftpUrl.size() >= 8 && (!ftpUrl.contains("ftp://")) && (!ftpUrl.contains("ftps://"))) {             //1.1.1.1
        ftpUrl = QString("ftp://%1/").arg(ftpUrl);
    }

    m_ftpUrl->setUrl(QString("%1%2/%3/%4/%5/%6/%7")
                     .arg(ftpUrl)
                     .arg(stationName)
                     .arg(QString::fromStdString(kd201eSetting.m_stationType))
                     .arg(year)
                     .arg(month)
                     .arg(day)
                     .arg(fileName));
    m_ftpUrl->setUserName(QString::fromStdString(kd201eSetting.m_ftpUser));
    m_ftpUrl->setPassword(QString::fromStdString(kd201eSetting.m_ftpPwd));
    m_ftpUrl->setPort(FTP_PORT);

    m_fileFtp = new QFile(TEMP_FOLDER + fileName);
    if (m_fileFtp->open(QIODevice::ReadOnly)) {

#ifdef __linux__
        if(!mkdirFtpPoco(fileName)) {
            return false;
        }
#else
        DLG << "Can't run mkdir poco";
#endif

        try {
            m_reply = m_putFtpManager->put(QNetworkRequest(*m_ftpUrl), m_fileFtp);

            DLG << "Sending... " << fileName;

            //CONNECT
            QObject::connect(m_putFtpManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(slt_ftpRequestFinished(QNetworkReply*)), Qt::UniqueConnection);
            QObject::connect(m_reply, SIGNAL(uploadProgress(qint64, qint64)), SLOT(slt_ftpUploadProgress(qint64, qint64)), Qt::UniqueConnection);
            QObject::connect(m_reply, SIGNAL(finished()), SLOT(slt_ftpUploadDone()), Qt::UniqueConnection);
            QObject::connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slt_ftpPutError(QNetworkReply::NetworkError)), Qt::UniqueConnection);

            m_reply->waitForBytesWritten(10);
            return true;
        }
        catch(exception ex) {
            return false;
        }
    }

    DLG << "Could not open file send to FTP";
    return false;
}

#ifdef __linux__
bool KD201E::mkdirFtpPoco(QString fileName)
{
    if( !(kd201eCommon.m_settingsState & STATE_VALID_STATION_NAME) ||
        !(kd201eCommon.m_settingsState & STATE_VALID_STATION_ID) ||
        !(kd201eCommon.m_settingsState & STATE_VALID_STATION_TYPE) ||
        !(kd201eCommon.m_settingsState & STATE_VALID_FTP_SERVER) ||
        !(kd201eCommon.m_settingsState & STATE_VALID_FTP_USER) ||
        !(kd201eCommon.m_settingsState & STATE_VALID_FTP_PASSWD)){
        return false;
    }

    QString stationName, stationID, stationType, year, month, day;
    stationName = QString::fromStdString(kd201eSetting.m_stationName);
    stationID = QString::fromStdString(kd201eSetting.m_stationID);
    stationType = QString::fromStdString(kd201eSetting.m_stationType);

    QStringList elements = fileName.split('_');
    if(elements.size() < 3)
        return false;

    //_yyyyMMddhhmmss
    //x01234567
    year = elements[2].mid(0, 4);
    month = elements[2].mid(4, 2);
    day = elements[2].mid(6, 2);
    DLG << QString("Path: %1/%2/%3/%4/%5").arg(stationName).arg(stationType).arg(year).arg(month).arg(day);

    FTPClientSession *ftpClient = nullptr;
    try {
        ftpClient = new FTPClientSession(kd201eSetting.m_ftpServerIP, FTP_PORT);
        DLG << QString::fromStdString(kd201eSetting.m_ftpServerIP);
    }catch(exception ex) {
        if(ftpClient != nullptr)
            delete ftpClient;
        return false;
    }

    try {
        if (!ftpClient->isLoggedIn()) {
            ftpClient->login(kd201eSetting.m_ftpUser, kd201eSetting.m_ftpPwd);
        }
    } catch (exception ex) {
        delete ftpClient;
        return false;
    }

    try {
        if (!ftpClient->isLoggedIn()) {
            delete ftpClient;
            return false;
        }
        ftpClient->createDirectory(stationName.toStdString());
        qDebug() << "created " << stationName;
    } catch(exception ex){}

    try {
        if (!ftpClient->isLoggedIn()) {
            delete ftpClient;
            return false;
        }
        ftpClient->createDirectory(QString(stationName + SEP + stationType).toStdString());
        qDebug() << "created " << QString(stationName + SEP + stationType);
    } catch(exception ex){}

    try {
        if (!ftpClient->isLoggedIn()) {
            delete ftpClient;
            return false;
        }
        ftpClient->createDirectory(QString(stationName + SEP + stationType + SEP + year).toStdString());
        qDebug() << "created " << QString(stationName + SEP + stationType + SEP + year);
    } catch(exception ex){}

    try {
        if (!ftpClient->isLoggedIn()) {
            delete ftpClient;
            return false;
        }
        ftpClient->createDirectory(QString(stationName + SEP + stationType + SEP + year + SEP + month).toStdString());
        qDebug() << "created " << QString(stationName + SEP + stationType + SEP + year + SEP + month);
    } catch(exception ex){}

    try {
        if (!ftpClient->isLoggedIn()) {
            DLG << "Can't login ftp";
            delete ftpClient;
            return false;
        }
        ftpClient->createDirectory(QString(stationName + SEP + stationType + SEP + year + SEP + month + SEP + day).toStdString());
        qDebug() << "created " << QString(stationName + SEP + stationType + SEP + year + SEP + month + SEP + day);
    } catch(exception ex){}

    try {
        if (ftpClient->isOpen())
            ftpClient->close();
        delete ftpClient;
    }catch(exception ex) {}

    DLG << "mkdir poco finish true";
    return true;
}
#endif

QString KD201E::createFileNameWithStandardFormat()
{
    if (!kd201eSetting.m_useTimeHtml) {
        return QString("%1_%2_%3.txt")
                .arg(QString::fromStdString(kd201eSetting.m_stationID))
                .arg(QString::fromStdString(kd201eSetting.m_stationName))
                .arg(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));
    }

    if(kd201eVariant.m_time == "!" || kd201eVariant.m_time == "")
        return "TimeStationError";

    //10/Jun/2017 09:54:53
    QRegExp rx("(\\:|\\/|\\ )");
    QString year, month, day, hour, minute, second;
    QStringList time = QString::fromStdString(kd201eVariant.m_time).split(rx);
    if(time.size() > 5) {
        year = time.at(2);
        month = mapMonth.value(time.at(1).toLower());
        day = time.at(0);
        hour = time.at(3);
        minute = time.at(4);
        second = time.at(5);

        return QString("%1_%2_%3%4%5%6%7%8.txt")
                .arg(QString::fromStdString(kd201eSetting.m_stationID))
                .arg(QString::fromStdString(kd201eSetting.m_stationName))
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
    if((interval < 1000) || (interval > 24*60*60*1000))
        return;

    if (m_timerUpdate->isActive())
        m_timerUpdate->stop();
    DLG << "Update with interval " << interval;
    m_timerUpdate->start(interval);
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
    if(reply->bytesAvailable() <= 0) {
        kd201eCommon.m_isStationConnected = false;
        DLG << "Not connect station";
        return;
    }

    kd201eCommon.m_isStationConnected = true;

    QString data = reply->readAll();
    parseData(data);
    if (WRITE_FILE) {
        saveDataFileStandardFormat(getDataString());
    }

    emit sgn_readHtmlFinish();
}

void KD201E::slt_fetch()
{
    if(kd201eCommon.m_settingsState & STATE_VALID_STATION_LINK)
        m_readHtmlManager->get(QNetworkRequest(QUrl(QString::fromStdString(kd201eSetting.m_stationLink))));
}

void KD201E::slt_ftpRequestFinished(QNetworkReply *reply)
{
    DLG << "Send Finished ";
    DLG << reply->errorString();
}

void KD201E::slt_ftpUploadProgress(qint64 done, qint64 total)
{
    double percent = 0;
    if(done > 0 && total > 0)
        percent = (done*100)/total;
    DLG << "Completed: " + QString::number(done) + "/" + QString::number(total) + " " + QString::number(percent) + "%";
    if (percent == 100) {
        kd201eCommon.m_isFtpConnected = true;
        if (m_fileFtp->isOpen()) {
            m_fileFtp->close();
        }
        if (QFile::exists(QString::fromStdString(kd201eCommon.m_currentWorkingFile))) {
            QFile::remove(QString::fromStdString(kd201eCommon.m_currentWorkingFile));
            DLG << "Delete complete upload file: " << QString::fromStdString(kd201eCommon.m_currentWorkingFile);
        }
    }
    else {
        kd201eCommon.m_isFtpConnected = false;
    }
}

void KD201E::slt_ftpUploadDone()
{
    qDebug() << "Done";
}

void KD201E::slt_ftpPutError(QNetworkReply::NetworkError error)
{
    DLG << "Put ftp error" << error;
}

void KD201E::slt_updateUnsendListFile()
{
    kd201eCommon.m_unSendListFile.clear();
    DLG << "Update unsend list file";
    QDir dir(TEMP_FOLDER);
    QStringList allFile = dir.entryList(QDir::Files);
    foreach (QString element, allFile) {
        if (    element.contains(QString::fromStdString(kd201eSetting.m_stationName)) &&
                element.contains(QString::fromStdString(kd201eSetting.m_stationID)) &&
                element.contains(".txt"))
        {
            kd201eCommon.m_unSendListFile.push_back(element.toStdString());
        }
    }

    if(kd201eCommon.m_unSendListFile.size() > 0) {
        kd201eCommon.m_currentWorkingFile = TEMP_FOLDER + kd201eCommon.m_unSendListFile.at(0);
        if(!putFtp(QString::fromStdString(kd201eCommon.m_unSendListFile.at(0))))
            return;
    }

    DLG << "List File Unsend: ";
    foreach (string element, kd201eCommon.m_unSendListFile) {
        DLG << QString::fromStdString(element);
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
            kd201eVariant.m_controller = subList.at(1).toStdString();
        }
        else if (list.at(i).contains("Serial:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_serial = subList.at(1).toStdString();
        }
        else if (list.at(i).contains("Software:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_software = subList.at(1).toStdString();
        }
        else if (list.at(i).contains("Time:")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_time = QString(subList.at(1) + "/" + subList.at(2) + "/" + subList.at(3) + " " + subList.at(4) + ":" + subList.at(5) + ":" + subList.at(6)).trimmed().toStdString();
        }

        //data
        if (list.at(i).contains("MVAL1")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_id01Val1 = subList.at(4).toStdString();
        }
        if (list.at(i).contains("SVAL1")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_id01Val2 = subList.at(4).toStdString();
        }
        if (list.at(i).contains("MVAL2")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_id02Val1 = subList.at(4).toStdString();
        }
        if (list.at(i).contains("SVAL2")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_id02Val2 = subList.at(4).toStdString();
        }
        if (list.at(i).contains("MVAL3")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_id03Val1 = subList.at(4).toStdString();
        }
        if (list.at(i).contains("SVAL3")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_id03Val2 = subList.at(4).toStdString();
        }
        if (list.at(i).contains("MVAL4")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_id04Val1 = subList.at(4).toStdString();
        }
        if (list.at(i).contains("SVAL4")){
            subList = list.at(i).split(rx, QString::SkipEmptyParts);
            kd201eVariant.m_id04Val2 = subList.at(4).toStdString();
        }
    }
}
