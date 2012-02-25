#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include "AdtLk.h"
#include "../Chunk.h"
#include "../Mhdr.h"
#include "../Mh2o.h"
#include "../Mcin.h"
#include "../Mcnk.h"
#include "McnkLk.h"
#include "../../utilities/Utilities.h"

AdtLk::AdtLk(const std::string & adtFileName) : adtName(adtFileName)
{
  std::ifstream adtFile;
  adtFile.open(adtFileName, std::ios::binary);

  const int chunkLettersAndSize = 8;
  int offsetInFile = 0;

  const int mcinOffset = 4;
  const int mh2oOffset = 40;
  const int mtexOffset = 8;
  const int mmdxOffset = 12;
  const int mmidOffset = 16;
  const int mwmoOffset = 20;
  const int mwidOffset = 24;
  const int mddfOffset = 28;
  const int modfOffset = 32;
  const int mfboOffset = 36;
  const int mtxfOffset = 44;

  mver = Chunk(adtFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mver.getRealSize();

  const int MhdrStartOffset = offsetInFile + chunkLettersAndSize;

  mhdr = Mhdr(adtFile, offsetInFile);

  offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mcinOffset);

  mcin = Mcin(adtFile, offsetInFile); 

  if (mhdr.getOffset(mh2oOffset) != 0)
  {
    offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mh2oOffset);
    mh2o = Mh2o(adtFile, offsetInFile);
  }

  offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mtexOffset);
  mtex = Chunk(adtFile, offsetInFile);

  offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mmdxOffset);
  mmdx = Chunk(adtFile, offsetInFile);

  offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mmidOffset);
  mmid = Chunk(adtFile, offsetInFile);

  offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mwmoOffset);
  mwmo = Chunk(adtFile, offsetInFile);

  offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mwidOffset);
  mwid = Chunk(adtFile, offsetInFile);

  offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mddfOffset);
  mddf = Chunk(adtFile, offsetInFile);

  offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + modfOffset);
  modf = Chunk(adtFile, offsetInFile);

  std::vector<int> mcnkOffsets = mcin.getMcnkOffsets();
  int currentMcnk;

  for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
  {
    offsetInFile = mcnkOffsets[currentMcnk];
    mcnks.push_back(McnkLk(adtFile, offsetInFile));
  }

  if (mhdr.getOffset(mfboOffset) != 0)
  {
    offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mfboOffset);
    mfbo = Chunk(adtFile, offsetInFile);
  }

  if (mhdr.getOffset(mtxfOffset) != 0)
  {
    offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mtxfOffset);
    mtxf = Chunk(adtFile, offsetInFile);
  }
}

AdtLk::AdtLk(const std::string & name
  , const Chunk & cMver
  , const Mhdr & cMhdr
  , const Mcin & cMcin
  , const Mh2o & cMh2o
  , const Chunk & cMtex
  , const Chunk & cMmdx
  , const Chunk & cMmid
  , const Chunk & cMwmo
  , const Chunk & cMwid
  , const Chunk & cMddf
  , const Chunk & cModf
  , const std::vector<McnkLk> & cMcnks
  , const Chunk & cMfbo
  , const Chunk & cMtxf
  ) : adtName(name)
  , mver(cMver)
  , mhdr(cMhdr)
  , mcin(cMcin)
  , mh2o(cMh2o)
  , mtex(cMtex)
  , mmdx(cMmdx)
  , mmid(cMmid)
  , mwmo(cMwmo)
  , mwid(cMwid)
  , mddf(cMddf)
  , modf(cModf)
  , mcnks(cMcnks)
  , mfbo(cMfbo)
  , mtxf(cMtxf)
{
}

void AdtLk::toFile()
{
  std::string fileName = adtName.append("test"); // TODO : remove this line
  std::ofstream outputFile(fileName.c_str(), std::ios::out|std::ios::app|std::ios::binary);
  outputFile.is_open();
	
  outputFile.write((char *)&mver.getWholeChunk()[0], sizeof(char) * mver.getWholeChunk().size());
  outputFile.write((char *)&mhdr.getWholeChunk()[0], sizeof(char) * mhdr.getWholeChunk().size());
  outputFile.write((char *)&mcin.getWholeChunk()[0], sizeof(char) * mcin.getWholeChunk().size());
  outputFile.write((char *)&mtex.getWholeChunk()[0], sizeof(char) * mtex.getWholeChunk().size());
  outputFile.write((char *)&mmdx.getWholeChunk()[0], sizeof(char) * mmdx.getWholeChunk().size());
  outputFile.write((char *)&mmid.getWholeChunk()[0], sizeof(char) * mmid.getWholeChunk().size());
  outputFile.write((char *)&mwmo.getWholeChunk()[0], sizeof(char) * mwmo.getWholeChunk().size());
  outputFile.write((char *)&mwid.getWholeChunk()[0], sizeof(char) * mwid.getWholeChunk().size());
  outputFile.write((char *)&mddf.getWholeChunk()[0], sizeof(char) * mddf.getWholeChunk().size());
  outputFile.write((char *)&modf.getWholeChunk()[0], sizeof(char) * modf.getWholeChunk().size());
  if (!mh2o.isEmpty())
    outputFile.write((char *)&mh2o.getWholeChunk()[0], sizeof(char) * mh2o.getWholeChunk().size());

  int currentMcnk;

  for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
    outputFile.write((char *)&mcnks[currentMcnk].getWholeChunk()[0], sizeof(char) * mcnks[currentMcnk].getWholeChunk().size());

  if (!mfbo.isEmpty())
    outputFile.write((char *)&mfbo.getWholeChunk()[0], sizeof(char) * mfbo.getWholeChunk().size());
  if (!mtxf.isEmpty())
    outputFile.write((char *)&mtxf.getWholeChunk()[0], sizeof(char) * mtxf.getWholeChunk().size());

  outputFile.close();
}

std::ostream & operator<<(std::ostream & os, const AdtLk & adtLk)
{
  os << adtLk.adtName << std::endl;
  os << "------------------------------" << std::endl;
  os << adtLk.mver;
  os << adtLk.mhdr;
  os << adtLk.mcin;
  os << adtLk.mh2o;
  os << adtLk.mtex;
  os << adtLk.mmdx;
  os << adtLk.mmid;
  os << adtLk.mwid;
  os << adtLk.mddf;
  os << adtLk.modf;

  std::vector<McnkLk>::const_iterator mcnksIter;
  int i = 0;

  for (mcnksIter = adtLk.mcnks.begin() ; mcnksIter != adtLk.mcnks.end() ; ++mcnksIter)
  {
    os << "MCNK #" << i << " : " << std::endl;
    os << *mcnksIter;
    i++;
  }

  os << adtLk.mfbo;
  os << adtLk.mtxf;

  return os;
}