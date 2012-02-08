#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"
#include "MphdAlpha.h"
#include "../../utilities/Utilities.h"

MphdAlpha::MphdAlpha() : Chunk()
{
}

MphdAlpha::MphdAlpha(std::ifstream & fullAdtData, int position) : Chunk(fullAdtData, position)
{
}

MphdAlpha::MphdAlpha(const std::vector<char> & fullAdtData, int position, int sizeAdjustments) : Chunk(fullAdtData, position, sizeAdjustments)
{
}

MphdAlpha::MphdAlpha(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("DHPM", givenSize, data) 
{
}

bool MphdAlpha::isWmoBased() const
{
	const int isWmoBasedOffset = 8;
	return Utilities::getIntFromCharVector(data, isWmoBasedOffset) == 2;
}

Mphd MphdAlpha::toMphd()
{
	std::vector<char> mphdLkData(32);

	// I don't think other flags are necessary for alpha to lk... ?
	if (isWmoBased())
		mphdLkData[0] = 1;

	Mphd mphdLk = Mphd("DHPM", 32, mphdLkData);
	return mphdLk;
}