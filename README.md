# Network File Sharing
## Project Overview

**Network File Sharing** is a robust and efficient C++ application designed for transferring files and messages between multiple clients and a central server. The server operates as a hub, accepting connections and facilitating communication between connected clients. This project showcases key networking principles and multi-threading in C++, making it an ideal demonstration of practical client-server interaction.

### Project Team Members :
1. *Jimmy George*
2. *Nitya Patil K S*
3. *Gourav Soni*
   
## Thanks Note : Trainer - **Shweatank Sir**
#### Thank You,
We would like to express our sincere gratitude to **Shweatank Sir** for his invaluable guidance and support throughout the development of this project. Under his mentorship, we have gained in-depth knowledge and practical experience in the following areas:

- **IPC (Inter-Process Communication):** Understanding various methods for processes to communicate and synchronize their actions.
- **POSIX Sockets:** Learning about network communication using POSIX-compliant socket programming.
- **Code Execution:** Gaining insights into efficient code execution and management.
- **Logger:** Implementing logging mechanisms to track and record application behavior and debugging.
- **Security:** Learning best practices and methodologies for securing communication and data.
- **Testing:** Understanding the importance of rigorous testing and how to implement it effectively.
- **Cloud GitLab:** Using cloud-based GitLab for code implementation, version control, and continuous integration/continuous deployment (CI/CD) pipelines.

Thank you, Sir, for your continuous encouragement and for sharing your knowledge with us.

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [System Architecture](#system-architecture)
4. [System Requirements](#system-requirements)
5. [Installation and Setup](#installation-and-setup)
6. [Usage](#usage)
    - [Starting the Server](#starting-the-server)
    - [Connecting the Client](#connecting-the-client)
    - [File Transfer](#file-transfer)
7. [Example Run](#example-run)
8. [Log Management](#log-management)
9. [Contributing](#contributing)
10. [License](#license)
11. [References](#references)

## Introduction

- The **Network File Sharing** project provides a simple yet effective way to demonstrate client-server communication using C++. The server can manage multiple clients simultaneously, allowing them to send files and exchange messages. This README will guide you through setting up, using, and understanding the project's core functionalities.

## Features

### 1. Multi-Client Support
- **Concurrent Connections**: The server can manage multiple client connections simultaneously, thanks to its multi-threaded architecture.

### 2. File Transfer
- **Cross-Platform File Sharing**: Clients can send files to the server from any supported platform. The server saves these files securely for further use.

### 3. Real-Time Messaging
- **Instant Messaging**: Clients can send real-time text messages to the server, which can be logged and reviewed later.

### 4. Comprehensive Logging
- **Timestamped Logs**: All actions, including file transfers and messages, are logged with precise timestamps to ensure traceability.

### 5. Cross-Platform Compatibility
- **Operating System Independence**: The project is compatible with both Windows and Linux environments, ensuring broad accessibility.

## System Architecture

The architecture of this project follows a client-server model, where the server acts as a central node that manages all communication:

1. **Server**: Listens on a specified port, accepting connections from multiple clients. Handles file uploads, stores them, and logs all activities.
2. **Client**: Connects to the server, sending files and messages. Can initiate communication and receive acknowledgments or messages from the server.

## System Requirements

### 1. Operating System
- **Windows 10/11** or **Linux (Ubuntu recommended)**

### 2. Compiler
- **GCC** or **MSVC** (supporting C++11 or later)

### 3. Libraries
- **Boost.Asio**: For handling networking operations.
- **pthread**: For implementing multi-threading.

## Installation and Setup

### 1. Clone the Repository
To get started, clone the project repository to your local machine:

```bash
git clone https://github.com/your-repository/network-file-sharing.git
cd network-file-sharing
```
### 2. Install Dependencies
On Linux:

```bash
sudo apt-get update
sudo apt-get install build-essential libboost-all-dev
```
On Windows:
   1. Install Boost Libraries.
   2. Ensure the paths are set correctly in your environment.

### 3. Compiling the Project
On Linux:

```bash
g++ -std=c++11 -pthread server.cpp -o server -lboost_system
g++ -std=c++11 -pthread client.cpp -o client -lboost_system
```
## Usage

### Server
#### 1. Start the Server:

```bash
./server <port>
```
Replace <port> with the desired port number. The server will begin listening for incoming client connections.

### Client
#### 1. Start the Client:

```bash
./client <server_ip> <port>
```
Replace <server_ip> with the IP address of the server and <port> with the port number.

#### 2. Send a File:
        a. The client will prompt you to enter the file path.After entering it, the file will be sent to the server.
#### 3. Send a Message:
        b. After the file transfer, the client can also send text messages to the server.  

## Example run

### Server Output :
```bash
[2024-08-08 12:00:00] Server started on port 8080
[2024-08-08 12:02:15] Connection accepted from 172.20.0.45:8080
[2024-08-08 12:02:40] Received file 'text.txt' from 172.20.0.35
[2024-08-08 12:03:10] Message received: "Hello, Server this side jimmy!"

[2024-08-08 12:04:15] Connection accepted from 172.20.0.45:8080
[2024-08-08 12:04:30] Received file 'test.txt' from 172.20.0.44
[2024-08-08 12:05:10] Message received: "Hello, Server this side Nithya!"
```
### Client Output :
```bash
[2024-08-08 12:0:00] Connected to server at 172.20.0.45:8080
[2024-08-08 12:02:25] Sending file 'text.txt'
[2024-08-08 12:02:30] File 'text.txt' sent successfully.
[2024-08-08 12:03:00] Message sent: "Hello, Server this side Jimmy!"

[2024-08-08 12:04:10] Connected to server at 172.20.0.45:8080
[2024-08-08 12:04:15] Sending file 'test.txt'
[2024-08-08 12:02:26] File 'test.txt' sent successfully.
[2024-08-08 12:05:05] Message sent: "Hello, Server this side Nithya !"
```

## Log Management
     1. All server logs are stored in log.txt and client logs in log.txt
     2. Logs include detailed timestamps for every execution done after succesfull connection by 'server' and 'client' side.
    
### Use of Logger Tool

#### 1. Server
##### Logger.h
```bash
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();
    void log(const std::string& message);

private:
    std::ofstream log_file;
};

#endif // LOGGER_H
```
##### Logger.cpp
```bash
#include "Logger.h"
#include <iostream>
#include <ctime>

Logger::Logger(const std::string& filename) : log_file(filename, std::ios::app) {
    if (!log_file.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Logger::log(const std::string& message) {
    std::time_t now = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    log_file << buffer << ": " << message << std::endl;
}
```
##### server.cpp
```bash
#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Logger.h"

// Constants
const int PORT = 8080;
const int BUFFER_SIZE = 1024;

// Function to Handle File Reception
void receiveFile(int clientSocket, Logger& logger) {
    std::ofstream file("received_file", std::ios::binary);
    if (!file) {
        logger.log("Error creating file for receiving.");
        return;
    }

    char buffer[BUFFER_SIZE];
    logger.log("Starting file reception.");

    ssize_t bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) {
        if (std::strncmp(buffer, "FILE_END", 8) == 0) {
            break;
        }
        file.write(buffer, bytesReceived);
    }

    logger.log("File received successfully.");
}

// Function to Handle Messages
void receiveMessage(int clientSocket, Logger& logger) {
    char buffer[BUFFER_SIZE] = {0};
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    logger.log("Message received: " + std::string(buffer));
}

int main() {
    Logger logger("log.txt");
    int serverFd, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create socket
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == 0) {
        logger.log("Socket creation error.");
        return -1;
    }
    logger.log("Socket created successfully.");

    // Bind socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        logger.log("Bind failed.");
        return -1;
    }
    logger.log("Bind successful.");

    // Listen for connections
    if (listen(serverFd, 3) < 0) {
        logger.log("Listen failed.");
        return -1;
    }
    logger.log("Server is listening for connections.");

    // Accept connection
    clientSocket = accept(serverFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        logger.log("Accept failed.");
        return -1;
    }
    logger.log("Connection accepted from client.");

    // Handle client interaction
    char buffer[BUFFER_SIZE] = {0};
    while (true) {
        recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (std::strncmp(buffer, "FILE_START", 10) == 0) {
            receiveFile(clientSocket, logger);
        } else if (std::strncmp(buffer, "exit", 4) == 0) {
            logger.log("Client chose to exit.");
            break;
        } else {
            receiveMessage(clientSocket, logger);
        }
    }

    close(clientSocket);
    logger.log("Client socket closed.");
    close(serverFd);
    logger.log("Server shut down.");
    return 0;
}
```
#### 2. Client
##### Logger.h
```bash
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();
    void log(const std::string& message);

private:
    std::ofstream log_file;
};

#endif // LOGGER_H
```
##### Logger.cpp
```bash
#include "Logger.h"
#include <iostream>
#include <ctime>

Logger::Logger(const std::string& filename) : log_file(filename, std::ios::app) {
    if (!log_file.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Logger::log(const std::string& message) {
    std::time_t now = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    log_file << buffer << ": " << message << std::endl;
}
```
##### client.h
```bash
[5:03 pm, 8/8/2024] Jimmy George: #include "Logger.h"
#include <iostream>
#include <ctime>

Logger::Logger(const std::string& filename) : log_file(filename, std::ios::app) {
    if (!log_file.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Logger::log(const std::string& message) {
    std::time_t now = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    log_file << buffer << ": " << message << std::endl;
}

#### client.cpp
```bash
#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Logger.h"

// Constants
const int PORT = 8080;
const int BUFFER_SIZE = 1024;

// Function to Send a File
void sendFile(int socket, const std::string& filePath, Logger& logger) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        logger.log("Error opening file: " + filePath);
        return;
    }

    char buffer[BUFFER_SIZE];
    logger.log("Starting file transfer: " + filePath);
    send(socket, "FILE_START", strlen("FILE_START"), 0);

    while (file.read(buffer, BUFFER_SIZE)) {
        send(socket, buffer, file.gcount(), 0);
    }
    send(socket, buffer, file.gcount(), 0);  // Send remaining bytes

    send(socket, "FILE_END", strlen("FILE_END"), 0);
    logger.log("File sent successfully: " + filePath);
}

// Function to Send a Message
void sendMessage(int socket, const std::string& message, Logger& logger) {
    send(socket, message.c_str(), message.size(), 0);
    logger.log("Message sent: " + message);
}

// Main Function
int main() {
    Logger logger("log.txt");
    int socketFd;
    struct sockaddr_in serverAddr;
    std::string input;

    // Create socket
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0) {
        logger.log("Socket creation error.");
        return -1;
    }
    logger.log("Socket created successfully.");

    // Connect to server
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "172.20.0.45", &serverAddr.sin_addr) <= 0) {
        logger.log("Invalid address/Address not supported.");
        return -1;
    }

    if (connect(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        logger.log("Connection error.");
        return -1;
    }
    logger.log("Connected to server.");

    // Loop for sending messages or files
    while (true) {
        std::cout << "Enter 'file' to send a file, 'message' to send a message, or 'exit' to quit: ";
        std::cin >> input;
        std::cin.ignore();  // Ignore the newline character after input

        if (input == "file") {
            std::string filePath;
            std::cout << "Enter file path: ";
            std::getline(std::cin, filePath);
            logger.log("User chose to send a file.");
            sendFile(socketFd, filePath, logger);
        } else if (input == "message") {
            std::string message;
            std::cout << "Enter message: ";
            std::getline(std::cin, message);
            logger.log("User chose to send a message.");
            sendMessage(socketFd, message, logger);
        } else if (input == "exit") {
            logger.log("User chose to exit.");
            std::cout << "Exiting..." << std::endl;
            break;
        } else {
            logger.log("Invalid option chosen.");
            std::cerr << "Invalid option." << std::endl;
        }
    }

    close(socketFd);
    logger.log("Socket closed, client exited.");
    return 0;
}
```
## Contributing

- If you would like to contribute to this project, please fork the repository and submit a pull request. **For major changes, please open an issue to discuss what you would like to change.**

## License

- This **'Network File Sharing'** project is licensed under the our group - see the LICENSE file for details.

## References

- [Boost.Asio Documentation](#features)
- [Features](#features)
- [Training](#features)
- [Youtube](#features)
- [Google](#features)

## Support

- Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.
  
## Roadmap

- If you have ideas for releases in the future, it is a good idea to list them in the README.
  
