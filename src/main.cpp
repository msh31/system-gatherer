#include <windows.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>
#include <fstream> 

std::string GetRegistryValue(HKEY hKey, const std::string& subKey, const std::string& valueName) 
{
    HKEY key;
    char buffer[512];
    DWORD dataSize = sizeof(buffer);
    DWORD type;

    if (RegOpenKeyExA(hKey, subKey.c_str(), 0, KEY_READ, &key) == ERROR_SUCCESS) {
        if (RegQueryValueExA(key, valueName.c_str(), nullptr, &type, (LPBYTE)buffer, &dataSize) == ERROR_SUCCESS) {
            RegCloseKey(key);
            return std::string(buffer);
        }
        RegCloseKey(key);
    }

    return "Unknown";
}

std::string GetComputerName() 
{
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);

    if (!GetComputerNameA(computerName, &size)) { return "Unknown"; }

    return std::string(computerName);
}

void SaveToFile(const std::string& systemInfo, const std::string& processInfo) 
{
    std::ofstream file("sys_intel.txt");
    if (file.is_open()) {
        file << systemInfo << "\n\n" << processInfo;
        file.close();
        std::cout << "\nResults saved to sys_intel.txt\n";
    }
}

std::string EnumerateProcesses()
{
    std::string processInfo = "=== RUNNING PROCESSES ===\n";

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) { return "Failed to create process snapshot\n"; }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) 
    {
        do 
        {
            processInfo += "PID: " + std::to_string(pe32.th32ProcessID) + " | " + std::string(pe32.szExeFile) + "\n";
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return processInfo;
}

int main()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    std::string computerName = GetComputerName();
    std::string productName = GetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName");
    std::string buildNumber = GetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CurrentBuild");
    std::string releaseId = GetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ReleaseId");

    std::string sysInfo = "=== SYSTEM INFORMATION ===\n";
    sysInfo += "OS: " + productName + "\n";
    sysInfo += "Build: " + buildNumber + "\n";
    sysInfo += "Release: " + releaseId + "\n";
    sysInfo += "Processors: " + std::to_string(systemInfo.dwNumberOfProcessors) + "\n";
    sysInfo += "Architecture: " + std::string(systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? "x64" : "x86") + "\n";
    sysInfo += "Computer Name: " + computerName + "\n";

    std::string procInfo = EnumerateProcesses();
    std::cout << sysInfo << "\n" << procInfo;

    SaveToFile(sysInfo, procInfo);

    return 0;
}