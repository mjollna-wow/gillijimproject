#ifndef _WOWFILES_MCRF_H_
#define _WOWFILES_MCRF_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>

class Mcrf : public Chunk
{
  public:

    Mcrf();
    Mcrf(std::ifstream & adtFile, int offsetInFile);
	  Mcrf(const std::vector<char> & wholeFile, int offsetInFile);
    Mcrf(std::string letters, int givenSize, const std::vector<char> & chunkData);
	
    friend std::ostream & operator<<(std::ostream & os, const Mcrf & mcrf);	
};

#endif