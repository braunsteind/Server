#ifndef SERVER_EXITCOMMAND_H
#define SERVER_EXITCOMMAND_H

#include "Command.h"

class ExitCommand : public Command {
public:
    virtual void execute(vector<string> args);
};

#endif //SERVER_EXITCOMMAND_H