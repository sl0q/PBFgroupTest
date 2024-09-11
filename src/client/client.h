#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Client
{
private:
    std::string name;
    int port;
    int interval;
    int clientSocket;

public:
    Client(const std::string &name, int port, int interval);
    void run();

private:
    void _createSocket();
    void _sendMessage();
    std::string _getCurrentTime();
};