#include "GamesList.h"

GamesList *GamesList::instance = 0;

GamesList *GamesList::getInstance() {
    if (instance == 0) {
        instance = new GamesList;
    }
    return instance;
}

void GamesList::ResetInstance() {
    delete instance;
    //so getInstance will still work.
    instance = 0;
}

map<string, GameRoom *> GamesList::getList() {
    //return copy of the games list.
    return games;
}

void GamesList::addGame(string gameName, int clientSocket) {
    //create game room.
    GameRoom *gameRoom = new GameRoom(clientSocket);
    //insert the game room to map.
    games[gameName] = gameRoom;
}

void GamesList::removeGame(string gameName) {
    delete games[gameName];
    games.erase(gameName);
}