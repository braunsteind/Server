#include "JoinCommand.h"

void JoinCommand::execute(vector<string> args) {
    int const nameNotInUse = -1;
    int clientSocket = atoi(args[0].c_str());
    string gameName = args[1];
    GamesList *gamesList = GamesList::getInstance();
    map<string, GameRoom *> games = gamesList->getList();
    int roomExist = 0;
    //loop on games names.
    for (map<string, GameRoom *>::iterator it = games.begin(); it != games.end(); it++) {
        string currentName = it->first;
        //if the name exist.
        if (currentName.compare(gameName) == 0) {
            roomExist = 1;
            break;
        }
    }
    //if room doesn't exist.
    if (roomExist == 0) {
        int n = write(clientSocket, &nameNotInUse, sizeof(nameNotInUse));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
        }
        return;
    }
    //add second client and start the game.
    GameRoom *gameRoom = games[gameName];
    gameRoom->addSecondClient(clientSocket);
    gameRoom->startGame();
}