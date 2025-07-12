#include <windows.h>
#include <iostream>
#include <string>

std::string GetRegistryValue(HKEY hKey, const std::string& subKey, const std::string& valueName) {
    HKEY key;
    char data[512];
    DWORD dataSize = sizeof(data);
    DWORD type;

    if (RegOpenKeyExA(hKey, subKey.c_str(), 0, KEY_READ, &key) == ERROR_SUCCESS) {
        if (RegQueryValueExA(key, valueName.c_str(), nullptr, &type, (LPBYTE)data, &dataSize) == ERROR_SUCCESS) {
            RegCloseKey(key);
            return std::string(data);
        }
        RegCloseKey(key);
    }

    return "Unknown";
}

int main() {
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    std::string productName = GetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName");
    std::string buildNumber = GetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CurrentBuild");
    std::string releaseId = GetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ReleaseId");

    std::cout << "=== SYSTEM INFORMATION ===" << "\n";
    std::cout << "OS: " << productName << "\n";
    std::cout << "Build: " << buildNumber << "\n";
    std::cout << "Release: " << releaseId << "\n";
    std::cout << "Processors: " << systemInfo.dwNumberOfProcessors << "\n";
    std::cout << "Architecture: " << (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? "x64" : "x86") << "\n";

    return 0;
}