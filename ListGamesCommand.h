#ifndef SERVER_LISTGAMESCOMMAND_H
#define SERVER_LISTGAMESCOMMAND_H

#include "Command.h"
#include "GamesList.h"
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

class ListGamesCommand : public Command {
public:
    virtual void execute(vector<string> args);
};

#endif //SERVER_LISTGAMESCOMMAND_H