#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Chunk.h"
#include "Mphd.h"

Mphd::Mphd() : Chunk()
{
}

Mphd::Mphd(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Mphd::Mphd(const std::vector<char> & fullAdtData, int position, int sizeAdjustments) : Chunk(fullAdtData, position, sizeAdjustments)
{
}

Mphd::Mphd(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("DHPM", givenSize, data) 
{
}