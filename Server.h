#ifndef UNTITLED1_SERVER_H
#define UNTITLED1_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>

class Server {
public:
    Server(int port);

    void start();

    void stop();

private:
    int port;
    int serverSocket; // the socket's file descriptor
    /**
     * Handle the player's moves.
     * @param clientSocket The client socket.
     * @param row The row that played. -1 to stop the game, -2 for no move.
     * @param col The column that played. -1 to stop the game, -2 for no move.
     * @param stop Function will change it to true if need to stop the game.
     * @param firstTime First time running flag.
     */
    void handlePlayer(int clientSocket, int &row, int &col, bool &stop, bool firstTime);

    /**
     * Announce the number to the players.
     * @param clientSocket The client socket.
     * @param number The number of the player.
     */
    void announcePlayerNumber(int clientSocket, char number);
};

#endif //UNTITLED1_SERVER_H