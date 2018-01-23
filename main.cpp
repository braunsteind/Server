#include "Server.h"
#include "ConfigurationFileHandler.h"
#include <iostream>
#include <stdlib.h>

#define THREADS_NUM 5

using namespace std;

int main() {
    //reading the file
    ConfigurationFileHandler handler;
    handler.readConfigurationFile();
    int port = handler.getPortFromFile();
    //running the server
    Server server(port, THREADS_NUM);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}