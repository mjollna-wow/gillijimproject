#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Chunk.h"
#include "../utilities/Utilities.h"

Chunk::Chunk() : letters("NONE"), givenSize(0)
{
	std::vector<char> emptyData(0);
	data = emptyData;
}

Chunk::Chunk(std::ifstream & adtFile, int position) : letters("")
{
  letters = Utilities::getLettersFromFile(adtFile, position);
  position += 4;

  givenSize = Utilities::getIntFromFile(adtFile, position);
  position += 4;

  data = Utilities::getCharVectorFromFile(adtFile, position, givenSize);
}

Chunk::Chunk(const std::vector<char> & fullAdtData, int fullDataOffset, int sizeAdjustments)
{
	letters = Utilities::getStringFromCharVector(fullAdtData, fullDataOffset, 4);
	fullDataOffset = fullDataOffset + 4;

	givenSize = Utilities::getIntFromCharVector(fullAdtData, fullDataOffset);
	fullDataOffset = fullDataOffset + 4;

	data = Utilities::getCharSubVector(fullAdtData, fullDataOffset, givenSize + sizeAdjustments);
}

Chunk::Chunk(std::string let, int givSize, const std::vector<char> & da) : letters(let), givenSize(givSize), data(da)
{
}

std::vector<char> Chunk::getWholeChunk() const
{
	std::vector<char> wholeChunk(0);

	std::vector<char> let(letters.begin(), letters.end());
	wholeChunk.insert(wholeChunk.end(), let.begin(), let.end());

	char size[4];
	size[0] = givenSize & 0xff;
	wholeChunk.push_back(size[0]);
	size[1] = (givenSize >> 8)  & 0xff;
	wholeChunk.push_back(size[1]);
	size[2] = (givenSize >> 16) & 0xff;
	wholeChunk.push_back(size[2]);
	size[3] = (givenSize >> 24) & 0xff;
	wholeChunk.push_back(size[3]);

	wholeChunk.insert(wholeChunk.end(), data.begin(), data.end());

	return wholeChunk;
}

bool Chunk::isEmpty()
{
	return (letters == "NONE") && (givenSize == 0) && data.size() == 0;
}

std::ostream & operator<<(std::ostream & os, const Chunk & chunk)
{
	os << "Chunk letters : " << chunk.letters << std::endl;
	os << "Chunk givenSize : " << chunk.givenSize << std::endl;
	os << "------------------------------" << std::endl;
	return os;
}

int Chunk::getOffset(const int offsetInData)
{
	return Utilities::getIntFromCharVector(data, offsetInData);
}

int Chunk::getRealSize()
{
	return data.size();
}

int Chunk::getGivenSize()
{
	return givenSize;
}