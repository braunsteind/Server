
#include "ConfigurationFileHandler.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void ConfigurationFileHandler::readConfigurationFile() {
    string portLine;
    string tempPort;
    int i, startIndex = 0;

    //opening file
    ifstream inFile;
    inFile.open("../exe/Configuration");

    //reading the Port line.
    getline(inFile, portLine);
    //done reading from file
    inFile.close();

    //extracting the port number
    for (i = 0; i < portLine.size(); i++) {
        if (portLine[i] == ':') {
            //fixing the starting location
            startIndex = i + 1;
        }
    }
    //cutting the string to Port only
    tempPort = portLine.substr(startIndex);
    this->port = atoi(tempPort.c_str());
}

int ConfigurationFileHandler::getPortFromFile() {
    return port;
}
