#ifndef SERVER_SINGLETON_H
#define SERVER_SINGLETON_H
#pragma once

#include <string>
#include <map>
#include "GameRoom.h"


using namespace std;

class GamesList {
public:
    static GamesList *getInstance();

    /**
     * Get the games list.
     * @return The games list.
     */
    map<string, GameRoom> getList();

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
    static GamesList *instance;
    map<string, GameRoom> games;
};

#endif //SERVER_SINGLETON_H