#include "GameRoom.h"

GameRoom::GameRoom(int clientSocket) : clientSocket1(clientSocket), canJoin(true) {}

void GameRoom::addSecondClient(int clientSocket, pthread_t threadId) {
    this->clientSocket2 = clientSocket;
    this->threadId = threadId;
    this->canJoin = false;
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
    close(clientSocket1);
    close(clientSocket2);
}

int GameRoom::getClient1Socket() {
    return clientSocket1;
}

int GameRoom::getClient2Socket() {
    return clientSocket2;
}

bool GameRoom::isFull() {
    //if can join = true return false, else true.
    return (!canJoin);
}

void GameRoom::announcePlayerNumber(int clientSocket, char number) {
    int n = write(clientSocket, &number, sizeof(number));
    if (n == -1) {
        throw "Error writing number to socket";
    }
}

void GameRoom::handlePlayer(int clientSocket, int &row, int &col, bool &stop, bool firstTime) {
    const int serverRun = 1, endOfGame = -1;
    int n;
    //if not first time handling player.
    if (!firstTime) {
        pthread_mutex_lock(&lock);
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
        pthread_mutex_unlock(&lock);
    }

    //read the row.
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
    //write to client that the server is running.
    n = write(clientSocket, &serverRun, sizeof(serverRun));
    if (n == -1) {
        cout << "Error writing col to socket" << endl;
        stop = true;
        return;
    }
    //read the col.
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
    if (row == endOfGame && col == endOfGame) {
        stop = true;
    }
}

void GameRoom::endGame() {
    pthread_mutex_lock(&lock);
    const int endServer = -3;
    int n;
    n = write(clientSocket1, &endServer, sizeof(endServer));
    if (n == -1) {
        cout << "Error writing end of server to socket" << endl;
    }
    n = write(clientSocket2, &endServer, sizeof(endServer));
    if (n == -1) {
        cout << "Error writing end of server to socket" << endl;
    }
    close(clientSocket1);
    close(clientSocket2);
    pthread_cancel(threadId);
    pthread_mutex_unlock(&lock);
}