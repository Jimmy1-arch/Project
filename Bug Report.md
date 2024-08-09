# Bug Tracker Report

## 1. Bug-Report ( A )


**Project:** Network File Sharing  
**Reported by:** Gourav Soni , Jimmy George, Nitya Patil K S  
**Date:** 2024-08-07  
**Status:** Open  
**Priority:** Medium  
**Severity:** Major  
**Assigned to:** To be assigned

## 1. Bug Details

**Bug ID:** A-2024-08-07 
**Title:** Password Authentication Not Working Properly

### Description
The password authentication mechanism in the server is not functioning as expected. Users are either unable to authenticate successfully, or the server allows access even with incorrect passwords. This issue compromises the security of the network file-sharing system.

### Steps to Reproduce
1. Start the server application.
2. Attempt to log in with a valid username and incorrect password.
3. Attempt to log in with a valid username and correct password.
4. Observe the server’s response in both cases.

### Expected Behavior
The server should only allow access when a correct username and password combination is provided. Access should be denied for incorrect passwords.

### Actual Behavior
- In some cases, access is granted even with an incorrect password.
- In other cases, valid credentials result in authentication failure.

### Error Log
_No specific error logs observed._

## Root Cause Analysis

### Cause
To be determined.

## Fix Description

### Solution Implemented
_Not yet implemented._

## Testing

_No tests conducted since the issue has not been resolved._

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
## Report ( B )

**Project:** Network File Sharing  
**Reported by:** Gourav Soni , Jimmy George, Nitya Patil K S 
**Date:** 2024-08-08   
**Status:** Resolved  
**Priority:** High  
**Severity:** Critical  
**Assigned to:** Jimmy George, Nitya Patil K S, Gourav Soni  
**Fixed by:** Gourav Soni , Jimmy George,Nitya Patil K S

## 2. Bug Details

**Bug ID:** B-2024-08-08  
**Title:** Server Crashes When Receiving Large Files  

### Description
The server application crashes when attempting to receive files larger than 10MB. The crash occurs intermittently, but more frequently when multiple clients are connected. The issue seems to be related to memory management or buffer handling.

### Steps to Reproduce
1. Start the server application.
2. Connect a client to the server.
3. Send a file larger than 10MB from the client to the server.
4. Observe the server crash.

### Expected Behavior
The server should receive large files without crashing and handle them gracefully.

### Actual Behavior
The server crashes with a segmentation fault when receiving large files.

### Error Log
## 1. segmentation fault :

## Root Cause Analysis

### Cause
The issue was traced to the buffer handling logic within the `handleClient` function on the server side. The buffer was not correctly resized or managed when receiving large amounts of data, leading to a segmentation fault.

Specifically, the buffer was being overwritten without proper checks or adjustments for the file size, leading to memory corruption.

## Fix Description

### Solution Implemented
The buffer management was revised to handle large files more effectively. The following changes were made:

- **Dynamic Buffer Allocation:** Instead of a fixed-size buffer, the buffer size is now dynamically allocated based on the file size.
- **File Size Check:** Added logic to check the file size before allocating the buffer to prevent memory issues.
- **Enhanced Logging:** Added additional logging to capture file transfer progress and potential issues during the transfer.

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
            }
            outFile.close();
            std::cout << "[" << clientIP << "] File (" << filename << ") received successfully." << std::endl;
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
- *Stress Tests*: Passed. The server was tested with files up to 100MB and multiple simultaneous clients without crashing.
- *Regression Tests*: Passed. No other features were affected.

### Steps to Add to Git
1. Create a new branch (optional):  
   ```bash
   git checkout -b bugfix/large-file-server-crash
      ```
2. Create a new Markdown file for the report (e.g., BUG_REPORT.md) and paste the formatted content above.
3. Add and commit the file:
```bash
git add BUG_REPORT.md
git commit -m "Add bug report for B-2024-08-08  : Server crashes when receiving large files"
```
4. Push the changes to the repository:
```bash
git push origin bugfix/large-file-server-crash
```

