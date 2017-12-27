#ifndef SERVER_LISTGAMESCOMMAND_H
#define SERVER_LISTGAMESCOMMAND_H

#include "Command.h"

class ListGamesCommand : public Command {
public:
    virtual void execute(vector<string> args);
};

#endif //SERVER_LISTGAMESCOMMAND_H