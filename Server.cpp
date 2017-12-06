#include "Server.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

Server::Server(int port) : port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in player1Address, player2Address;
    socklen_t player1AddressLen, player2AddressLen;
    while (true) {
        cout << "Waiting for players connections..." << endl;
        // Accept player1 connection
        int player1Socket = accept(serverSocket, (struct sockaddr *) &player1Address, &player1AddressLen);
        cout << "Player 1 is connected" << endl;
        if (player1Socket == -1) {
            throw "Error on accept";
        }
        // Accept player2 connection
        int player2Socket = accept(serverSocket, (struct sockaddr *) &player2Address, &player2AddressLen);
        cout << "Player 2 is connected" << endl;
        if (player2Socket == -1) {
            throw "Error on accept";
        }
        //send players there number.
        announcePlayerNumber(player1Socket, '1');
        announcePlayerNumber(player2Socket, '2');
        int row, col;
        bool firstTime = true, stop = false;
        //play the game.
        while (!stop) {
            handlePlayer(player1Socket, row, col, stop, firstTime);
            firstTime = false;
            if (!stop) {
                handlePlayer(player2Socket, row, col, stop, firstTime);
            }
        }
        // Close communication with the players.
        close(player1Socket);
        close(player2Socket);
    }
}

//Handle players.
void Server::handlePlayer(int clientSocket, int &row, int &col, bool &stop, bool firstTime) {
    int n;
    //if not first time handling player.
    if (!firstTime) {
        //send the other player the played move.
        n = write(clientSocket, &row, sizeof(row));
        if (n == -1) {
            throw "Error writing row to socket";
        }
        n = write(clientSocket, &col, sizeof(col));
        if (n == -1) {
            throw "Error writing col to socket";
        }
    }
    // Read the player's move.
    n = read(clientSocket, &row, sizeof(row));
    if (n == -1) {
        cout << "Error reading the move" << endl;
        return;
    }
    if (n == 0) {
        cout << "Player disconnected" << endl;
        return;
    }
    n = read(clientSocket, &col, sizeof(col));
    if (n == -1) {
        cout << "Error reading the col" << endl;
        return;
    }
    if (n == 0) {
        cout << "Player disconnected" << endl;
        return;
    }
    //if game ended.
    if (row == -1 && col == -1) {
        stop = true;
    }
}

void Server::announcePlayerNumber(int clientSocket, char number) {
    int n = write(clientSocket, &number, sizeof(number));
    if (n == -1) {
        throw "Error writing number to socket";
    }
}

void Server::stop() {
    close(serverSocket);
}