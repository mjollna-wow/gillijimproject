#ifndef MHDR_H_
#define MHDR_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Chunk.h"

class Mhdr : public Chunk
{
  public:
	
  Mhdr();
  Mhdr(std::ifstream & adtFile, int offsetInFile);
  Mhdr(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
};

#endif