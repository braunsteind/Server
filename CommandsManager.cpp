#include "CommandsManager.h"

CommandsManager::CommandsManager() {
    //commandsmap["print"]=new PrintCommand();
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete (it->second);
    }
}

void CommandsManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}
