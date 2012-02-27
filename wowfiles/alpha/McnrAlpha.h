#ifndef MCNRALPHA_H_
#define MCNRALPHA_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../lichking/McnrLk.h"
#include "../Chunk.h"

class McnrAlpha : public Chunk
{
  public:
	
  McnrAlpha();
  McnrAlpha(std::ifstream & adtFile, int offsetInFile);
  McnrAlpha(const  std::string letters, int givenSize, const std::vector<char> & chunkData);

  McnrLk toMcnrLk() const;
};

#endif