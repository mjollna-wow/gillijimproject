#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/alpha/McnrAlpha.h>
#include <wowfiles/lichking/McnrLk.h>

McnrAlpha::McnrAlpha() : Chunk()
{
}

McnrAlpha::McnrAlpha(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

McnrAlpha::McnrAlpha(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("RNCM", givenSize, data) 
{
}

McnrLk McnrAlpha::toMcnrLk() const
{
  const int unknownBytes (13);

  McnrLk mcnrLk ("RNCM", givenSize - unknownBytes, data);

  return mcnrLk;
}