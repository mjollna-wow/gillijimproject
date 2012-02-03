#include <vector>
#include <string>
#include "../Chunk.h"
#include "McnkCataTex0.h"
#include "../../utilities/Utilities.h"

McnkCataTex0::McnkCataTex0(const std::vector<char> & fullAdtData, int fullDataOffset, int sizeAdjustments) : Chunk(fullAdtData, fullDataOffset, sizeAdjustments)
{
	const int chunkLettersAndSize = 8;
	fullDataOffset = chunkLettersAndSize + fullDataOffset;

	mcly = Chunk(data, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mcly.getGivenSize();

	mcal = Chunk(data, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mcal.getGivenSize();

	/*if (givenSize > fullDataOffset) // TODO : I don't like the way that looks -_-
	{
		mcmt = Chunk(data, fullDataOffset, sizeAdjustments);
		fullDataOffset = chunkLettersAndSize + fullDataOffset + mcmt.getGivenSize();
	}
	else
	{
		mcmt = Chunk();
	}*/
}

std::ostream & operator<<(std::ostream & os, const McnkCataTex0 & mcnkCataTex0)
{
	os << "Chunk letters : " << mcnkCataTex0.letters << std::endl;
	os << "Chunk givenSize : " << mcnkCataTex0.givenSize << std::endl;

	os << "------------------------------" << std::endl;

	os << mcnkCataTex0.mcly;
	os << mcnkCataTex0.mcal;
	/*os << mcnkCataTex0.mcmt;*/

	os << "------------------------------" << std::endl;
	return os;
}