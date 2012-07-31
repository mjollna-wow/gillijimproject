#include <vector>
#include <set>
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

std::vector<int> Modf::getWmoIndicesForMwmo() const
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

void Modf::updateIndicesForLk(std::vector<int> & alphaIndices) // TODO : that thing looks awful. Needs to be totally different (at least it does what it's supposed to do though).
{
  std::vector<int> modfAlphaIndices( getEntriesIndices() );

  // TODO : add check to be sure alphaIndices.size() == data.size()

  for (int i = 0 ; i < modfAlphaIndices.size() ; ++i)
  {
    for (int j = 0 ; j < alphaIndices.size() ; ++j)
    {
      if ( modfAlphaIndices[i] == alphaIndices[j] )
	    {
        modfAlphaIndices[i] = j;
	    }
    }
  }

  const int entrySize (64);
  std::vector<char> newModfData (0);

  std::vector<char>::const_iterator dataIter;
  int newIndex (0);
  
  for (dataIter = data.begin() ; dataIter != data.end() ; ++dataIter)
  {
    if ( ( dataIter - data.begin() ) % entrySize == 0 )
	  {
      std::vector<char> currentIndex ( Utilities::getCharVectorFromInt( modfAlphaIndices[newIndex] ) );
      newModfData.insert( newModfData.end(), currentIndex.begin(), currentIndex.end() );
      ++newIndex;
	    dataIter += 3;
	  }
    else
    {
      newModfData.push_back( *dataIter );
    }
  }  
  
  data = newModfData;
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