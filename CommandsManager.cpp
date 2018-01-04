#include "CommandsManager.h"

CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new ListGamesCommand();
    commandsMap["join"] = new JoinCommand();
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete (it->second);
    }
}

void CommandsManager::executeCommand(string command, vector<string> args, int clientSocket, pthread_t threadId) {
    //if command not exist.
    if (commandsMap.find(command) == commandsMap.end()) {
        return;
    }
    //command exist.
    Command *commandObj = commandsMap[command];
    commandObj->execute(args, clientSocket, threadId);
}