#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <vector>
#include <string>

namespace Utilities
{
	int getIntFromCharVector(const std::vector<char> & someData, int offset);
	float getFloatFromCharVector(const std::vector<char> & someData, int offset);
	std::string getStringFromCharVector(const std::vector<char> & someData, int start, int stringLength);
	std::vector<char> getCharSubVector(const std::vector<char> & someData, int start, int length);
};

#endif