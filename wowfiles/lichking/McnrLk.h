#ifndef MCNRLK_H_
#define MCNRLK_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"

class McnrLk : public Chunk
{
  public:
  
  McnrLk();
  McnrLk(std::ifstream & adtFile, int offsetInFile);
  McnrLk(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
};

#endif