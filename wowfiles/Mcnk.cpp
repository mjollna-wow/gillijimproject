#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Chunk.h"
#include "Mcnk.h"
#include "../utilities/Utilities.h"

Mcnk::Mcnk(const std::vector<char> & fullAdtData, int fullDataOffset, int sizeAdjustements) : Chunk(fullAdtData, fullDataOffset, sizeAdjustements)
{
}

Mcnk::Mcnk(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Mcnk::Mcnk(std::string letters, int givenSize, const std::vector<char> &data) : Chunk("KNCM", givenSize, data)
{
  const int chunkHeaderSize = 128;

  std::vector<char>::iterator chunkDataIter;
  for (chunkDataIter = data.begin() ; chunkDataIter != data.begin() + chunkHeaderSize ; ++chunkDataIter)
  {
    mcnkHeader.push_back(*chunkDataIter);
  }
}