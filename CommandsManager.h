#ifndef SERVER_COMMANDSMANAGER_H
#define SERVER_COMMANDSMANAGER_H

#include "StartCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include <map>
#include "Command.h"

class CommandsManager {
public:
    CommandsManager();

    ~CommandsManager();

    void executeCommand(string command, vector<string> args, int clientSocket, pthread_t threadId);

private:
    map<string, Command *> commandsMap;
};

#endif //SERVER_COMMANDSMANAGER_H