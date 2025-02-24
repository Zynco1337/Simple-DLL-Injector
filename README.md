# Zynco Simple DLL Injector Using Remote Thread Injection

A clean, and efficient cheat injector that utilizes a Classic DLL Injection via Remote Thread Injection. This tool automatically downloads the required DLL and places it in the temp folder for injection.

## Features
- **DLL Injection**: Injects a dynamic link library (DLL) into any running process.
- **Window Hooking**: Uses a Windows hook for targeted injection, ensuring efficiency and reliability.
- **Automatic DLL Download**: Downloads the required DLL from a specified URL.
- **Temporary Storage**: Places the DLL in the Temp folder for security and organization.

## Requirements
- **Windows Operating System** (Windows 7/8/10 or later).
- **Administrator Privileges** for injection.
- **Internet Connection** for downloading the DLL.

## Usage

1. **Run the Injector**: 
   - Launch the injector application.
   - Provide the necessary parameters (e.g., target process, DLL URL).

2. **Injection Process**:
   - The injector will download the DLL and save it to the temporary folder.
   - It will hook into the target process and inject the DLL.

3. **Verify Injection**:
   - Once the process is complete, verify if the DLL has been injected by checking the target process's memory or using relevant debugging tools.

## Methods Used in the Code:

1. **Downloading the DLL**:
   - The injector downloads the DLL from a specified URL.
   - It saves the DLL to the system's temporary directory using `GetTempPathA` and `DownloadFile`.

2. **Finding the Target Process**:
   - The code identifies the target process (e.g., `ExampleGameName.exe`) by its name.
   - It retrieves the process ID (PID) of the running application using `GetProcessIdByName`.

3. **Opening the Target Process**:
   - Using the process ID (PID), the code opens the target process for manipulation using `OpenProcess` with `PROCESS_ALL_ACCESS` to grant full control.

4. **Allocating Memory in the Target Process**:
   - The code allocates memory within the target process using `VirtualAllocEx`.
   - It reserves memory space for storing the path to the DLL that will be injected.

5. **Writing the DLL Path to the Target Process**:
   - The injector writes the path of the downloaded DLL into the allocated memory of the target process using `WriteProcessMemory`.

6. **Loading the DLL**:
   - The code retrieves the address of the `LoadLibraryW` function from `kernel32.dll` using `GetProcAddress`.
   - A remote thread is created in the target process via `CreateRemoteThread`, which calls `LoadLibraryW` with the DLL path to inject the DLL.

7. **Cleanup**:
   - After injection, the allocated memory is released using `VirtualFreeEx`, and handles to the process and thread are closed.
   - The DLL is deleted from the temp directory after the target process exits using `DeleteFileAfterProcessExit`.


## Contributing

If you'd like to contribute, feel free to fork the repository and create a pull request. Any improvements, bug fixes, or feature additions are welcome!

## License

This project is licensed under the MIT License 

## Disclaimer

This tool is meant for educational purposes only. Use at your own risk. I Am NOT responsible for any Bans That Happens When Using,
