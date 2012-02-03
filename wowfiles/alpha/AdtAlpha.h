#ifndef ADT_ALPHA_H_
#define ADT_ALPHA_H_

#include <vector>
#include <string>
#include "../Chunk.h"
#include "McnkAlpha.h"
#include "../Mcin.h"

class AdtAlpha
{
	public:

		AdtAlpha(const std::vector<char> & fullAdtData, int fullDataOffset, int adtNum);
		friend std::ostream & operator<<(std::ostream & os, const AdtAlpha & adtAlpha);
		// TODO : Have something for ADT coords.

	private:

		int adtNumber;
		Chunk mhdr;
		Mcin mcin;
		Chunk mtex;
		Chunk mddf;
		Chunk modf;
		std::vector<McnkAlpha> mcnks;
};

#endif