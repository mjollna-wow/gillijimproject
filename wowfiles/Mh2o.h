#ifndef MH2O_H_
#define MH2O_H_

#include <vector>
#include <string>
#include "Chunk.h"

class Mh2o : public Chunk
{
    public:
	
		Mh2o();
		Mh2o(const std::vector<char> & fullAdtData, int fullDataOffset, int sizeAdjustments);
		Mh2o(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
};

#endif