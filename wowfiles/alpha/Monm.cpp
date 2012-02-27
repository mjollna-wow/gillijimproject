#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"
#include "Monm.h"
#include "../../utilities/Utilities.h"

Monm::Monm() : Chunk()
{
}

Monm::Monm(std::ifstream & wdtAlphaFile, int offsetInFile) : Chunk(wdtAlphaFile, offsetInFile)
{
}

Monm::Monm(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("NIAM", givenSize, data) 
{
}

Chunk Monm::toMwmo() const
{
  Chunk mwmoLk = Chunk("OMWM", givenSize, data);
  return mwmoLk;
}