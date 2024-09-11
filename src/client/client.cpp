#include "client.h"

Client::Client(const std::string &name, int port, int interval)
    : name(name), port(port), interval(interval)
{
}

void Client::run()
{
    while (true)
    {
        _createSocket();
        _sendMessage();
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}

void Client::_createSocket()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "Client socket created" << std::endl;
}

void Client::_sendMessage()
{
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Error connecting to server" << std::endl;
        return;
    }

    std::string message = _getCurrentTime() + " \"" + name + "\"";
    send(clientSocket, message.c_str(), message.size(), 0);
    std::cout << "Message sent" << std::endl;
    close(clientSocket);
}

std::string Client::_getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S.", std::localtime(&now_c));

    return std::string(buffer) + std::to_string(ms.count()) + "]";
}
