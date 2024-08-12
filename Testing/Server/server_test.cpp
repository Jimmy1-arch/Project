#include "server.h"
#include <gtest/gtest.h>
#include <thread>
#include <sys/types.h>       // For socket-related types
#include <sys/socket.h>      // For socket(), connect(), etc.
#include <netinet/in.h>      // For sockaddr_in, htons()
#include <arpa/inet.h>       // For inet_pton()
#include <unistd.h>          // For close()

// Define the port number
const int PORT = 8086;

// A function to run the server in a separate thread
void startServerInThread() {
    std::thread serverThread(startServer);
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Give the server time to start
    serverThread.detach();  // Ensure the server thread continues running after the test ends
}

// Test to check if the server starts correctly and can accept a connection
TEST(ServerTest, ServerStartsAndAcceptsConnection) {
    startServerInThread();  // Start the server

    // Set up client socket to connect to the server
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_NE(clientSocket, -1) << "Failed to create client socket";

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    // Try to connect to the server
    int result = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    EXPECT_EQ(result, 0) << "Failed to connect to the server";

    // Clean up
    close(clientSocket);
}

// Test to check if the server can receive a file
TEST(ServerTest, ServerReceivesFile) {
    startServerInThread();  // Start the server

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_NE(clientSocket, -1) << "Failed to create client socket";

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    int result = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    ASSERT_EQ(result, 0) << "Failed to connect to the server";

    // Send a filename to the server
    const char* filename = "testfile.txt";
    send(clientSocket, filename, strlen(filename), 0);

    // Send a file start marker
    send(clientSocket, "FILE_START", strlen("FILE_START"), 0);

    // Send some file data
    const char* fileContent = "Hello, World!";
    send(clientSocket, fileContent, strlen(fileContent), 0);

    // Send a file end marker
    send(clientSocket, "FILE_END", strlen("FILE_END"), 0);

    // Receive acknowledgment from the server
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    ASSERT_STREQ(buffer, "ACK: File received");

    // Clean up
    close(clientSocket);

    // Check if the file was created and contains the correct content
    std::ifstream inFile("testfile.txt");
    ASSERT_TRUE(inFile.is_open()) << "File was not created";
    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    ASSERT_EQ(content, fileContent) << "File content does not match";
    inFile.close();

    // Optionally, remove the test file after the test
    std::remove("testfile.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
