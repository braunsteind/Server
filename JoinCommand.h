#ifndef SERVER_JOINCOMMAND_H
#define SERVER_JOINCOMMAND_H

#include "Command.h"
#include <cstdlib>
#include "GameRoom.h"
#include "GamesList.h"

class JoinCommand : public Command {
public:
    virtual void execute(vector<string> args);

};

#endif //SERVER_JOINCOMMAND_H