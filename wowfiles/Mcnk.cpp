#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mcnk.h>
#include <utilities/Utilities.h>

Mcnk::Mcnk() : Chunk()
{
}

Mcnk::Mcnk(std::ifstream & adtFile, int offsetInFile, const int headerSize)
{
  letters = Utilities::getLettersFromFile(adtFile, offsetInFile);
  offsetInFile += 4;

  givenSize = Utilities::getIntFromFile(adtFile, offsetInFile);
  offsetInFile += 4;

  data = Utilities::getCharVectorFromFile(adtFile, offsetInFile, headerSize);
}

Mcnk::Mcnk(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("KNCM", givenSize, data) 
{
}

void Mcnk::toFile()
{
  // TODO : something.
}