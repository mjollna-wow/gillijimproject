#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mcal.h>
#include <utilities/Utilities.h>

Mcal::Mcal() : Chunk()
{
}

Mcal::Mcal(std::ifstream & adtFile, int offsetInFile, int alphaSize) : Chunk(adtFile, offsetInFile)
{
  letters = Utilities::getLettersFromFile(adtFile, offsetInFile);
  offsetInFile += 4;

  givenSize = Utilities::getIntFromFile(adtFile, offsetInFile);
  offsetInFile += 4;

  data = Utilities::getCharVectorFromFile(adtFile, offsetInFile, alphaSize);
}

Mcal::Mcal(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("LACM", givenSize, data)
{
}