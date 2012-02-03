#ifndef MCNKALPHA_H_
#define MCNKALPHA_H_

#include <vector>
#include <iostream>
#include <string>
#include "../Chunk.h"

class McnkAlpha : public Chunk
{
	public:

		McnkAlpha(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
		McnkAlpha(std::string letters, int givenSize, const std::vector<char> &data);
		friend std::ostream & operator<<(std::ostream & os, const McnkAlpha & mcnkAlpha);

	private:

		std::vector<char> mcnkHeader;
		Chunk mcvt;
		Chunk mcnr;
		Chunk mcly;
		Chunk mcrf;
		Chunk mcsh;
		Chunk mcal;
		Chunk mclq;
};

#endif