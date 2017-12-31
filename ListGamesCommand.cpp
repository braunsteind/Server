#include "ListGamesCommand.h"

void ListGamesCommand::execute(vector<string> args) {
    const int nameLength = 50;
    int n;
    int clientSocket = atoi(args[0].c_str());
    char end[nameLength];
    //get the running games.
    GamesList *gamesList = GamesList::getInstance();
    map<string, GameRoom *> games = gamesList->getList();
    //loop on games.
    for (map<string, GameRoom *>::iterator it = games.begin(); it != games.end(); it++) {
        char roomName[nameLength];
        string current = it->first;
        //copy key.
        for (int j = 0; j < current.length(); j++) {
            roomName[j] = current[j];
        }
        //add '\0' to end.
        for (int j = current.length(); j < nameLength; j++) {
            roomName[j] = '\0';
        }
        cout << "sending: " << string(roomName) << endl;
        //write game name.
        n = write(clientSocket, &roomName, sizeof(roomName));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
        }
    }
    //end of names (send empty room name).
    for (int i = 0; i < nameLength; i++) {
        end[i] = '\0';
    }
    n = write(clientSocket, end, sizeof(end));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
    }
}