#include <vector>
#include <string>
#include "Chunk.h"
#include "Main.h"
#include "../utilities/Utilities.h"

Main::Main() : Chunk()
{
}

Main::Main(const std::vector<char> & fullAdtData, int position, int sizeAdjustments) : Chunk(fullAdtData, position, sizeAdjustments)
{
}

Main::Main(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("NIAM", givenSize, data) 
{
}