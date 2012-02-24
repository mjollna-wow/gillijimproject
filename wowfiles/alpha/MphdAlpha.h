#ifndef MPHD_ALPHA_H_
#define MPHD_ALPHA_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"
#include "../Mphd.h"

class MphdAlpha : public Chunk
{
  public:
	
  MphdAlpha();
  MphdAlpha(std::ifstream & wdtAlphaFile, int offsetInFile);
  MphdAlpha(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
  MphdAlpha(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
  bool isWmoBased() const;
  Mphd toMphd() const;
};

#endif