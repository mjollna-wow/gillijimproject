#ifndef _WOWFILES_MWMO_H_
#define _WOWFILES_MWMO_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>

class Mwmo : public Chunk
{
  public:

    Mwmo();
    Mwmo(std::ifstream & adtFile, int offsetInFile);
	  Mwmo(const std::vector<char> & wholeFile, int offsetInFile);
    Mwmo(std::string letters, int givenSize, const std::vector<char> & chunkData);
	
    friend std::ostream & operator<<(std::ostream & os, const Mwmo & mwmo);	
};

#endif