#include "GameRoom.h"

GameRoom::GameRoom(int clientSocket) {
    this->clientSocket1 = clientSocket;
}

void GameRoom::addSecondClient(int clientSocket) {
    this->clientSocket2 = clientSocket;
}

void GameRoom::startGame() {
    //send players there number.
    announcePlayerNumber(clientSocket1, '1');
    announcePlayerNumber(clientSocket2, '2');
    int row, col;
    bool firstTime = true, stop = false;
    //play the game.
    while (!stop) {
        handlePlayer(clientSocket1, row, col, stop, firstTime);
        firstTime = false;
        if (!stop) {
            handlePlayer(clientSocket2, row, col, stop, firstTime);
        }
    }
}

int GameRoom::getClient1Socket() {
    return clientSocket1;
}

int GameRoom::getClient2Socket() {
    return clientSocket2;
}

void GameRoom::announcePlayerNumber(int clientSocket, char number) {
    int n = write(clientSocket, &number, sizeof(number));
    if (n == -1) {
        throw "Error writing number to socket";
    }
}

void GameRoom::handlePlayer(int clientSocket, int &row, int &col, bool &stop, bool firstTime) {
    int n;
    //if not first time handling player.
    if (!firstTime) {
        //send the other player the played move.
        n = write(clientSocket, &row, sizeof(row));
        if (n == -1) {
            cout << "Error writing row to socket" << endl;
            stop = true;
            return;
        }
        n = write(clientSocket, &col, sizeof(col));
        if (n == -1) {
            cout << "Error writing col to socket" << endl;
            stop = true;
            return;
        }
    }
    //read the player's move.
    n = read(clientSocket, &row, sizeof(row));
    if (n == -1) {
        cout << "Error reading row" << endl;
        stop = true;
        return;
    }
    //if player disconnected.
    if (n == 0) {
        cout << "Player disconnected" << endl;
        //stop the game.
        stop = true;
        return;
    }
    n = read(clientSocket, &col, sizeof(col));
    if (n == -1) {
        cout << "Error reading col" << endl;
        stop = true;
        return;
    }
    if (n == 0) {
        cout << "Player disconnected" << endl;
        stop = true;
        return;
    }
    //if game ended.
    if (row == -1 && col == -1) {
        stop = true;
    }
}
