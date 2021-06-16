/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: Constants.h
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DEFAULT_SERVER_IP               QString("113.160.203.19")
//#define SERVER_IP   QString("127.0.0.1")
#define DEFAULT_SERVER_PORT             11111
#define DEFAULT_SERVER_READ_INTERVAL    10000
#define DEFAULT_SEND_TO_SERVER_INTERVAL 10000

//sim
#define DEFAULT_SIM_SERVER_IP           "118.70.182.185"
#define DEFAULT_SIM_SERVER_PORT         9096

#define UPDATE_DATA_INTERVAL            10000
#define TIM_UPDATE_STATUS               5000

#define DELAY_REQ_MS                    50

#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   800
#define TOPBAR_HEIGHT   70
#define APP_HEIGHT      660

#ifdef __WIN32
#define PH_INI_FOLDER           "C://KTTVAuto/"
#define PH_INI_FILENAME         "C://KTTVAuto/kttv.ini"
#define PH_DB                   "C://KTTVAuto/kttv.db"
#elif __linux__
#define PH_INI_FOLDER           "/usr/KTTVAuto/"
#define PH_INI_FILENAME         "/usr/KTTVAuto/kttv.ini"
#define PH_DB                   "/usr/KTTVAuto/AppData/kttv.db"
#endif

#define CST_ROOT_USER               "root"
#define CST_ROOT_PASSWORD           "kttvauto"
#define CST_ROOT_ID                 "ducvuongcity"

#endif // CONSTANTS_H
