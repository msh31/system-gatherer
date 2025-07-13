#include "utilities.hpp"

std::string UTILITIES::GetRegistryValue(HKEY hKey, const std::string& subKey, const std::string& valueName)
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

std::string UTILITIES::GetComputerName()
{
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    if (!::GetComputerNameA(computerName, &size)) {
        return "Unknown";
    }
    return std::string(computerName);
}

std::string UTILITIES::GetArchitectureString(const SYSTEM_INFO& sysInfo) {
    return std::string(sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? "x64" : "x86");
}

std::string UTILITIES::EnumerateProcesses()
{
    std::string processInfo = "=== RUNNING PROCESSES ===\n";

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return "Failed to create process snapshot\n";
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32))
    {
        do {
            processInfo += "PID: " + std::to_string(pe32.th32ProcessID) + " | " + std::string(pe32.szExeFile) + "\n";
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return processInfo;
}

std::vector<std::string> UTILITIES::GetProcessNames() 
{
    std::vector<std::string> processNames;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return processNames; // return empty vector
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            processNames.push_back(std::string(pe32.szExeFile));
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return processNames;
}

void UTILITIES::SaveToFile(const std::string& systemInfo, const std::string& processInfo)
{
    std::ofstream file("sys_intel.txt");
    if (file.is_open())
    {
        file << systemInfo << "\n\n" << processInfo;
        file.close();
        std::cout << "\nResults saved to sys_intel.txt\n";
    }
}