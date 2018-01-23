#include <sstream>
#include "Server.h"
#include "ThreadPool.h"

#define MAX_CONNECTED_CLIENTS 10
using namespace std;

struct ThreadArgs {
    pthread_t *threadId;
    int clientSocket;
};

struct StartArgs {
    int serverSocket;
    ThreadPool *threadPool;
};

Server::Server(int port, int threadsNum) : port(port), serverSocket(0), serverThreadId(0) {
    cout << "Server" << endl;
    //create thread pool.
    threadPool = new ThreadPool(threadsNum);
}

void Server::start() {
    //create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    //assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    //start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    pthread_t serverThreadId;
    StartArgs startArgs;
    startArgs.serverSocket = serverSocket;
    startArgs.threadPool = threadPool;
    pthread_create(&serverThreadId, NULL, startConnection, (void *) &startArgs);

    //while not getting exit.
    string input;
    while (input.compare("exit") != 0) {
        //get input.
        cin >> input;
    }
    stop();
}

void Server::stop() {
    GamesList *gamesList = GamesList::getInstance();
    vector<GameRoom *> runningGames = gamesList->getRunningGames();
    map<string, GameRoom *> openedGames = gamesList->getList();

    //loop on running games.
    for (int i = 0; i < runningGames.size(); i++) {
        //end game.
        runningGames[i]->endGame();
    }
    //loop on the opened games.
    for (map<string, GameRoom *>::iterator it = openedGames.begin(); it != openedGames.end(); it++) {
        it->second->endGame();
    }

    //terminate thread pool.
    threadPool->terminate();

    //close the thread the server.
    pthread_cancel(serverThreadId);
    close(serverSocket);
}

void *startConnection(void *sArgs) {
    //get args.
    struct StartArgs *startArgs = (struct StartArgs *) sArgs;
    int serverSocket = startArgs->serverSocket;
    ThreadPool *threadPool = startArgs->threadPool;

    //create vector of threads.
    while (true) {
        //define the client socket's structures
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen;
        cout << "Waiting for clients connections..." << endl;
        //accept client connection
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        cout << "client is connected" << endl;
        if (clientSocket == -1) {
            throw "Error on accept";
        }
        //add new thread.
        pthread_t thread;
        ThreadArgs args;
        args.threadId = &thread;
        args.clientSocket = clientSocket;
        //pthread_create(&thread, NULL, handleClient, (void *) &args);
        threadPool->addTask(new Task(handleClient, (void *) &args));
    }
    return NULL;
}

void *handleClient(void *tArgs) {
    CommandsManager cm;
    //the thread args.
    struct ThreadArgs *threadArgsArgs = (struct ThreadArgs *) tArgs;
    pthread_t pthread = *(threadArgsArgs->threadId);
    int clientSocket = threadArgsArgs->clientSocket;

    //get client's commands.
    char data[DATA_LENGTH];
    int n = read(clientSocket, &data, sizeof(data));
    if (n == -1) {
        cout << "Error reading command" << endl;
        return NULL;
    }
    //if client disconnected.
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return NULL;
    }

    //split the data.
    string str(data);
    istringstream iss(str);
    string command;
    iss >> command;
    vector<string> args;
    //add data to args vector.
    while (iss) {
        string arg;
        iss >> arg;
        args.push_back(arg);
    }

    //execute command.
    cm.executeCommand(string(command), args, clientSocket, pthread);
    return NULL;
}