//
// Created by penta on 2021-02-13.
//

#ifndef SILO_GUI_SESSION_H
#define SILO_GUI_SESSION_H

#include <vector>
#include "../../lib/silo-main/src/simulator/simulator.h"

typedef class Session {
public:
    Session();
    ~Session();
    SIMU* simulator;
} Session;

typedef unsigned int SessionID;

#endif //SILO_GUI_SESSION_H
