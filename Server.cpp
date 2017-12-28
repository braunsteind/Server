#include "Server.h"

#define MAX_CONNECTED_CLIENTS 10
using namespace std;

Server::Server(int port) : port(port), serverSocket(0) {
    cout << "Server" << endl;
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
    pthread_t pthread;
    pthread_create(&pthread, NULL, startConnection, (void *) serverSocket);
    pthread_exit(NULL);
}

void Server::stop() {
    close(serverSocket);
}

void *startConnection(void *serverSocketNumber) {
    //int serverSocket = (int) serverSocketNumber;
    int serverSocket = 5;
    //create vector of threads.
    vector<pthread_t> threads;
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
        //add new thread
        threads.push_back(threads.size());
        pthread_create(&threads[threads.size() - 1], NULL, handleClient, (void *) clientSocket);
        //close communication with the client.
        //close(clientSocket);
    }
    return NULL;
}

void *handleClient(void *clientSocketNumber) {
    CommandsManager cm;
    int n, spaceIndex, twoWordsCommand = 0, dataLength = 0;
    int clientSocket = (int) clientSocketNumber;
    char data[DATA_LENGTH];
    while (true) {
        n = read(clientSocket, &data, sizeof(data));
        if (n == -1) {
            cout << "Error reading command" << endl;
            return NULL;
        }
        //if client disconnected.
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return NULL;
        }
        //loop on the data from client.
        for (int i = 0; i < DATA_LENGTH; i++) {
            //update the length
            dataLength++;
            //check if the command ended and if it's one or two words.
            if (data[i] == '\0') {
                break;
            } else if (data[i] == ' ') {
                spaceIndex = i;
                twoWordsCommand = 1;
            }
        }
        char command1[5];
        vector<string> args;
        //if one word command.
        if (twoWordsCommand == 0) {
            //create command.
            char command[dataLength];
            //copy the command.
            for (int i = 0; i < dataLength; i++) {
                command[i] = data[i];
            }
            cm.executeCommand(string(command), args);
        } else { //if two words command.
            char command[spaceIndex + 1];
            char name[dataLength - (spaceIndex + 1)];
            //copy the command.
            for (int i = 0; i < spaceIndex; i++) {
                command[i] = data[i];
            }
            command[spaceIndex] = '\0';
            //copy the name.
            for (int i = spaceIndex + 1; i < dataLength; i++) {
                name[i] = data[i];
            }
            args.push_back(string(name));
            cm.executeCommand(string(command), args);
        }
    }
    return NULL;
}