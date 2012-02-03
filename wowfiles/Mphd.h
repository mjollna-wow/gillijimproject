#ifndef MPHD_H_
#define MPHD_H_

#include <vector>
#include <string>
#include "Chunk.h"

class Mphd : public Chunk
{
    public:
	
		Mphd();
		Mphd(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
		Mphd(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
};

#endif