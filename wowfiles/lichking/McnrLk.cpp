#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"
#include "McnrLk.h"
#include "../../utilities/Utilities.h"

McnrLk::McnrLk() : Chunk()
{
}

McnrLk::McnrLk(std::ifstream & adtFile, int offsetInFile)
{
  letters = Utilities::getLettersFromFile(adtFile, offsetInFile);
  offsetInFile += 4;

  const int unknownBytes = 13;

  givenSize = Utilities::getIntFromFile(adtFile, offsetInFile) + unknownBytes;
  offsetInFile += 4;

  data = Utilities::getCharVectorFromFile(adtFile, offsetInFile, givenSize);
}

McnrLk::McnrLk(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("RNCM", givenSize, data) 
{
}