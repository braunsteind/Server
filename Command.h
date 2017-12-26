#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <string>
#include <vector>

using namespace std;

class Command {
public:
    virtual void execute(vector<string> args) = 0;

    virtual ~Command() {}
};

#endif //SERVER_COMMAND_H