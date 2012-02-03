#include <vector>
#include <iostream>
#include <string>
#include "../Chunk.h"
#include "McnkLk.h"
#include "../../utilities/Utilities.h"

McnkLk::McnkLk(const std::vector<char> & fullAdtData, int fullDataOffset, int sizeAdjustments) : Chunk(fullAdtData, fullDataOffset, sizeAdjustments)
{
	const int mcnkHeaderSize = 128;
	const int chunkLettersAndSize = 8;
	const int headerStartOffset = fullDataOffset;

	fullDataOffset = chunkLettersAndSize + fullDataOffset;

	mcnkHeader = Utilities::getCharSubVector(fullAdtData, fullDataOffset, mcnkHeaderSize);

	const int mcvtOffset = 0x014;
	const int mccvOffset = 0x074;
	const int mcnrOffset = 0x018;
	const int mclyOffset = 0x01C;
	const int mcrfOffset = 0x020;
	const int mcshOffset = 0x02C;
	const int mcalOffset = 0x024;
	const int mclqOffset = 0x060;
	const int mcseOffset = 0x058;

	fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcvtOffset);

	mcvt = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	if (Utilities::getIntFromCharVector(mcnkHeader, mccvOffset) != 0)
	{
		fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mccvOffset);
		mccv = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);
	}

	sizeAdjustments = sizeAdjustments + 13;
	fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcnrOffset);
	mcnr = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	sizeAdjustments = 0;
	fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mclyOffset);
	mcly = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcrfOffset);
	mcrf = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	if (Utilities::getIntFromCharVector(mcnkHeader, mcshOffset) != 0)
	{
		fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcshOffset);
		mcsh = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);
	}

	fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcalOffset);
	mcal = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	if (Utilities::getIntFromCharVector(mcnkHeader, mclqOffset) != 0)
	{
		fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mclqOffset);
		mclq = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);
	}

	if (Utilities::getIntFromCharVector(mcnkHeader, mcseOffset) != 0)
	{
		fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcseOffset);
		mcse = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);
	}
}

std::ostream & operator<<(std::ostream & os, const McnkLk & mcnkLk)
{
	os << "Chunk letters : " << mcnkLk.letters << std::endl;
	os << "Chunk givenSize : " << mcnkLk.givenSize << std::endl;

	os << "------------------------------" << std::endl;

	os << mcnkLk.mcvt;
	os << mcnkLk.mccv;
	os << mcnkLk.mcnr;
	os << mcnkLk.mcly;
	os << mcnkLk.mcrf;
	os << mcnkLk.mcsh;
	os << mcnkLk.mcal;
	os << mcnkLk.mclq;
	os << mcnkLk.mcse;

	os << "------------------------------" << std::endl;
	return os;
}