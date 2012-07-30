#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mddf.h>
#include <utilities/Utilities.h>

Mddf::Mddf() : Chunk()
{
}

Mddf::Mddf(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Mddf::Mddf(const std::vector<char> & wholeFile, int offsetInFile) : Chunk(wholeFile, offsetInFile)
{
}

Mddf::Mddf(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("FDDM", givenSize, data)
{
}

std::vector<int> Mddf::getEntriesIndices() const
{
  const int entrySize (36);
  std::vector<int> indices (0);

  std::vector<char>::const_iterator dataIter;
  int currentStart (0);
  
  for (dataIter = data.begin() ; dataIter != data.end() ; ++dataIter)
  {
    if ( ( dataIter - data.begin() ) % entrySize == 0 )
	  {
      indices.push_back( Utilities::get<int> ( data, currentStart ) );
	    currentStart = ( dataIter - data.begin() ) + entrySize;
	  }
  }

  return indices;
}

std::vector<int> Mddf::getM2IndicesForMmdx() const
{
  std::vector<int> mddfIndices( getEntriesIndices() );
  std::set<int> s;
  
  int size ( mddfIndices.size() );
  int i;

  for( i = 0 ; i < size ; ++i ) 
  {
    s.insert( mddfIndices[i] );
  }

  std::vector<int> indicesForMmdx ( s.begin(), s.end() );

  return indicesForMmdx;
}

std::ostream & operator<<(std::ostream & os, const Mddf & mddf)
{
  os << "Chunk letters : " << mddf.letters << std::endl;
  os << "Chunk givenSize : " << mddf.givenSize << std::endl;
  os << "Real chunk Size : " << mddf.getRealSize() << std::endl;
  os << "Indices : " << std::endl;

  std::vector<int> indices ( mddf.getEntriesIndices() );

  std::vector<int>::const_iterator mddfIndicesIter;

  for (mddfIndicesIter = indices.begin() ; mddfIndicesIter != indices.end() ; ++mddfIndicesIter)
  {
    os << *mddfIndicesIter << " ";
  }

  os << std::endl;

  os << "------------------------------" << std::endl;

  return os;
}