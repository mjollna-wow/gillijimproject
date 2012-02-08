#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"	
#include "AdtAlpha.h"
#include "McnkAlpha.h"
#include "../Mcin.h"

AdtAlpha::AdtAlpha(std::ifstream & wdtAlphaFile, int offsetInFile, int adtNum) : adtNumber(adtNum)
{
  const int chunkLettersAndSize = 8;
	
  const int mcinOffset = 0x0;
  const int mtexOffset = 0x4;
  const int mddfOffset = 0x0C;
  const int modfOffset = 0x14;
	
  mhdr = Chunk(wdtAlphaFile, offsetInFile);

  const int MhdrStartOffset = offsetInFile + chunkLettersAndSize;

  offsetInFile = MhdrStartOffset + mhdr.getOffset(mcinOffset);
  mcin = Mcin(wdtAlphaFile, offsetInFile);

  offsetInFile = MhdrStartOffset + mhdr.getOffset(mtexOffset);
  mtex = Chunk(wdtAlphaFile, offsetInFile);

  offsetInFile = MhdrStartOffset + mhdr.getOffset(mddfOffset);
  mddf = Chunk(wdtAlphaFile, offsetInFile);

  offsetInFile = MhdrStartOffset + mhdr.getOffset(modfOffset);
  modf = Chunk(wdtAlphaFile, offsetInFile);

  std::vector<int> mcnkOffsets = mcin.getMcnkOffsets();
  int currentMcnk;

  for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
  {
    offsetInFile = mcnkOffsets[currentMcnk];
    mcnks.push_back(McnkAlpha(wdtAlphaFile, offsetInFile));
  }
}

std::ostream & operator<<(std::ostream & os, const AdtAlpha & adtAlpha)
{
  os << "ADT #" << adtAlpha.adtNumber << std::endl;
  os << "------------------------------" << std::endl;
  os << adtAlpha.mhdr;
  os << adtAlpha.mcin;
  os << adtAlpha.mtex;
  os << adtAlpha.mddf;
  os << adtAlpha.modf;

  std::vector<McnkAlpha>::const_iterator mcnksIter;
  int i = 0;

  for (mcnksIter = adtAlpha.mcnks.begin() ; mcnksIter != adtAlpha.mcnks.end() ; ++mcnksIter)
  {
    os << "MCNK #" << i << " : " << std::endl;
    os << *mcnksIter;
    i++;
  }

  return os;
}