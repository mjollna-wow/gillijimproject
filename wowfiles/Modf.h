#ifndef _WOWFILES_MODF_H_
#define _WOWFILES_MODF_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>

class Modf : public Chunk
{
  public:

    Modf();
    Modf(std::ifstream & adtFile, int offsetInFile);
	  Modf(const std::vector<char> & wholeFile, int offsetInFile);
    Modf(std::string letters, int givenSize, const std::vector<char> & chunkData);

    std::vector<int> getWmoIndicesForMwmo() const;

    friend std::ostream & operator<<(std::ostream & os, const Modf & modf);	

  private:

    std::vector<int> getEntriesIndices() const;
};

#endif