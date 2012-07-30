#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Modf.h>
#include <utilities/Utilities.h>

Modf::Modf() : Chunk()
{
}

Modf::Modf(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Modf::Modf(const std::vector<char> & wholeFile, int offsetInFile) : Chunk(wholeFile, offsetInFile)
{
}

Modf::Modf(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("FDOM", givenSize, data)
{
}

std::vector<int> Modf::getEntriesIndices() const
{
  const int entrySize (64);
  std::vector<int> indices (0);

  std::vector<char>::const_iterator dataIter;
  int currentStart (0);
  
  for (dataIter = data.begin() ; dataIter != data.end() ; ++dataIter)
  {
    if ( ( dataIter - data.begin() ) % entrySize == 0 )
	  {
      indices.push_back( Utilities::get<int> ( data, currentStart ));
	    currentStart = ( dataIter - data.begin() ) + entrySize;
	  }
  }

  return indices;
}

std::ostream & operator<<(std::ostream & os, const Modf & modf)
{
  os << "Chunk letters : " << modf.letters << std::endl;
  os << "Chunk givenSize : " << modf.givenSize << std::endl;
  os << "Real chunk Size : " << modf.getRealSize() << std::endl;
  os << "Indices : " << std::endl;

  std::vector<int> indices ( modf.getEntriesIndices() );

  std::vector<int>::const_iterator modfIndicesIter;

  for (modfIndicesIter = indices.begin() ; modfIndicesIter != indices.end() ; ++modfIndicesIter)
  {
    os << *modfIndicesIter << " ";
  }

  os << std::endl;

  os << "------------------------------" << std::endl;
  return os;
}