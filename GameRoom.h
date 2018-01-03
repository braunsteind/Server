#ifndef SERVER_GAMEROOM_H
#define SERVER_GAMEROOM_H

#include <iostream>
#include <unistd.h>

using namespace std;

class GameRoom {
public:
    /**
     * Constructor.
     * @param clientSocket1 The client socket.
     */
    GameRoom(int clientSocket1);

    /**
     * Add second client to room.
     * @param clientSocket The client socket.
     * @param threadId The thread id.
     */
    void addSecondClient(int clientSocket, pthread_t threadId);

    /**
     * Get client 1 socket number.
     * @return Client 1 socket number.
     */
    int getClient1Socket();

    /**
     * Get client 2 socket number.
     * @return Client 2 socket number.
     */
    int getClient2Socket();

    /**
     * Start to play the game.
     */
    void startGame();

    /**
     * End the game.
     */
    void endGame();

private:
    pthread_t threadId;
    int clientSocket1;
    int clientSocket2;
    pthread_mutex_t lock;

    /**
    * Announce the number to the players.
    * @param clientSocket The client socket.
    * @param number The number of the player.
    */
    void announcePlayerNumber(int clientSocket, char number);

    /**
    * Handle the player's moves.
    * @param clientSocket The client socket.
    * @param row The row that played. -1 to stop the game, -2 for no move.
    * @param col The column that played. -1 to stop the game, -2 for no move.
    * @param stop Function will change it to true if need to stop the game.
    * @param firstTime First time running flag.
    */
    void handlePlayer(int clientSocket, int &row, int &col, bool &stop, bool firstTime);
};

#endif //SERVER_GAMEROOM_H