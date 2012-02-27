#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Chunk.h"
#include "McinAlpha.h"
#include "../utilities/Utilities.h"

McinAlpha::McinAlpha() : Chunk()
{
}

McinAlpha::McinAlpha(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

McinAlpha::McinAlpha(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("NICM", givenSize, data)
{
}

std::ostream & operator<<(std::ostream & os, const Mcin & mcin)
{
	os << "Chunk letters : " << mcin.letters << std::endl;
	os << "Chunk givenSize : " << mcin.givenSize << std::endl;
	os << "MCNK Offsets in MCIN : " << std::endl;

	std::vector<int> mcnkOffsets = mcin.getMcnkOffsets();

	std::vector<int>::iterator mcnkOffsetsIter;
	int i = 1;

	for (mcnkOffsetsIter = mcnkOffsets.begin() ; mcnkOffsetsIter != mcnkOffsets.end() ; ++mcnkOffsetsIter)
	{
		if (i % 16 == 0)
			os << *mcnkOffsetsIter << std::endl;
		else
			os << *mcnkOffsetsIter << "\t";
		i++;
	}

	os << "------------------------------" << std::endl;
	return os;
}