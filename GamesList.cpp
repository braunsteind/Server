#include "GamesList.h"

GamesList *GamesList::instance = 0;
pthread_mutex_t GamesList::lock;
pthread_mutex_t GamesList::lock2;
pthread_mutex_t GamesList::lock3;
pthread_mutex_t GamesList::addRunningGameLock;
pthread_mutex_t GamesList::removeRunningGameLock;

GamesList *GamesList::getInstance() {
    if (instance == 0) {
        pthread_mutex_lock(&lock);
        if (instance == 0) {
            instance = new GamesList;
        }
        pthread_mutex_unlock(&lock);
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

vector<GameRoom *> GamesList::getRunningGames() {
    return runningGames;
}

void GamesList::addGame(string gameName, int clientSocket) {
    pthread_mutex_lock(&GamesList::lock2);
    //create game room.
    GameRoom *gameRoom = new GameRoom(clientSocket);
    //insert the game room to map.
    games[gameName] = gameRoom;
    pthread_mutex_unlock(&GamesList::lock2);
}

void GamesList::removeGame(string gameName) {
    pthread_mutex_lock(&GamesList::lock3);
    games.erase(gameName);
    pthread_mutex_unlock(&GamesList::lock3);
}

void GamesList::addRunningGame(GameRoom *gameRoom) {
    pthread_mutex_lock(&GamesList::addRunningGameLock);
    runningGames.push_back(gameRoom);
    pthread_mutex_unlock(&GamesList::addRunningGameLock);
}

void GamesList::removeRunningGameRoom(GameRoom *gameRoom) {
    pthread_mutex_lock(&GamesList::removeRunningGameLock);
    //loop on running games
    for (int i = 0; i < runningGames.size(); i++) {
        //if the running game to remove.
        if (runningGames[i] == gameRoom) {
            //remove the game.
            runningGames.erase(runningGames.begin() + i);
        }
    }
    pthread_mutex_unlock(&GamesList::removeRunningGameLock);
}