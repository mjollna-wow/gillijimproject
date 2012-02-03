#include <vector>
#include <fstream>
#include <string>
#include "Wdt.h"
#include "Chunk.h"
#include "../utilities/FileHandling.h"
#include "../utilities/Utilities.h"

Wdt::Wdt(const std::string & wdtFile) : wdtName(wdtFile)
{
	FileHandling file(wdtFile);
	std::vector<char> fullData = file.getFullFile();

	const int chunkLettersAndSize = 8;

	int fullDataOffset = 0;
	int sizeAdjustments = 0;

	mver = Chunk(fullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mver.getGivenSize();

	mphd = Chunk(fullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mphd.getGivenSize();

	main = Chunk(fullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + main.getGivenSize();

	mwmo = Chunk(fullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mwmo.getGivenSize();

	if (mwmo.getGivenSize() != 0)
	{
		modf = Chunk(fullData, fullDataOffset, sizeAdjustments);
		fullDataOffset = chunkLettersAndSize + fullDataOffset + modf.getGivenSize();
	}
}

Wdt::Wdt(const std::string & name
	, const Chunk & cMver
	, const Chunk & cMphd
	, const Chunk & cMain
	, const Chunk & cMwmo
	, const Chunk & cModf
	) : wdtName(name)
	, mver(cMver)
	, mphd(cMphd)
	, main(cMain)
	, mwmo(cMwmo)
	, modf(cModf)
{
}

void Wdt::toFile()
{
	std::string fileName = wdtName.append("test"); // TODO : remove this line :)
	std::ofstream outputFile(fileName.c_str(), std::ios::out|std::ios::app|std::ios::binary);
	outputFile.is_open();
	
	outputFile.write((char *)&mver.getWholeChunk()[0], sizeof(char) * mver.getWholeChunk().size());
	outputFile.write((char *)&mphd.getWholeChunk()[0], sizeof(char) * mphd.getWholeChunk().size());
	outputFile.write((char *)&main.getWholeChunk()[0], sizeof(char) * main.getWholeChunk().size());
	outputFile.write((char *)&mwmo.getWholeChunk()[0], sizeof(char) * mwmo.getWholeChunk().size());
	if (!modf.isEmpty())
		outputFile.write((char *)&modf.getWholeChunk()[0], sizeof(char) * modf.getWholeChunk().size());
	
	outputFile.close();
}

std::ostream & operator<<(std::ostream & os, const Wdt & wdt)
{
	os << wdt.wdtName << std::endl;
	os << "------------------------------" << std::endl;
	os << wdt.mver;
	os << wdt.mphd;
	os << wdt.main;
	os << wdt.mwmo;
	os << wdt.modf;

	return os;
}