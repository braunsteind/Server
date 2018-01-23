#include "StartCommand.h"

void StartCommand::execute(vector<string> args, int clientSocket, pthread_t threadId) {
    int const nameInUse = -1, nameIsOk = 1;
    int n;
    string gameName = args[0];
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
            //close socket and finish thread.
            close(clientSocket);
            pthread_exit(NULL);
        }
    }
    //
    n = write(clientSocket, &nameIsOk, sizeof(nameIsOk));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
    }

    //create new room and exit thread.
    gamesList->addGame(gameName, clientSocket);
    //pthread_exit(NULL);
}