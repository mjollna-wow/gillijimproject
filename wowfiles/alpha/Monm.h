#ifndef MONM_H_
#define MONM_H_

#include <vector>
#include <string>
#include "../Chunk.h"

class Monm : public Chunk
{
    public:
	
		Monm();
		Monm(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
		Monm(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
		Chunk toMwmo();
};

#endif