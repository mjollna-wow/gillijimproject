#ifndef MPHD_H_
#define MPHD_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Chunk.h"

class Mphd : public Chunk
{
  public:
  
    Mphd();
    Mphd(std::ifstream & adtFile, int offsetInFile);
    Mphd(const  std::string letters, int givenSize, const std::vector<char> & chunkData);

    int getFlags();
};

#endif