#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mphd.h>

Mphd::Mphd() : Chunk()
{
}

Mphd::Mphd(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Mphd::Mphd(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("DHPM", givenSize, data) 
{
}

int Mphd::getFlags()
{
  return getOffset(0);
}