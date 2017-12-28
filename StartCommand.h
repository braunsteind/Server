#ifndef SERVER_STARTCOMMAND_H
#define SERVER_STARTCOMMAND_H

#include "Command.h"
#include "GamesList.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

class StartCommand : public Command {
public:
    virtual void execute(vector<string> args);
};

#endif //SERVER_STARTCOMMAND_H