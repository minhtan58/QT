/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: cemsconstants
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef CEMSCONSTANTS_H
#define CEMSCONSTANTS_H

#define DEFAULT_SERVER_IP               QString("113.160.203.19")
//#define SERVER_IP   QString("127.0.0.1")
#define DEFAULT_SERVER_PORT             11111
#define DEFAULT_SERVER_READ_INTERVAL    10000
#define DEFAULT_SEND_TO_SERVER_INTERVAL 300000

#define UPDATE_DATA_INTERVAL            10000
#define TIM_UPDATE_STATUS               5000

#define DELAY_REQ_MS                    100
#define DELAY_RE_REQ_MS                 100

#define HS_O2       0.631
#define HS_TEMP     9.340
#define HS_OPP      6.278
#define HS_DUST_PM  154.523
#define HS_VEL      6.373

#define HS_AMP_2_PPM_CO     142.857
#define HS_AMP_2_PPM_NO     81.235
#define HS_AMP_2_PPM_NOX
#define HS_AMP_2_PPM_SO2    49.804

#define HS_PPM_2_STD_CO     1.14
#define HS_PPM_2_STD_NO     1.23
#define HS_PPM_2_STD_NO2    1.88
#define HS_PPM_2_STD_NOX    1.88
//#define HS_PPM_2_STD_SO2    2.62
#define HS_PPM_2_STD_SO2    2.62 * 0.5

#define AMP_MIN               2.5

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480
#define TOPBAR_HEIGHT   70
#define APP_HEIGHT      410

#ifdef __WIN32
#define CEMS_SETTINGS_FOLDERPATH    "D://CEMS/"
#define CEMS_SETTINGS_FILENAME      "D://CEMS/cems.ini"
#define PH_DB                       "D://CEMS/dbCems.db"
#define PH_EXPORT_FOLDER            "D://CEMS/ExportData"
#elif __linux__
#define CEMS_SETTINGS_FOLDERPATH    "/user/CEMS/"
#define CEMS_SETTINGS_FILENAME      "/user/CEMS/cems.ini"
#define PH_DB                       "/user/CEMS/dbCems.db"
#define PH_EXPORT_FOLDER            "/user/CEMS/ExportData"
#endif

#define STR_NO_PARAMS   QString("")

#endif // CEMSCONSTANTS_H
