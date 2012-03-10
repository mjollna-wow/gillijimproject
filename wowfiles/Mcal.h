#ifndef MCAL_H_
#define MCAL_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class Mcal : public Chunk
{
  public:

    Mcal();
    Mcal(std::ifstream & adtFile, int offsetInFile, int alphaSize);
    Mcal(std::string letters, int givenSize, const std::vector<char> & chunkData);
};

#endif