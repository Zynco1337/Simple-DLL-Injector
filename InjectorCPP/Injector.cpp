
#include "functions.h"

//Check The functions.h File For All The Methods Enjoy!
//And Please Dont Skid This :)
// https://github.com/Zynco1337

int main() {
    SetConsoleWindowSize(50, 20);
    CenterConsoleWindow();
    

    std::wstring processName = L"ExampleGameName.exe";  //This Is Your Game Name Like "Roblox.exe"
    std::wstring tempDir;
    char tempPath[MAX_PATH];
    std::wstring dllPath, downloadUrl = L"https://YourDLLWebsite.com/Example.dll";   // The Website To Your DLL. Be Sure That The DLL Auto Downloades When Opening Your Website.
    dllPath = std::wstring(tempPath, tempPath + strlen(tempPath)) + L"Example.dll";  // Please Enter Your DLL Name here

    if (!GetTempPathA(MAX_PATH, tempPath)) {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "[-]Error 92YT" << std::endl;       //  std::cerr << "ERROR: Failed to get temp path!" << std::endl;
        std::cerr << "[-]Closing in 5 Seconds" << std::endl;

        Sleep(5000);
        return 1;
    }
    

    if (!DownloadFile(downloadUrl, dllPath)) {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "[-]Error 15QK" << std::endl;       //  std::cerr << "Failed to the DLL!" << std::endl;
        std::cerr << "[-]Closing in 5 Seconds" << std::endl; 

        Sleep(5000);
        return 1;
    }

    DWORD pid = GetProcessIdByName(processName);
    if (pid == 0) {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "[-]Game not found/Game not Open!" << std::endl;
        std::cerr << "[-]Closing in 5 Seconds" << std::endl;
        Sleep(5000);
        return 1;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess) {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "[-]Error 67AP" << std::endl;      //   std::cerr << "Failed to open process!" << std::endl;
        std::cerr << "[-]Closing in 5 Seconds" << std::endl;

        Sleep(5000);
        return 1;
    }

    LPVOID allocMem = VirtualAllocEx(hProcess, NULL, dllPath.size() * sizeof(wchar_t), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!allocMem) {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "[-]Error 83XJ" << std::endl;      //   std::cerr << "Failed to allocate memory!" << std::endl;
        std::cerr << "[-]Closing in 5 Seconds" << std::endl;

        CloseHandle(hProcess);
        Sleep(5000);
        return 1;
    }

    if (!WriteProcessMemory(hProcess, allocMem, dllPath.c_str(), dllPath.size() * sizeof(wchar_t), NULL)) {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "[-]Error 41KL" << std::endl;     //    std::cerr << "Failed to write memory!" << std::endl;
        std::cerr << "[-]Closing in 5 Seconds" << std::endl;

        VirtualFreeEx(hProcess, allocMem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        Sleep(5000);
        return 1;
    }

    FARPROC loadLibraryAddr = GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");
    if (!loadLibraryAddr) {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "[-]Error 58FV" << std::endl;      //   std::cerr << "Failed to get LoadLibraryW address!" << std::endl;
        std::cerr << "[-]Closing in 5 Seconds" << std::endl;

        VirtualFreeEx(hProcess, allocMem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        Sleep(5000);
        return 1;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, allocMem, 0, NULL);
    if (!hThread) {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cerr << "[-]Error 72DM" << std::endl;     //    std::cerr << "Failed to create remote thread!" << std::endl;
        std::cerr << "[-]Closing in 5 Seconds" << std::endl;

        VirtualFreeEx(hProcess, allocMem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        Sleep(5000);
        return 1;
    }

    WaitForSingleObject(hThread, INFINITE);

    VirtualFreeEx(hProcess, allocMem, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
    SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::wcout << L"[+]Injection successful!" << std::endl;
    std::wcout << L"[+]Cleaning up & Closing in 5 Seconds!" << std::endl; // Maybe Adding DLL Debugging Soon

    DeleteFileAfterProcessExit(dllPath, pid);
    Sleep(5000);
    return 0;
}
