#include "server.h"

Server::Server(int port)
    : port(port)
{
    _setupServer();
}

void Server::run()
{
    while (true)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0)
        {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }
        else
            std::cout << "New socket accepted" << std::endl;
        std::thread(&Server::_handleClient, this, clientSocket).detach();
    }
}

void Server::_setupServer()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "Server socket created" << std::endl;

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Error binding socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "Server socket binded" << std::endl;

    listen(serverSocket, 5);
}

void Server::_handleClient(int clientSocket)
{
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    int n = read(clientSocket, buffer, sizeof(buffer) - 1);
    if (n > 0)
    {
        buffer[n] = '\0';
        _logMessage(buffer);
    }
    int err = close(clientSocket);
}

void Server::_logMessage(const std::string &message)
{
    std::lock_guard<std::mutex> lock(logMutex);
    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile.is_open())
    {
        logFile << message << std::endl;
        logFile.close();
    }
}
