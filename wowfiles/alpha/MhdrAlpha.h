#ifndef MHDRALPHA_H_
#define MHDRALPHA_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Chunk.h"

class MhdrAlpha : public Chunk
{
  public:
	
  MhdrAlpha();
  MhdrAlpha(std::ifstream & adtFile, int offsetInFile);
  MhdrAlpha(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
};

#endif