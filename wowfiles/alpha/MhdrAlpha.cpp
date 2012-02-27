#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Chunk.h"
#include "MhdrAlpha.h"

MhdrAlpha::MhdrAlpha() : Chunk()
{
}

MhdrAlpha::MhdrAlpha(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

MhdrAlpha::MhdrAlpha(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("RDHM", givenSize, data) 
{
}