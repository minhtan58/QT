/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: DbHandler.cpp
    Create: 06
    Author: Vuong Nguyen

 ****************************************************************************/

#include "DbHandler.h"

DbHandler::DbHandler(QObject *parent)
    : QObject(parent)
{
    DB;
}

void DbHandler::eventHandler(QString objectName, int eventId, QString param)
{
    Q_UNUSED(objectName)
    DLOG("Request %s - %s", MODEL->eventName(eventId).toStdString().data(), param.toStdString().data());
    QStringList params = getListParam(param);
    switch (eventId) {
    case HMIEvents::HMI_REQUEST_GET_CURRENT_USER_LOGIN_INFORMATION: {
        AccountInformation acc = DB->getAccount(MODEL->userAccount());
        MODEL->userCodeSet(acc.id);
        MODEL->userAccountSet(acc.username);
        MODEL->userPasswordSet(acc.password);
        MODEL->userPermissionSet(acc.permission);
        MODEL->userFullNameSet(acc.fullName);
        MODEL->userDescriptionSet(acc.description);
        break;
    }
    case HMIEvents::HMI_REQUEST_GET_LOGIN_HISTORY: {
        MODEL->resetLoginHistory();
        DLOG("Start read login history");
        MODEL->setLoginHistoryList(DB->getLoginHistory(MODEL->historySearchDateStart(), MODEL->historySearchDateEnd()));
        DLOG("End read login history");
        DBRESPONSE(HMIEvents::DB_RESPONSE_GET_LOGIN_HISTORY_FINISHED);
        break;
    }
    case HMIEvents::HMI_REQUEST_GET_ACCOUNT_LIST: {
        MODEL->resetAccountList();
        DLOG("Start read account list");
        MODEL->setAccountList(DB->getAccountList(MODEL->userPermission()));
        DLOG("End read account list");
        DBRESPONSE(HMIEvents::DB_RESPONSE_GET_ACCOUNT_LIST_FINISHED);
        break;
    }
    case HMIEvents::HMI_REQUEST_GET_DATAVIEW_LIST: {
        MODEL->resetDataviewList();
        DLOG("Start read dataview list");
        MODEL->setDataviewList(DB->getDataviewList(MODEL->dataviewSearchDateStart(), MODEL->dataviewSearchDateEnd()));
        DLOG("End read dataview list");
        DBRESPONSE(HMIEvents::DB_RESPONSE_GET_DATAVIEW_LIST_FINISHED);
        break;
    }
    case HMIEvents::HMI_BUTTON_REQUEST_LOGIN: {
        if (params[0].isEmpty() || params[1].isEmpty()) {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Hãy nhập tài khoản và mật khẩu để đăng nhập");
            return;
        } else if(DB->isAccountExists(params[0])) {
            AccountInformation acc = DB->getAccount(params[0]);
            if(DB->getAccount(params[0]).password == params[1]) {
                MODEL->isLoginSet(true);
                MODEL->userCodeSet(acc.id);
                MODEL->userAccountSet(acc.username);
                MODEL->userPasswordSet(acc.password);
                MODEL->userPermissionSet(acc.permission);
                MODEL->userFullNameSet(acc.fullName);
                MODEL->userDescriptionSet(acc.description);
                SENDEVENT("", HMIEvents::DB_RESPONSE_LOGIN_FINISHED, "1");
                SENDEVENT("", HMIEvents::HMI_REQUEST_HIDE_POPUP, QString::number(Z_LOGIN));
                SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Đăng nhập thành công!");
                MODEL->dbUserLoginTimeSet(MODEL->dbFormatCurrentTime());
                DB->addHistoryRow(MODEL->userCode(), MODEL->dbUserLoginTime(), "");
            } else {
                MODEL->isLoginSet(false);
                DLOG("Password incorrect");
                SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Tên đăng nhập hoặc mật khẩu sai");
            }
        } else {
            MODEL->isLoginSet(false);
            DLOG("Username not exists");
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Tên đăng nhập hoặc mật khẩu sai");
        }
        break;
    }
    case HMIEvents::HMI_BUTTON_REQUEST_LOGOUT: {
        DB->updateHistoryRow(MODEL->userCode(), MODEL->dbUserLoginTime(), MODEL->dbFormatCurrentTime());
        MODEL->isLoginSet(false);
        MODEL->userCodeSet("");
        MODEL->userAccountSet("");
        MODEL->userPasswordSet("");
        MODEL->userPermissionSet(0b00000);
        MODEL->userFullNameSet("");
        MODEL->userDescriptionSet("");
        SENDEVENT("", HMIEvents::HMI_REQUEST_HIDE_POPUP, QString::number(Z_LOGIN));
        SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Đã đăng xuất");
        if (MODEL->isWorkingScreen()) {
            SENDEVENT("", HMIEvents::HMI_BUTTON_HOME, "");
        }

        break;
    }
    case HMIEvents::HMI_REQUEST_DB_SAVE_CHANGE_ACCOUNT: {
        if(DB->isAccountExists(params[1])) {
            AccountInformation accInf = DB->getAccount(params[1]);
            accInf.id = params[0];
            accInf.fullName = params[2];
            accInf.description = params[3];
            if (DB->updateExistsAccount(accInf)) {
                SENDEVENT("", HMIEvents::HMI_REQUEST_GET_ACCOUNT_LIST, "");
                SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Đã cập nhật thông tin tài khoản");
            } else {
                SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Xảy ra lỗi\n Không thể cập nhật thông tin tài khoản");
            }
        }
        break;
    }
    case HMIEvents::HMI_REQUEST_DB_DELETE_ACCOUNT: {
        if(DB->isAccountExists(params[0])) {
            if (DB->deleteAccount(params[0])) {
                SENDEVENT("", HMIEvents::HMI_REQUEST_GET_ACCOUNT_LIST, "");
                SENDEVENT("", HMIEvents::HMI_REQUEST_HIDE_POPUP, QString::number(Z_LOGIN));
                SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Đã xóa tài khoản");
            } else {
                SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Xảy ra lỗi\n Không thể xóa tài khoản");
            }
        } else {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Tài khoản " + params[0] + " chưa tồn tại");
        }
        break;
    }
    case HMIEvents::HMI_REQUEST_DB_CHANGE_PASSWORD: {
        if(params[1] == MODEL->userPassword()) {
            if(!params[2].isEmpty() && (params[2] == params[3])) {
                AccountInformation accInf = DB->getAccount(params[0]);
                accInf.password = params[2];
                if(DB->updateExistsAccount(accInf)) {
                    SENDEVENT("", HMIEvents::HMI_REQUEST_HIDE_POPUP, QString::number(Z_LOGIN));
                    SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Đã đổi mật khẩu");
                } else {
                    SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Xảy ra lỗi\nKhông thể đổi mật khẩu");
                }
            } else {
                SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Mật khẩu mới không đúng");
            }
        } else {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Mật khẩu hiện tại không đúng");
        }
        break;
    }
    case HMIEvents::HMI_REQUEST_DB_CREATE_NEW_ACCOUNT: {
        if(params[0].isEmpty() || params[1].isEmpty() || params[2].isEmpty()) {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Xin hãy nhập đầy đủ thông tin");
        } else if(DB->isAccountExists(params[1])) {
            SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Tài Khoản đã tồn tại");
        } else {
            if(DB->addAccount(params[0], params[1], params[2], DBManager::ACC_PERMISSION_EMPLOYEES, params[3], params[4])) {
                SENDEVENT("", HMIEvents::HMI_REQUEST_HIDE_POPUP, QString::number(Z_LOGIN));
                SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Đã tạo tài khoản " + params[1]);
                SENDEVENT("", HMIEvents::HMI_REQUEST_GET_ACCOUNT_LIST, "");
            } else {
                SENDEVENT("", HMIEvents::HMI_REQUEST_SHOW_COMMON_QN, "3000Xảy ra lỗi\nKhông thể thêm tài khoản " + params[1]);
            }
        }
        break;
    }
    case HMIEvents::HMI_REQUEST_DB_SAVE_KHITUONG: {
        DataviewRow row;
        row.date = MODEL->dbFormatCurrentTime();
        row.ff = MODEL->work_wind_ff();
        row.dd = MODEL->work_wind_dd();
        row.khiap = MODEL->work_thb_khiap();
        row.rain1h = MODEL->work_rain_1h();
        row.rain24h = MODEL->work_rain_24h();
        DB->addDataviewRow(row);
        break;
    }
    default:
        break;
    }
}
