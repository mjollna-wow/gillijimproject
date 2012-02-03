#include <vector>
#include <string>
#include "../Chunk.h"
#include "MainAlpha.h"
#include "../Main.h"
#include "../../utilities/Utilities.h"

MainAlpha::MainAlpha() : Chunk()
{
}

MainAlpha::MainAlpha(const std::vector<char> & fullAdtData, int position, int sizeAdjustments) : Chunk(fullAdtData, position, sizeAdjustments)
{
}

MainAlpha::MainAlpha(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("NIAM", givenSize, data) 
{
}

std::vector<int> MainAlpha::getMhdrOffsets() const
{
	std::vector<int> mhdrOffsets(4096);
	int otherMainDataSize = 16;
	int currentMainOffset = 0;
	int mhdrNumber;

	for (mhdrNumber = 0 ; mhdrNumber < 4096 ; mhdrNumber++)
	{
		mhdrOffsets[mhdrNumber] = Utilities::getIntFromCharVector(data, currentMainOffset);
		currentMainOffset = currentMainOffset + otherMainDataSize;
	}

	return mhdrOffsets;
}

Main MainAlpha::toMain()
{
	std::vector<char> mainLkData(32768);

	int i;
	int j = 0;

	for (i = 0 ; i < 65536 ; i = i+16)
	{
		std::cout << "i : " << i << std::endl;
		std::cout << "j : " << j << std::endl;
		if (Utilities::getIntFromCharVector(data, i) != 0)
			mainLkData[j] = 1;
		j = j+8;
	}

	// if there's an offset on alpha (every 16 bytes), every 8 bytes on lk : 1

	Main mainLk = Main("NIAM", 32768, mainLkData);
	return mainLk;
}

std::ostream & operator<<(std::ostream & os, const MainAlpha & main)
{
	os << "Chunk letters : " << main.letters << std::endl;
	os << "Chunk givenSize : " << main.givenSize << std::endl;
	os << "MHDR Offsets in MAIN : " << std::endl;

	std::vector<int> mhdrOffsets = main.getMhdrOffsets();

	std::vector<int>::iterator mhdrOffsetsIter;
	int i = 1;

	for (mhdrOffsetsIter = mhdrOffsets.begin() ; mhdrOffsetsIter != mhdrOffsets.end() ; ++mhdrOffsetsIter)
	{
		if (i % 16 == 0)
			os << *mhdrOffsetsIter << std::endl;
		else
			os << *mhdrOffsetsIter << "\t";
		i++;
	}

	os << "------------------------------" << std::endl;
	return os;
}