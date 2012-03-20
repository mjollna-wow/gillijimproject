#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/alpha/McvtAlpha.h>
#include <utilities/Utilities.h>

McvtAlpha::McvtAlpha() : Chunk()
{
}

McvtAlpha::McvtAlpha(std::ifstream & wdtAlphaFile, int offsetInFile) : Chunk(wdtAlphaFile, offsetInFile)
{
}

McvtAlpha::McvtAlpha(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("TVCM", givenSize, data) 
{
}

Chunk McvtAlpha::toMcvt() const 
{

  /* Note : Alpha vertices are NOT interleaved... Which means there are all outer vertices first (all 81), then all inner vertices (all 64) in MCVT (and not 9-8-9-8 etc. of each). 
   So here we re-order them for post-alpha format.
   */

  std::vector<char> cMcvtData (0);
  std::vector<char> tempData (0);

  const int outerVerticesSequence = 9*4;
  const int innerVerticesSequence = 8*4;

  const int innerDataStart = outerVerticesSequence*9;

  float currentVertex;
  int i;

  for (i = 0 ; i < 9 ; ++i)
  {
    tempData = Utilities::getCharSubVector(data, i*outerVerticesSequence, outerVerticesSequence);
    cMcvtData.insert(cMcvtData.end(), tempData.begin(), tempData.end());

    if (i == 8) break; 

    tempData = Utilities::getCharSubVector(data, innerDataStart+(i*innerVerticesSequence), innerVerticesSequence);
    cMcvtData.insert(cMcvtData.end(), tempData.begin(), tempData.end());
  }

  Chunk mcvtLk ("TVCM", givenSize, cMcvtData);

  return mcvtLk;
}