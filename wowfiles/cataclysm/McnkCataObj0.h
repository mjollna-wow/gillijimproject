#ifndef MCNKCATAOBJ0_H_
#define MCNKCATAOBJ0_H_

#include <vector>
#include <string>
#include "../Chunk.h"

class McnkCataObj0 : public Chunk
{
	public:

		McnkCataObj0(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
		McnkCataObj0(std::string letters, int givenSize, const std::vector<char> &data);

	private:

		std::vector<char> mcnkHeader;
		Chunk mcrd;
		Chunk mcrw;

};

#endif