#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mcrf.h>
#include <utilities/Utilities.h>

Mcrf::Mcrf() : Chunk()
{
}

Mcrf::Mcrf(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Mcrf::Mcrf(const std::vector<char> & wholeFile, int offsetInFile)
{
}

Mcrf::Mcrf(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("FRCM", givenSize, data)
{
}

std::ostream & operator<<(std::ostream & os, const Mcrf & mcrf)
{
  os << "Chunk letters : " << mcrf.letters << std::endl;
  os << "Chunk givenSize : " << mcrf.givenSize << std::endl;

  if ( mcrf.data.size() != 0 )
  {
    os << "MCRF content : " << std::endl;

    std::vector<int> mcrfIndices ( Utilities::vecCharTo<int>(mcrf.data) );

    std::vector<int>::const_iterator mcrfContentIter;

    for (mcrfContentIter = mcrfIndices.begin() ; mcrfContentIter != mcrfIndices.end() ; ++mcrfContentIter)
    {
      os << *mcrfContentIter << std::endl;
    }
  }

  os << "------------------------------" << std::endl;
  return os;
}