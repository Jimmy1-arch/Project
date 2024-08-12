#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Constants
const int PORT = 8086;
const int BUFFER_SIZE = 1024;

// Function to send a file
void sendFile(int socket, const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    // Extract the filename from the file path
    std::string filename = filePath.substr(filePath.find_last_of("/\\") + 1);

    // Send the filename
    send(socket, filename.c_str(), filename.size(), 0);
    usleep(100); // Small delay to ensure filename is sent before FILE_START

    char buffer[BUFFER_SIZE];
    // Notify server about file transfer
    send(socket, "FILE_START", strlen("FILE_START"), 0);

    // Send file content
    while (file.read(buffer, BUFFER_SIZE)) {
        send(socket, buffer, file.gcount(), 0);
    }
    send(socket, buffer, file.gcount(), 0);  // Send remaining bytes

    // Notify server end of file transfer
    send(socket, "FILE_END", strlen("FILE_END"), 0);

    // Receive acknowledgment
    int bytesRead = recv(socket, buffer, BUFFER_SIZE, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Server: " << buffer << std::endl;
    } else {
        std::cerr << "Failed to receive acknowledgment from server." << std::endl;
    }

    std::cout << "File sent successfully: " << filePath << std::endl;
}

// Function to send a message
void sendMessage(int socket, const std::string& message) {
    send(socket, message.c_str(), message.size(), 0);
    std::cout << "Message sent: " << message << std::endl;

    char buffer[BUFFER_SIZE];
    int bytesRead = recv(socket, buffer, BUFFER_SIZE, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Server: " << buffer << std::endl;
    } else {
        std::cerr << "Failed to receive acknowledgment from server." << std::endl;
    }
}

// Main function for automated testing
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <test_mode> [file_path|message]" << std::endl;
        return -1;
    }

    std::string mode = argv[1];
    std::string pathOrMessage = (argc > 2) ? argv[2] : "";

    int socketFd;
    struct sockaddr_in serverAddr;

    // Create socket
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0) {
        std::cerr << "Socket creation error." << std::endl;
        return -1;
    }

    // Connect to server
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported." << std::endl;
        return -1;
    }

    if (connect(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection error." << std::endl;
        return -1;
    }

    // Handle test modes
    if (mode == "file") {
        sendFile(socketFd, pathOrMessage);
    } else if (mode == "message") {
        sendMessage(socketFd, pathOrMessage);
    } else {
        std::cerr << "Invalid test mode. Use 'file' or 'message'." << std::endl;
        close(socketFd);
        return -1;
    }

    close(socketFd);
    return 0;
}
