/****************************************************************************

    Copyright (C) 2018 by LGE
    File: DbHandler.cpp
    Create: 14
    Author: Vuong Nguyen

 ****************************************************************************/

#include "DbHandler.h"

DbHandler::DbHandler(QObject *parent) : QObject(parent)
{
    DbManager::getInstance();
    m_timerSendDataToServer = new QTimer(this);
    m_process = new QProcess(this);
    int interval = GETDPDATA(CEMSEnum::DP_SETTINGS_NETWORK_SERVER_INTERVAL).toInt();
    m_timerSendDataToServer->setInterval(interval > 0 ? interval : DEFAULT_SEND_TO_SERVER_INTERVAL);
    connect(m_timerSendDataToServer, SIGNAL(timeout()), this, SLOT(checkSendServerData()), Qt::UniqueConnection);
    start();
}

void DbHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    switch (eventId) {
    case CEMSEnum::HMI_LIST_REQUEST_GET_HISTORY_DATA: {
        QList<CemsDataRow> list;
        list = DbManager::getInstance()->getHistoryData(param);
        DataManager::getInstance()->setHistoryDataList(list);
        SENDEVENT("" , CEMSEnum::DB_RESPONSE_GET_HISTORY_DATA_FINISHED, "");
        break;
    }
    case CEMSEnum::DB_REQUEST_ADD_MISSING_DATA_ROW: {
        QStringList dataRow = DataManager::getInstance()->getWorkingDataRow();
        if (dataRow.size() == 11) {
            saveToMissingDb(dataRow);
        } else {
            DLOG("Datarow to add missing data");
        }
        break;
    }
    case CEMSEnum::DB_REQUEST_REMOVE_MISSING_DATA_ROW: {
        if(!param.isEmpty()) {
            DbManager::getInstance()->removeSentMissingData(param);
        }
        break;
    }
    case CEMSEnum::HMI_BUTTON_REQ_EXPORT: {
        SENDEVENT("" , CEMSEnum::HMI_REQUEST_SHOW_COMMON_POPUP, "3000,Export successful!");
        exportDataFile();
        break;
    }
    default:
        break;
    }
}

void DbHandler::updateAppData(int dpid)
{
    switch (dpid) {
    case CEMSEnum::DP_SETTINGS_NETWORK_SERVER_INTERVAL: {
        if(m_timerSendDataToServer != nullptr && m_timerSendDataToServer->isActive()) {
            m_timerSendDataToServer->stop();
        }

        int interval = GETDPDATA(dpid).toInt();
        m_timerSendDataToServer->setInterval(interval > 0 ? interval : DEFAULT_SEND_TO_SERVER_INTERVAL);
        m_timerSendDataToServer->start();
        DLOG("NetworkMainServerHandler run with timer - %d, read value - %d", m_timerSendDataToServer->interval(), interval);
        break;
    }
    default:
        break;
    }
}

void DbHandler::checkSendServerData()
{
    updateTime();
    if (GETDPDATA(CEMSEnum::DP_SETTINGS_SERIALPORT_STATUS).toInt() != 1) {
        DLOG("Dcon not connect, no data to send serrver");
    }

    QDateTime currentTime = QDateTime::currentDateTime();

    QStringList workingRow;
    workingRow << currentTime.toString("yyyy-MM-dd HH:mm:ss")
               << GETDPDATA(CEMSEnum::DP_AIR_O2)
               << GETDPDATA(CEMSEnum::DP_AIR_CO)
               << GETDPDATA(CEMSEnum::DP_AIR_NO)
               << GETDPDATA(CEMSEnum::DP_AIR_NOX)
               << GETDPDATA(CEMSEnum::DP_AIR_SO2)
               << GETDPDATA(CEMSEnum::DP_TEMP)
               << GETDPDATA(CEMSEnum::DP_OPP)
               << GETDPDATA(CEMSEnum::DP_DUST_PM)
               << GETDPDATA(CEMSEnum::DP_VEL)
               << GETDPDATA(CEMSEnum::DP_FLOW);
    saveToHistoryDb(workingRow);
    DataManager::getInstance()->setWorkingDataRow(workingRow);
    QList<CemsDataRow> missingList = DbManager::getInstance()->getMissingData();
    if(missingList.isEmpty()) {
        DataManager::getInstance()->resetMissingDataList();
    } else if(missingList.size() > 10) {
        QList<CemsDataRow> missingSubList;
        for (int idx = 0; idx < 10; ++idx) {
            missingSubList << missingList.at(idx);
        }
        DataManager::getInstance()->setMissingDataList(missingSubList);
    } else {
        DataManager::getInstance()->setMissingDataList(missingList);
    }
    SENDEVENT("", CEMSEnum::DB_REQUEST_SENDDATA_TO_SERVER, "");
}

void DbHandler::saveToHistoryDb(QStringList dataRow)
{
    DbManager::getInstance()->addHistoryDataRow(dataRow.at(0),
                                                dataRow.at(1),
                                                dataRow.at(2),
                                                dataRow.at(3),
                                                dataRow.at(4),
                                                dataRow.at(5),
                                                dataRow.at(6),
                                                dataRow.at(7),
                                                dataRow.at(8),
                                                dataRow.at(9),
                                                dataRow.at(10));
    DbManager::getInstance()->removeOldHistoryData(HISTORY_DAY);
}

void DbHandler::saveToMissingDb(QStringList dataRow)
{
    DbManager::getInstance()->addMissingDataRow(dataRow.at(0),
                                                dataRow.at(1),
                                                dataRow.at(2),
                                                dataRow.at(3),
                                                dataRow.at(4),
                                                dataRow.at(5),
                                                dataRow.at(6),
                                                dataRow.at(7),
                                                dataRow.at(8),
                                                dataRow.at(9),
                                                dataRow.at(10));
    DbManager::getInstance()->removeOldMissingData(MISSING_STORE_DAY);
}

void DbHandler::updateTime()
{
    m_process->start("/usr/Datalogger/scripts/updatetime.sh");
    m_process->waitForFinished();
}

void DbHandler::start()
{
    DLOG("Start Send Data To Server");
    if(m_timerSendDataToServer != nullptr && !m_timerSendDataToServer->isActive()) {
        m_timerSendDataToServer->start();
        DLOG("NetworkMainServerHandler run with timer = %d", m_timerSendDataToServer->interval());
    }
}

void DbHandler::exportDataFile()
{
    if(!QDir().exists(PH_EXPORT_FOLDER)) {
        if(!QDir().mkpath(QFileInfo(PH_EXPORT_FOLDER).absolutePath())) {
            DLOG("can't create storage folder %s", PH_EXPORT_FOLDER);
            return;
        }
    }

    QString selectedTime = GETDPDATA(CEMSEnum::DP_SEARCH_TIME_HISTORY_DATA);
    QList<CemsDataRow> list = DbManager::getInstance()->getHistoryData(selectedTime);
    if(list.size() < 1) {
        DLOG("Export List empty");
        return;
    }

    QString stationId = GETDPDATA(CEMSEnum::DP_GENERAL_STATION_ID);
    QString stationName = GETDPDATA(CEMSEnum::DP_GENERAL_STATION_NAME);
    if(stationName.isEmpty()) {
        stationName = "ExportData";
    }

    QString filename, data;
    data = QString("Station ID: %1\nStation Name: %2\nDate: %3\n\n").arg(stationId).arg(stationName).arg(selectedTime);
    if(stationId.isEmpty()) {
        filename = PH_EXPORT_FOLDER + QString("/%1_%2.txt").arg(stationName).arg(selectedTime.replace('-','_'));
    } else {
        filename = PH_EXPORT_FOLDER + QString("/%1_%2_%3.txt").arg(stationId).arg(stationName).arg(selectedTime.replace('-','_'));
    }

    data += QString("%1%2%3%4%5%6%7%8%9%10%11\n")
            .arg("Time", -25)
            .arg("O2", -10)
            .arg("CO", -10)
            .arg("NO", -10)
            .arg("NOx", -10)
            .arg("SO2", -10)
            .arg("Temp", -10)
            .arg("Opp", -10)
            .arg("Dust PM", -10)
            .arg("Vel", -10)
            .arg("Flow", -10);

    for(int i = 0; i < list.size(); i++) {
        data += QString("%1%2%3%4%5%6%7%8%9%10%11\n")
                .arg(list.at(i).time, -25)
                .arg(list.at(i).valO2, -10)
                .arg(list.at(i).valCO, -10)
                .arg(list.at(i).valNO, -10)
                .arg(list.at(i).valNOX, -10)
                .arg(list.at(i).valSO2, -10)
                .arg(list.at(i).valTEMP, -10)
                .arg(list.at(i).valOPP, -10)
                .arg(list.at(i).valDUSTPM, -10)
                .arg(list.at(i).valVEL, -10)
                .arg(list.at(i).valFLOW, -10);
    }

    QFile fileWrite;
    QTextStream writeStream;
    fileWrite.setFileName(filename);
    if(fileWrite.open(QIODevice::WriteOnly | QIODevice::Text)) {
        writeStream.setDevice(&fileWrite);
        writeStream << data;
        fileWrite.close();
        DLOG("Write Successful to ", fileWrite.fileName().toStdString().data());
        return;
    }
    DLOG("Can't Open");
}
