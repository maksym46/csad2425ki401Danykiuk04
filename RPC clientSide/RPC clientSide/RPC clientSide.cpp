#include <iostream>
#include <string>
#include <windows.h>

HANDLE serialHandle;
bool initializeSerialPort(const std::string& portName) {
    std::wstring widePortName(portName.begin(), portName.end());
    serialHandle = CreateFile(
        widePortName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (serialHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open serial port: " << portName << std::endl;
        return false;
    }

    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);
    GetCommState(serialHandle, &serialParams);
    serialParams.BaudRate = CBR_9600;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY;
    SetCommState(serialHandle, &serialParams);

    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 50;
    timeout.ReadTotalTimeoutConstant = 50;
    timeout.ReadTotalTimeoutMultiplier = 10;
    timeout.WriteTotalTimeoutConstant = 50;
    timeout.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(serialHandle, &timeout);

    return true;
}

void sendMove(const std::string& move) {
    DWORD bytesWritten;
    WriteFile(serialHandle, move.c_str(), move.length(), &bytesWritten, NULL);
    WriteFile(serialHandle, "\n", 1, &bytesWritten, NULL);
}
std::string receiveResponse() {
    char buffer[256];
    DWORD bytesRead;
    if (ReadFile(serialHandle, buffer, sizeof(buffer), &bytesRead, NULL)) {
        return std::string(buffer, bytesRead);
    }
    return "";
}

int main() {
    std::string portName = "COM3";  
    if (!initializeSerialPort(portName)) {
        return 1;
    }

    std::cout << "Connected to Arduino on " << portName << std::endl;

    while (true) {
        std::cout << "Enter your move (Rock, Paper, Scissors) or type EXIT to quit: ";
        std::string clientMove;
        std::getline(std::cin, clientMove);

        if (clientMove == "EXIT") {
            break;
        }

        sendMove(clientMove);  
        std::string clientResponse = receiveResponse();
        std::cout << "Server response: " << clientResponse << std::endl;
    }

    CloseHandle(serialHandle);
    return 0;
}
