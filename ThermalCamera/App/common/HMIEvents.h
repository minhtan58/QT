/****************************************************************************

    Copyright (C) 2018 by KingKong JSC
    File: Defines
    Create: 04/01/2018
    Author: Vuong Nguyen

 ****************************************************************************/

#ifndef HMIEVENTS_H
#define HMIEVENTS_H

enum EventsID {
    DATA_THERMAL_IMAGE,
    DATA_THERMAL_TEMPERATURE,
    DATA_NORMAL_IMAGE,
    REQUEST_SEND_FDALARM,
    NOTIFY_THERMAL_IS_RUNNING,
    REQUEST_RESET_THERMAL_SPI,
};

#endif // HMIEVENTS_H
