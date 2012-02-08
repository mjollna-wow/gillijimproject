#ifndef MCNK_H_
#define MCNK_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Chunk.h"

class Mcnk : public Chunk
{
  public:

    Mcnk(std::ifstream & file, int offsetInFile);
    Mcnk(const std::vector<char> & fullAdtData, int fullDataOffset, int sizeAdjustements);
    Mcnk(std::string letters, int givenSize, const std::vector<char> &data);

  protected: 

    std::vector<char> mcnkHeader;
};

#endif