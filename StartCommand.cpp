#include "StartCommand.h"

void StartCommand::execute(vector<string> args) {
    int const nameInUse = -1;
    int n;
    int clientSocket = atoi(args[0].c_str());
    cout << "starting game from socket: " << clientSocket << endl;
    string gameName = args[1];
    GamesList *gamesList = GamesList::getInstance();
    map<string, GameRoom *> games = gamesList->getList();
    //loop on games names.
    for (map<string, GameRoom *>::iterator it = games.begin(); it != games.end(); it++) {
        string currentName = it->first;
        //if the name exist.
        if (currentName.compare(gameName) == 0) {
            n = write(clientSocket, &nameInUse, sizeof(nameInUse));
            if (n == -1) {
                cout << "Error writing to socket" << endl;
            }
            return;
        }
    }
    //create new room.
    gamesList->addGame(gameName, clientSocket);
}