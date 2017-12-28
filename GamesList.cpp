#include "GamesList.h"

GamesList *GamesList::instance = 0;

GamesList *GamesList::getInstance() {
    if (instance == 0) {
        instance = new GamesList;
    }
    return instance;
}

map<string, GameRoom> GamesList::getList() {
    //return copy of the games list.
    return this->games;
}

void GamesList::addGame(string gameName, int clientSocket) {
    //create game room.
    GameRoom gameRoom(clientSocket);
    //insert the game room to map.
    games[gameName] = gameRoom;
}

void GamesList::removeGame(string gameName) {
    games.erase(gameName);
}