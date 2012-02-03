#include <vector>
#include <string>
#include <iostream>
#include "Chunk.h"
#include "Mh2o.h"
#include "../utilities/Utilities.h"

Mh2o::Mh2o() : Chunk()
{
}

Mh2o::Mh2o(const std::vector<char> & fullAdtData, int fullDataOffset, int sizeAdjustments)
{
	letters = Utilities::getStringFromCharVector(fullAdtData, fullDataOffset, 4);
	fullDataOffset = fullDataOffset + 4;

	givenSize = Utilities::getIntFromCharVector(fullAdtData, fullDataOffset);
	fullDataOffset = fullDataOffset + 4;

	const int GRETSize = 1413829191;

	if (givenSize == GRETSize)
	{
		givenSize = fullAdtData.size() - fullDataOffset;
		data = Utilities::getCharSubVector(fullAdtData, fullDataOffset, givenSize);
	}
	else 
	{
		data = Utilities::getCharSubVector(fullAdtData, fullDataOffset, givenSize + sizeAdjustments);
	}
}

Mh2o::Mh2o(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("O2HM", givenSize, data) 
{
}