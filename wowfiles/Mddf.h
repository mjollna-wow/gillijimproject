#ifndef _WOWFILES_MDDF_H_
#define _WOWFILES_MDDF_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>

class Mddf : public Chunk
{
  public:

    Mddf();
    Mddf(std::ifstream & adtFile, int offsetInFile);
	  Mddf(const std::vector<char> & wholeFile, int offsetInFile);
    Mddf(std::string letters, int givenSize, const std::vector<char> & chunkData);
    Mddf(std::vector<int> & alphaIndices);
	
    std::vector<int> getM2IndicesForMmdx() const;

    friend std::ostream & operator<<(std::ostream & os, const Mddf & mddf);	

  private: 

    std::vector<int> getEntriesIndices() const;

};

#endif