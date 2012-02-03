#ifndef MAIN_H_
#define MAIN_H_

#include <vector>
#include <string>
#include "Chunk.h"

class Main : public Chunk
{
    public:
	
		Main();
		Main(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
		Main(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
};

#endif