#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mwmo.h>
#include <utilities/Utilities.h>

Mwmo::Mwmo() : Chunk()
{
}

Mwmo::Mwmo(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Mwmo::Mwmo(const std::vector<char> & wholeFile, int offsetInFile)
{
}

Mwmo::Mwmo(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("OMWM", givenSize, data)
{
}

std::ostream & operator<<(std::ostream & os, const Mwmo & mwmo)
{
  os << "Chunk letters : " << mwmo.letters << std::endl;
  os << "Chunk givenSize : " << mwmo.givenSize << std::endl;
  os << "Chunk full content : ";

  os << "------------------------------" << std::endl;
  return os;
}