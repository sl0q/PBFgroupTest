#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Server
{
private:
    int serverSocket;
    int port;
    std::mutex logMutex;

public:
    Server(int port);

    void run();

private:
    void _setupServer();
    void _handleClient(int clientSocket);
    void _logMessage(const std::string &message);
};
