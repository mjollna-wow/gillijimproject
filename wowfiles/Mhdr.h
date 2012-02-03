#ifndef MHDR_H_
#define MHDR_H_

#include <vector>
#include <string>
#include "Chunk.h"

class Mhdr : public Chunk
{
    public:
	
		Mhdr();
		Mhdr(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
		Mhdr(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
};

#endif