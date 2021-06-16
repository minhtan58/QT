#ifndef PIVARIABLES_H
#define PIVARIABLES_H

#include <string>
#include <vector>

using std::string;
using std::vector;

typedef struct {
    string m_controller;
    string m_serial;
    string m_software;
    string m_time;
    string m_id01Val1;
    string m_id01Val2;
    string m_id02Val1;
    string m_id02Val2;
    string m_id03Val1;
    string m_id03Val2;
    string m_id04Val1;
    string m_id04Val2;
} Kd201eVariables;

typedef struct {
    string m_stationName;
    string m_stationID;
    string m_stationType;
    string m_stationLink;
    string m_readInterval;
    string m_ftpServerIP;
    string m_ftpUser;
    string m_ftpPwd;
    bool m_useTimeHtml;
} Kd201eSetting;

typedef struct {
    bool m_isStationConnected;
    bool m_isFtpConnected;
    uint8_t m_settingsState;
    string m_currentWorkingFile;
    vector<string> m_unSendListFile;
} Kd201eCommon;

extern Kd201eVariables kd201eVariant;
extern Kd201eSetting kd201eSetting;
extern Kd201eCommon kd201eCommon;

#endif // PIVARIABLES_H
