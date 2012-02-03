#include <vector>
#include <string>
#include "WdtAlpha.h"
#include "MphdAlpha.h"
#include "../Wdt.h"
#include "AdtAlpha.h"
#include "Monm.h"
#include "../Chunk.h"
#include "MainAlpha.h"
#include "../../utilities/FileHandling.h"
#include "../../utilities/Utilities.h"

WdtAlpha::WdtAlpha(const std::string & wdtAlphaFile)
{
	FileHandling file(wdtAlphaFile);
	std::vector<char> fullData = file.getFullFile();

	const int chunkLettersAndSize = 8;
	const int mdnmOffset = 4;
	const int monmOffset = 12;
	//const int modfHintOffset = 8; // TODO : remove if ok

	int fullDataOffset = 0;
	int sizeAdjustments = 0;

	mver = Chunk(fullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mver.getGivenSize();

	const int MphdStartOffset = fullDataOffset + chunkLettersAndSize; 

	mphd = MphdAlpha(fullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mphd.getGivenSize();

	main = MainAlpha(fullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + main.getGivenSize(); 

	fullDataOffset = Utilities::getIntFromCharVector(fullData, MphdStartOffset + mdnmOffset);
	mdnm = Chunk(fullData, fullDataOffset, sizeAdjustments);

	fullDataOffset = Utilities::getIntFromCharVector(fullData, MphdStartOffset + monmOffset); 
	monm = Monm(fullData, fullDataOffset, sizeAdjustments);

	fullDataOffset = chunkLettersAndSize + fullDataOffset + monm.getGivenSize();

	if (mphd.isWmoBased()) //if (Utilities::getIntFromCharVector(fullData, MphdStartOffset + modfHintOffset) == 2) // TODO : remove if ok
	{
		modf = Chunk(fullData, fullDataOffset, sizeAdjustments);
		fullDataOffset = chunkLettersAndSize + fullDataOffset + modf.getGivenSize();
	}

	std::vector<int> adtsOffsets = main.getMhdrOffsets();
	int currentAdt;

	for (currentAdt = 0 ; currentAdt < 4096 ; currentAdt++)
	{	
		if (adtsOffsets[currentAdt] != 0)
		{
			fullDataOffset = adtsOffsets[currentAdt];
			adts.push_back(AdtAlpha(fullData, fullDataOffset, currentAdt));
		}
	}
}

Wdt WdtAlpha::toWdt()
{
	std::string name = "__testWdtLk.wdt";

	Mphd cMphd = mphd.toMphd();
	Main cMain = main.toMain();

	std::vector<char> emptyData(0);
	Chunk cMwmo = Chunk("OMWM", 0, emptyData);
	Chunk cModf = Chunk();

	if (mphd.isWmoBased())
	{
		cMwmo = monm.toMwmo();
		cModf = modf;
	}

	Wdt wdtLk = Wdt(name, mver, cMphd, cMain, cMwmo, cModf);
	return wdtLk;
}

std::ostream & operator<<(std::ostream & os, const WdtAlpha & wdtAlpha)
{
	os << wdtAlpha.wdtName << std::endl;
	os << "------------------------------" << std::endl;
	os << wdtAlpha.mver;
	os << wdtAlpha.mphd;
	os << wdtAlpha.main;
	os << wdtAlpha.mdnm;
	os << wdtAlpha.monm;
	os << wdtAlpha.modf;

	std::vector<AdtAlpha>::const_iterator adtsIter;
	int i = 0;

	for (adtsIter = wdtAlpha.adts.begin() ; adtsIter != wdtAlpha.adts.end() ; ++adtsIter)
	{
		os << *adtsIter;
		i++;
	}

	return os;
}