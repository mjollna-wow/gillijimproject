#ifndef MCINALPHA_H_
#define MCINALPHA_H_

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Chunk.h"

class McinAlpha : public Chunk
{
  public:

    McinAlpha();
    McinAlpha(std::ifstream & adtFile, int offsetInFile);
    McinAlpha(std::string letters, int givenSize, const std::vector<char> & chunkData);

    friend std::ostream & operator<<(std::ostream & os, const Mcin & mcin);
};

#endif