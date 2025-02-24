#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>
#include <shlobj.h>
#include <urlmon.h>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "urlmon.lib")
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")

// Custom Console Color
void SetConsoleColor(WORD attributes) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}




// Center Console Window To your Screen
void CenterConsoleWindow() {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    HWND consoleWindow = GetConsoleWindow();

    RECT consoleRect;
    GetWindowRect(consoleWindow, &consoleRect);
    int consoleWidth = consoleRect.right - consoleRect.left;
    int consoleHeight = consoleRect.bottom - consoleRect.top;

    int posX = (screenWidth - consoleWidth) / 2;
    int posY = (screenHeight - consoleHeight) / 2;

    SetWindowPos(consoleWindow, HWND_TOP, posX, posY, 0, 0, SWP_NOSIZE);

    LONG style = GetWindowLong(consoleWindow, GWL_EXSTYLE);
    SetWindowLong(consoleWindow, GWL_EXSTYLE, style | WS_EX_LAYERED);
    SetLayeredWindowAttributes(consoleWindow, 0, (BYTE)(255 * 0.9), LWA_ALPHA);
}




// Getting ProccesID By The Name

DWORD GetProcessIdByName(const std::wstring& processName) {
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return 0;
    }

    if (Process32First(hProcessSnap, &pe32)) {
        do {
            if (processName == pe32.szExeFile) {
                CloseHandle(hProcessSnap);
                return pe32.th32ProcessID;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);
    return 0;
}




// Downloading The DLL Thru The Web
// THis Also Stores The DLL in The %temp% Path
bool DownloadFile(const std::wstring& url, const std::wstring& savePath) {
    HRESULT hr = URLDownloadToFileW(NULL, url.c_str(), savePath.c_str(), 0, NULL);
    return (hr == S_OK);
}




// Check If The Game Is Running
bool IsProcessRunning(DWORD pid) {
    HANDLE hProcess = OpenProcess(SYNCHRONIZE, FALSE, pid);
    if (hProcess == NULL) {
        return false;
    }
    DWORD exitCode;
    GetExitCodeProcess(hProcess, &exitCode);
    CloseHandle(hProcess);
    return (exitCode == STILL_ACTIVE);
}




// Doesnt Work So Useless Maybe Coming IN The Future -Cl4vr & Zynco

bool DeleteFileAfterProcessExit(const std::wstring& filePath, DWORD pid) {
    while (IsProcessRunning(pid)) {
        Sleep(100);
    }
    return DeleteFileW(filePath.c_str());
}




// Custom Console Window Size
void SetConsoleWindowSize(int width, int height) {
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}
