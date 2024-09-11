#include <iostream>
#include <string>

#include "client.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: client <name> <port> <interval>" << std::endl;
        return 1;
    }

    std::string name = argv[1];
    int port = std::stoi(argv[2]);
    int interval = std::stoi(argv[3]);

    Client client(name, port, interval);
    client.run();

    return 0;
}