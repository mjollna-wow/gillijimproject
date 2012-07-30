#ifndef _WOWFILES_MMDX_H_
#define _WOWFILES_MMDX_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>

class Mmdx : public Chunk
{
  public:

    Mmdx();
    Mmdx(std::ifstream & adtFile, int offsetInFile);
	  Mmdx(const std::vector<char> & wholeFile, int offsetInFile);
    Mmdx(std::string letters, int givenSize, const std::vector<char> & chunkData);
	
    friend std::ostream & operator<<(std::ostream & os, const Mmdx & mmdx);	
};

#endif