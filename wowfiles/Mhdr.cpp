#include <vector>
#include <string>
#include "Chunk.h"
#include "Mhdr.h"

Mhdr::Mhdr() : Chunk()
{
}

Mhdr::Mhdr(const std::vector<char> & fullAdtData, int position, int sizeAdjustments) : Chunk(fullAdtData, position, sizeAdjustments)
{
}

Mhdr::Mhdr(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("RDHM", givenSize, data) 
{
}