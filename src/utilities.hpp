#ifndef UTILITIES_H
#define UTILITIES_H

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <tlhelp32.h>
#include <fstream>

class UTILITIES
{
public:
    std::string GetRegistryValue(HKEY hKey, const std::string& subKey, const std::string& valueName);
    std::string GetComputerName();
    std::string GetArchitectureString(const SYSTEM_INFO& sysInfo);

    std::vector<std::string> GetProcessNames();  // analysis logic
    std::string EnumerateProcesses();           // display/file output

    void SaveToFile(const std::string& systemInfo, const std::string& processInfo);
};

#endif