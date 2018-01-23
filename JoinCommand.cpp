#include "JoinCommand.h"

void JoinCommand::execute(vector<string> args, int cSocket, pthread_t threadId) {
    int const nameNotInUse = -1, nameIsOk = 1;
    int clientSocket = cSocket;
    string gameName = args[0];
    GamesList *gamesList = GamesList::getInstance();
    map<string, GameRoom *> games = gamesList->getList();
    bool roomExist = false;
    //loop on games names.
    for (map<string, GameRoom *>::iterator it = games.begin(); it != games.end(); it++) {
        string currentName = it->first;
        //if the name exist.
        if (currentName.compare(gameName) == 0) {
            roomExist = true;
            break;
        }
    }
    //if room doesn't exist.
    if (roomExist == false) {
        int n = write(clientSocket, &nameNotInUse, sizeof(nameNotInUse));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
        }
        //close socket and finish thread.
        close(clientSocket);
        pthread_exit(NULL);
    }
    //if name is ok.
    int n = write(clientSocket, &nameIsOk, sizeof(nameIsOk));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
    }

    //add second client.
    GameRoom *gameRoom = games[gameName];
    gameRoom->addSecondClient(clientSocket, threadId);
    //remove the game from the list.
    gamesList->addRunningGame(gameRoom);
    gamesList->removeGame(gameName);
    //start the game.
    gameRoom->startGame();
    gamesList->removeRunningGameRoom(gameRoom);
    //pthread_exit(NULL);
}