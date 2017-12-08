#include "Server.h"
#include "ConfigurationFileHandler.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
    //reading the file
    ConfigurationFileHandler handler;
    handler.readConfigurationFile();
    int port = handler.getPortFromFile();
    //running the server
    Server server(port);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}