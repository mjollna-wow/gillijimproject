#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mmid.h>
#include <utilities/Utilities.h>

Mmid::Mmid() : Chunk()
{
}

Mmid::Mmid(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Mmid::Mmid(const std::vector<char> & wholeFile, int offsetInFile) : Chunk(wholeFile, offsetInFile)
{
}

Mmid::Mmid(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("DIMM", givenSize, data)
{
}

std::ostream & operator<<(std::ostream & os, const Mmid & mmid)
{
  os << "Chunk letters : " << mmid.letters << std::endl;
  os << "Chunk givenSize : " << mmid.givenSize << std::endl;
  os << "Chunk full content : ";

  os << "------------------------------" << std::endl;
  return os;
}