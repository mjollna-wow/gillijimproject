#include <vector>
#include <string>
#include "../Chunk.h"	
#include "AdtAlpha.h"
#include "McnkAlpha.h"
#include "../Mcin.h"

AdtAlpha::AdtAlpha(const std::vector<char> & fullAdtData, int fullDataOffset, int adtNum) : adtNumber(adtNum)
{
	const int chunkLettersAndSize = 8;
	int sizeAdjustments = 0;
	
	const int mcinOffset = 0x0;
	const int mtexOffset = 0x4;
	const int mddfOffset = 0x0C;
	const int modfOffset = 0x14;
	
	mhdr = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	const int MhdrStartOffset = fullDataOffset + chunkLettersAndSize;

	fullDataOffset = MhdrStartOffset + mhdr.getOffset(mcinOffset);
	mcin = Mcin(fullAdtData, fullDataOffset, sizeAdjustments);

	fullDataOffset = MhdrStartOffset + mhdr.getOffset(mtexOffset);
	mtex = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	fullDataOffset = MhdrStartOffset + mhdr.getOffset(mddfOffset);
	mddf = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	fullDataOffset = MhdrStartOffset + mhdr.getOffset(modfOffset);
	modf = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

	std::vector<int> mcnkOffsets = mcin.getMcnkOffsets();
	int currentMcnk;

	for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
	{
		fullDataOffset = mcnkOffsets[currentMcnk];
		mcnks.push_back(McnkAlpha(fullAdtData, fullDataOffset, sizeAdjustments));
	}
	
}

std::ostream & operator<<(std::ostream & os, const AdtAlpha & adtAlpha)
{
	os << "ADT #" << adtAlpha.adtNumber << std::endl;
	os << "------------------------------" << std::endl;
	os << adtAlpha.mhdr;
	os << adtAlpha.mcin;
	os << adtAlpha.mtex;
	os << adtAlpha.mddf;
	os << adtAlpha.modf;

	std::vector<McnkAlpha>::const_iterator mcnksIter;
	int i = 0;

	for (mcnksIter = adtAlpha.mcnks.begin() ; mcnksIter != adtAlpha.mcnks.end() ; ++mcnksIter)
	{
		os << "MCNK #" << i << " : " << std::endl;
		os << *mcnksIter;
		i++;
	}

	return os;
}