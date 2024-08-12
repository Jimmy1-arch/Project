#ifndef SERVER_H
#define SERVER_H

#include <string>

void handleClient(int clientSocket, std::string clientIP);
int startServer();

#endif
