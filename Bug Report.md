# Bug Tracker Report

## 1. Bug-Report ( A )


- **Project:** Network File Sharing  
- **Reported by:** Gourav Soni , Jimmy George, Nitya Patil K S  
- **Date:** 2024-08-07  
- **Status:** Open  
- **Priority:** Medium  
- **Severity:** Major 
- **Assigned to:** To be assigned

## 1. Bug Details

- **Bug ID:** A-2024-08-07 
- **Title:** Password Authentication Not Working Properly

### Description
- The password authentication mechanism in the server is not functioning as expected. Users are either unable to authenticate successfully, or the server allows access even with incorrect passwords. This issue compromises the security of the network file-sharing system.

### Steps to Reproduce
1. Start the server application.
2. Attempt to log in with a valid username and incorrect password.
3. Attempt to log in with a valid username and correct password.
4. Observe the server’s response in both cases.

### Expected Behavior
- The server should only allow access when a correct username and password combination is provided. Access should be denied for incorrect passwords.

### Actual Behavior
- In some cases, access is granted even with an incorrect password.
- In other cases, valid credentials result in authentication failure.

### Error Log
- _No specific error logs observed._

## Root Cause Analysis

### Cause
- To be determined.

## Fix Description

### Solution Implemented
- _Not yet implemented._

## Testing

- _No tests conducted since the issue has not been resolved._

## Steps to Add to Git
- Create a new Markdown file (e.g., BUG_REPORT.md) or add this content to the existing one.

- Add and commit the file:
``` bash
git add BUG_REPORT.md
git commit -m "Add bug report for A-2024-08-07: Password authentication not working properly"
```
- Push the changes to the repository:
``` bash
git push origin your-branch-name
```
## Bug-Report ( B )

- **Project:** Network File Sharing  
- **Reported by:** Gourav Soni, Jimmy George, Nitya Patil K S   
- **Date:** 2024-08-09  
- **Status:** Resolved  
- **Priority:** High  
- **Severity:** Major  
- **Assigned to:**  Jimmy George, Nitya Patil K S, Gourav Soni   
- **Fixed by:** To be assigned

## 2. Bug Details

- **Bug ID:** B-2024-08-09  
- **Title:** File Not Received at Server End Despite Successful Transfer

### Description
- There is an issue where the server does not correctly receive files, even though the client indicates that the file has been sent successfully. This leads to missing files on the server side, causing disruptions in file availability and integrity.

### Steps to Reproduce
1. Start the server application.
2. Connect a client to the server.
3. Send a file from the client to the server.
4. Observe the server to check if the file has been received.

### Expected Behavior
- The server should receive and store the file correctly after it has been sent from the client.

### Actual Behavior
- The client confirms the file has been sent, but the server does not receive or store the file as expected.

### Error Log
- _No specific error logs observed._

## Root Cause Analysis

### Cause
- To be determined.

## Fix Description

### Solution Implemented
- To resolve this issue, we decided to display the contents of the file on the server's terminal once it is received successfully. This ensures that the file has been properly received and its contents are intact.

### Code Changes

```cpp
void handleClient(int clientSocket, std::string clientIP) {
    // New dynamic buffer allocation logic
    std::vector<char> buffer(BUFFER_SIZE);
    int bytesRead;

    // Receive filename
    bytesRead = recv(clientSocket, buffer.data(), BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        std::cerr << "[" << clientIP << "] Error receiving filename." << std::endl;
        close(clientSocket);
        return;
    }
    std::string filename(buffer.data(), bytesRead);

    // Log the filename and start receiving the file
    std::cout << "[" << clientIP << "] Receiving file (" << filename << ") from client..." << std::endl;

    std::string fileContents;

    while ((bytesRead = recv(clientSocket, buffer.data(), BUFFER_SIZE, 0)) > 0) {
        if (strncmp(buffer.data(), "FILE_START", 10) == 0) {
            std::ofstream outFile(filename, std::ios::binary);
            if (!outFile) {
                std::cerr << "Error opening file for writing." << std::endl;
                close(clientSocket);
                return;
            }

            std::cout << "[" << clientIP << "] Writing to file: " << filename << std::endl;
            while ((bytesRead = recv(clientSocket, buffer.data(), BUFFER_SIZE, 0)) > 0) {
                if (strncmp(buffer.data(), "FILE_END", 8) == 0) break;
                outFile.write(buffer.data(), bytesRead);
                fileContents.append(buffer.data(), bytesRead);
            }
            outFile.close();

            // Display file contents on the terminal
            std::cout << "[" << clientIP << "] File received successfully. Contents: \n" << fileContents << std::endl;

            send(clientSocket, "ACK: File received", 19, 0);
        } else {
            std::cout << "[" << clientIP << "] Message from client: " << buffer.data() << std::endl;
            send(clientSocket, "ACK: Message received", 21, 0);
        }
    }

    if (bytesRead < 0) {
        std::cerr << "[" << clientIP << "] Error receiving data." << std::endl;
    }

    close(clientSocket);
}
```
## Testing
- *Unit Tests*: Passed.
- *Integration Tests*: Passed.
- *Manual Verification*: The file contents are displayed on the server's terminal upon successful reception.
  
### Steps to Add to Git
1. Update your Markdown file (e.g., `BUG_REPORT.md`) to include this new bug report.

2. Add and commit the file:
   ```bash
   git add BUG_REPORT.md
   git commit -m "Add bug report for B-2024-08-09: File not received at server end despite successful transfer"
```
3. Push the changes to the repository
``` bash
git push origin your-branch-name
```
- *This bug report documents the problem and the implemented solution, ensuring clear tracking of the issue.*



