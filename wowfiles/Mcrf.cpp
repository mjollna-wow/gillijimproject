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

Mcrf::Mcrf(const std::vector<char> & wholeFile, int offsetInFile) : Chunk(wholeFile, offsetInFile)
{
}

Mcrf::Mcrf(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("FRCM", givenSize, data)
{
}

std::vector<int> Mcrf::getDoodadsIndices(const int & doodadsNumber) const
{
  std::vector<int> mcrfIndices ( Utilities::vecCharTo<int>(data) );
  std::vector<int> doodadsIndices ( mcrfIndices.begin(), mcrfIndices.begin() + doodadsNumber );

  return doodadsIndices;
}

std::vector<int> Mcrf::getWmosIndices(const int & wmosNumber) const
{
  std::vector<int> mcrfIndices ( Utilities::vecCharTo<int>(data) );
  std::vector<int> wmosIndices ( mcrfIndices.end() - wmosNumber, mcrfIndices.end() );

  return wmosIndices;
}

std::ostream & operator<<(std::ostream & os, const Mcrf & mcrf)
{
  os << "Chunk letters : " << mcrf.letters << std::endl;
  os << "Chunk givenSize : " << mcrf.givenSize << std::endl;
  os << "Chunk full content : ";

  if ( mcrf.data.size() != 0 )
  {
    std::vector<int> mcrfIndices ( Utilities::vecCharTo<int>(mcrf.data) );

    std::vector<int>::const_iterator mcrfContentIter;

    for (mcrfContentIter = mcrfIndices.begin() ; mcrfContentIter != mcrfIndices.end() ; ++mcrfContentIter)
    {
      os << *mcrfContentIter << " ";
    }
  }

  os << std::endl;

  os << "------------------------------" << std::endl;
  return os;
}