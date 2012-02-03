#ifndef MCNKCATATEX0_H_
#define MCNKCATATEX0_H_

#include <vector>
#include <string>
#include "../Chunk.h"

class McnkCataTex0 : public Chunk
{
	public:

		McnkCataTex0(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
		McnkCataTex0(std::string letters, int givenSize, const std::vector<char> &data);
		friend std::ostream & operator<<(std::ostream & os, const McnkCataTex0 & mcnkCataTex0);

	private:

		Chunk mcly;
		Chunk mcal;
		/*Chunk mcmt;*/

};

#endif