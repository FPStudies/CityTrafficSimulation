/*
 * ConsoleWriteAction.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_CONSOLE_WRITE_ACTION_H
#define TRAFFIC_SIM_CONSOLE_WRITE_ACTION_H

#include <string>

#include "ActionInterface.h"

// TODO
class ConsoleWriteAction: public ActionInterface{
    std::string last_command_;

    void writeToConsole();

public:
    virtual void update();
};

#endif
