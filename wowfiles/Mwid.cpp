#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mwid.h>
#include <utilities/Utilities.h>

Mwid::Mwid() : Chunk()
{
}

Mwid::Mwid(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Mwid::Mwid(const std::vector<char> & wholeFile, int offsetInFile)
{
}

Mwid::Mwid(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("DIWM", givenSize, data)
{
}

std::ostream & operator<<(std::ostream & os, const Mwid & mwid)
{
  os << "Chunk letters : " << mwid.letters << std::endl;
  os << "Chunk givenSize : " << mwid.givenSize << std::endl;
  os << "Chunk full content : ";

  os << "------------------------------" << std::endl;
  return os;
}