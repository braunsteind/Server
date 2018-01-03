#ifndef SERVER_SINGLETON_H
#define SERVER_SINGLETON_H
#pragma once

#include <pthread.h>
#include <string>
#include <map>
#include <vector>
#include "GameRoom.h"


using namespace std;

class GamesList {
public:
    /**
     * Get the instance
     * @return The instance.
     */
    static GamesList *getInstance();

    /**
     * Delete the instance.
     */
    static void ResetInstance();

    /**
     * Get the games list.
     * @return The games list.
     */
    map<string, GameRoom *> getList();

    /**
     * Add game to list.
     * @param gameName The game name.
     * @param clientSocket The client socket.
     */
    void addGame(string gameName, int clientSocket);

    /**
     * Remove game from list.
     * @param gameName The game name.
     */
    void removeGame(string gameName);

    /**
     * Get the running games.
     * @return The running games.
     */
    vector<GameRoom *> getRunningGames();

    /**
     * Add running game to game room.
     * @param gameRoom The running game room.
     */
    void addRunningGame(GameRoom *gameRoom);

    /**
     * Close the game room.
     * @param gameRoom The game room to close.
     */
    void removeRunningGameRoom(GameRoom *gameRoom);

private:
    static GamesList *instance;
    static pthread_mutex_t lock;
    static pthread_mutex_t lock2;
    static pthread_mutex_t lock3;
    static pthread_mutex_t addRunningGameLock;
    static pthread_mutex_t removeRunningGameLock;
    map<string, GameRoom *> games;
    vector<GameRoom *> runningGames;

    /**
     * Constructor.
     */
    GamesList() {};

    /**
     * Copy Constructor.
     * @param other The other GamesList.
     */
    GamesList(const GamesList &other);

    /**
     * Destructor.
     */
    ~GamesList() {};
};

#endif //SERVER_SINGLETON_H