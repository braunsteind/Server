#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <string>
#include <vector>

using namespace std;

class Command {
public:
    virtual void execute(vector<string> args, int clientSocket = 0, pthread_t threadId = 0) = 0;

    virtual ~Command() {}
};

#endif //SERVER_COMMAND_H