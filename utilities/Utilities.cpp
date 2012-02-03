#include <vector>
#include <string>
#include "Utilities.h"

namespace Utilities
{
	int getIntFromCharVector(const std::vector<char> & someData, int offset)
	{
		std::vector<char>::const_iterator dataIter;
		char curValues[4];
		int i = 0;
	
		for (dataIter = someData.begin() + offset ; dataIter != someData.begin() + offset + 4 ; ++dataIter)
		{
			curValues[i] = *dataIter;
			i++;
		}
		memcpy(&offset, curValues, sizeof(offset));
	
		return offset;
	}

	float getFloatFromCharVector(const std::vector<char> & someData, int offset)
	{
		float result;
		std::vector<char>::const_iterator dataIter;
		char curValues[4];
		int i = 0;
	
		for (dataIter = someData.begin() + offset ; dataIter != someData.begin() + offset + 4 ; ++dataIter)
		{
			curValues[i] = *dataIter;
			i++;
		}
		memcpy(&result, curValues, sizeof(result));
	
		return result;
	}

	std::string getStringFromCharVector(const std::vector<char> & someData, int start, int stringLength)
	{
		std::string letters = "";
	
		std::vector<char>::const_iterator adtIter;
		for (adtIter = someData.begin() + start ; adtIter != someData.begin() + start + stringLength ; ++adtIter)
		{
			letters = letters + *adtIter;
		}
		return letters;
	}

	std::vector<char> getCharSubVector(const std::vector<char> & someData, int start, int length)
	{
		std::vector<char> subVector;
		std::vector<char>::const_iterator dataIter;

		for (dataIter = someData.begin() + start ; dataIter != someData.begin() + start + length ; ++dataIter)
		{
			subVector.push_back(*dataIter);
		}

		return subVector;
	}

}