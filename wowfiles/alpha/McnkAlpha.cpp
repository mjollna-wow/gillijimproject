#include <vector>
#include <iostream>
#include <string>
#include "../Chunk.h"
#include "McnkAlpha.h"
#include "../../utilities/Utilities.h"

McnkAlpha::McnkAlpha(const std::vector<char> & fullAdtData, int fullDataOffset, int sizeAdjustments) : Chunk(fullAdtData, fullDataOffset, sizeAdjustments)
{
	const int mcnkHeaderSize = 128;
	const int chunkLettersAndSize = 8;
	const int headerStartOffset = fullDataOffset;

	fullDataOffset = chunkLettersAndSize + fullDataOffset;

	mcnkHeader = Utilities::getCharSubVector(fullAdtData, fullDataOffset, mcnkHeaderSize);

	const int mcvtOffset = 0x018;
	const int mcvtSize = 580;
	const int mcnrOffset = 0x01C;
	const int mcnrSize = 448;
	const int mclyOffset = 0x020;
	const int mcrfOffset = 0x024;
	const int mcshOffset = 0x030;
	const int mcshSizeOffset = 0x034;
	const int mcalOffset = 0x028;
	const int mcalSizeOffset = 0x02C;
	const int mcnkSizeOffset = 0x05C;
	const int mclqOffset = 0x064;

	fullDataOffset = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcvtOffset);
	std::vector<char> mcvtData = Utilities::getCharSubVector(fullAdtData, fullDataOffset, mcvtSize);
	mcvt = Chunk("TVCM", mcvtSize, mcvtData);

	fullDataOffset = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcnrOffset);
	std::vector<char> mcnrData = Utilities::getCharSubVector(fullAdtData, fullDataOffset, mcnrSize);
	mcnr = Chunk("RNCM", mcnrSize, mcnrData);

	fullDataOffset = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mclyOffset);
	mcly = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	fullDataOffset = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcrfOffset);
	mcrf = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	fullDataOffset = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcshOffset);
	int mcshSize = Utilities::getIntFromCharVector(mcnkHeader, mcshSizeOffset);
	std::vector<char> mcshData = Utilities::getCharSubVector(fullAdtData, fullDataOffset, mcshSize);
	mcsh = Chunk("HSCM", mcshSize, mcshData);

	fullDataOffset = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcalOffset);
	int mcalSize = Utilities::getIntFromCharVector(mcnkHeader, mcalSizeOffset);
	std::vector<char> mcalData = Utilities::getCharSubVector(fullAdtData, fullDataOffset, mcalSize);
	mcal = Chunk("LACM", mcalSize, mcalData);

	fullDataOffset = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mclqOffset);
	int mclqSize = Utilities::getIntFromCharVector(mcnkHeader, mcnkSizeOffset) - Utilities::getIntFromCharVector(mcnkHeader, mclqOffset);
	std::vector<char> mclqData = Utilities::getCharSubVector(fullAdtData, fullDataOffset, mclqSize);
	mclq = Chunk("QLCM", mclqSize, mclqData);
}

std::ostream & operator<<(std::ostream & os, const McnkAlpha & mcnkAlpha)
{
	os << "Chunk letters : " << mcnkAlpha.letters << std::endl;
	os << "Chunk givenSize : " << mcnkAlpha.givenSize << std::endl;

	os << "------------------------------" << std::endl;

	os << mcnkAlpha.mcvt;
	os << mcnkAlpha.mcnr;
	os << mcnkAlpha.mcly;
	os << mcnkAlpha.mcrf;
	os << mcnkAlpha.mcsh;
	os << mcnkAlpha.mcal;
	os << mcnkAlpha.mclq;

	os << "------------------------------" << std::endl;
	return os;
}