#ifndef UNTITLED1_SERVER_H
#define UNTITLED1_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <vector>
#include "CommandsManager.h"

#define DATA_LENGTH 50

class Server {
public:
    Server(int port);

    void start();

    void stop();

private:
    int port;
    int serverSocket; // the socket's file descriptor
    int serverThreadId;
};

/**
 * Wait for client connection.
 * @param serverSocketNumber The server's socket number.
 * @return NULL.
 */
void *startConnection(void *serverSocketNumber);

/**
 * Handle the client.
 * @param clientSocket The client's socket.
 * @return NULL.
 */
void *handleClient(void *clientSocketNumber);

#endif //UNTITLED1_SERVER_H