#ifndef SERVER_SINGLETON_H
#define SERVER_SINGLETON_H
#pragma once

#include <pthread.h>
#include <string>
#include <map>
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

private:
    static GamesList *instance;
    static pthread_mutex_t lock;
    static pthread_mutex_t lock2;
    static pthread_mutex_t lock3;
    map<string, GameRoom *> games;

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