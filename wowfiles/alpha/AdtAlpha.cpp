#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../Chunk.h"	
#include "AdtAlpha.h"
#include "../lichking/AdtLk.h"
#include "McnkAlpha.h"
#include "../Mcin.h"

AdtAlpha::AdtAlpha(std::string & wdtAlphaName, int offsetInFile, int adtNum) : adtNumber(adtNum)
{
  std::ifstream wdtAlphaFile;
  wdtAlphaFile.open(wdtAlphaName, std::ios::binary);

  adtFileName = getAdtFileName(wdtAlphaName);

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

std::string AdtAlpha::getAdtFileName(const std::string & wdtName) const
{
  std::string adtFileName = wdtName;
  adtFileName = adtFileName.substr(0, adtFileName.size() - 4);
  adtFileName.append("_");

  int xCoord = adtNumber / 64;
  int yCoord = adtNumber % 64;

  std::stringstream tempStream;
  
  tempStream << xCoord;
  adtFileName.append(tempStream.str());

  adtFileName.append("_");
  tempStream.str("");

  tempStream << yCoord;
  adtFileName.append(tempStream.str());
  
  adtFileName.append(".adt");

  return adtFileName;
}

AdtLk AdtAlpha::toAdtLk() const
{  
  std::vector<char> emptyData(0);

  std::string cName = adtFileName;
  Chunk cMver = Chunk("REVM", 0, emptyData);
  Mhdr cMhdr = Mhdr("RDHM", 0, emptyData);
  Mcin cMcin = Mcin("NICM", 0, emptyData);
  Mh2o cMh2o = Mh2o("2OHM", 0, emptyData);
  Chunk cMtex = Chunk("XETM", 0, emptyData);
  Chunk cMmdx = Chunk("XDMM", 0, emptyData);
  Chunk cMmid = Chunk("DIMM", 0, emptyData);
  Chunk cMwmo = Chunk("OMWM", 0, emptyData);
  Chunk cMwid = Chunk("DIWM", 0, emptyData);
  Chunk cMddf = Chunk("FDDM", 0, emptyData);
  Chunk cModf = Chunk("FDOM", 0, emptyData);
  std::vector<McnkLk> cMcnks; // not good :)
  Chunk cMfbo = Chunk("OBFM", 0, emptyData);
  Chunk cMtxf = Chunk("FXTM", 0, emptyData);

  AdtLk adtLk(cName, cMver, cMhdr, cMcin, cMh2o, cMtex, cMmdx, cMmid, cMwmo, cMwid, cMddf, cModf, cMcnks, cMfbo, cMtxf);
  return adtLk;
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