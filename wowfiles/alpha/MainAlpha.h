#ifndef MAIN_ALPHA_H_
#define MAIN_ALPHA_H_

#include <vector>
#include <string>
#include "../Chunk.h"
#include "../Main.h"

class MainAlpha : public Chunk
{
    public:
	
		MainAlpha();
		MainAlpha(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
		MainAlpha(const  std::string letters, int givenSize, const std::vector<char> & chunkData);
		std::vector<int> getMhdrOffsets() const;
		Main toMain();
		friend std::ostream & operator<<(std::ostream & os, const MainAlpha & main);
};

#endif