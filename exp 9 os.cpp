#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define PIPE_NAME "\\\\.\\pipe\\SamplePipe"

int main() {
    HANDLE hPipe;
    DWORD dwRead, dwWritten;
    char buffer[1024];
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

    hPipe = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                            PIPE_UNLIMITED_INSTANCES, 1024, 1024, 0, &sa);
    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Failed to create pipe. Error: %lu\n", GetLastError());
        return 1;
    }

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, "child_program.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed with error %lu\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    Sleep(1000);
    ConnectNamedPipe(hPipe, NULL);

    snprintf(buffer, sizeof(buffer), "Hello from Sender!");
    WriteFile(hPipe, buffer, strlen(buffer) + 1, &dwWritten, NULL);
    printf("Parent (Sender) sent: %s\n", buffer);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(hPipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
