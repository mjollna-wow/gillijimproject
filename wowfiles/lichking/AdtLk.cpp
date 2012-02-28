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
  , const int & mhdrFlags
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
  const int mhdrFixedSize = 64;
  const int mcinFixedSize = 4096;
  const int chunkLettersAndSize = 8;
  const int relativeMhdrStart = 0x14;

  std::vector<char> mhdrData(0);

  std::vector<char> flags = Utilities::getCharVectorFromInt(mhdrFlags);
  mhdrData.insert(mhdrData.end(), flags.begin(), flags.end());

  int offsetInFile;

  offsetInFile = chunkLettersAndSize + mver.getRealSize() + chunkLettersAndSize + mhdrFixedSize;
  std::vector<char> mcinOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  mhdrData.insert(mhdrData.end(), mcinOffset.begin(), mcinOffset.end());

  offsetInFile = offsetInFile + chunkLettersAndSize + mcinFixedSize; // ...
  std::vector<char> mtexOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  mhdrData.insert(mhdrData.end(), mtexOffset.begin(), mtexOffset.end());

  offsetInFile = offsetInFile + chunkLettersAndSize + mtex.getRealSize();
  std::vector<char> mmdxOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  mhdrData.insert(mhdrData.end(), mmdxOffset.begin(), mmdxOffset.end());

  offsetInFile = offsetInFile + chunkLettersAndSize + mmdx.getRealSize();
  std::vector<char> mmidOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  mhdrData.insert(mhdrData.end(), mmidOffset.begin(), mmidOffset.end());

  offsetInFile = offsetInFile + chunkLettersAndSize + mmid.getRealSize();
  std::vector<char> mwmoOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  mhdrData.insert(mhdrData.end(), mwmoOffset.begin(), mwmoOffset.end());

  offsetInFile = offsetInFile + chunkLettersAndSize + mwmo.getRealSize();
  std::vector<char> mwidOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  mhdrData.insert(mhdrData.end(), mwidOffset.begin(), mwidOffset.end());

  offsetInFile = offsetInFile + chunkLettersAndSize + mwid.getRealSize();
  std::vector<char> mddfOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  mhdrData.insert(mhdrData.end(), mddfOffset.begin(), mddfOffset.end());

  offsetInFile = offsetInFile + chunkLettersAndSize + mddf.getRealSize();
  std::vector<char> modfOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  mhdrData.insert(mhdrData.end(), modfOffset.begin(), modfOffset.end());

  offsetInFile = offsetInFile + chunkLettersAndSize + modf.getRealSize();

  std::vector<McnkLk>::const_iterator mcnksIter;
  int currentMcnk;

  std::vector<char> mcinData(0);
  const int unusedMcinBytes = 8;
  int throughMcinUnusedBytes;

  for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++) // TODO : get rid of unnecessary offsets (mh2o & mfbo) when size pb corrected
  {
    std::vector<char> mcnkOffset = Utilities::getCharVectorFromInt(offsetInFile);
    mcinData.insert(mcinData.end(), mcnkOffset.begin(), mcnkOffset.end());

    offsetInFile = offsetInFile + mcnks[currentMcnk].getWholeChunk().size();

    std::vector<char> mnckSize = Utilities::getCharVectorFromInt(mcnks[currentMcnk].getGivenSize());
    mcinData.insert(mcinData.end(), mnckSize.begin(), mnckSize.end());
 
    for (throughMcinUnusedBytes = 0 ; throughMcinUnusedBytes < unusedMcinBytes ; throughMcinUnusedBytes++)
    {
      mcinData.push_back(0);
    }
  }

  mcin = Mcin("NICM", mcinFixedSize, mcinData);

  const std::vector<char> emptyOffset(4);

  std::vector<char> mfboOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  if (mfbo.getGivenSize() != 0)
  {
    mhdrData.insert(mhdrData.end(), mfboOffset.begin(), mfboOffset.end());
  }
  else
  {
    mhdrData.insert(mhdrData.end(), emptyOffset.begin(), emptyOffset.end());
  }

  offsetInFile = offsetInFile + chunkLettersAndSize + mh2o.getRealSize();
  std::vector<char> mh2oOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  if (mh2o.getGivenSize() != 0)
  {
    mhdrData.insert(mhdrData.end(), mh2oOffset.begin(), mh2oOffset.end());
  }
  else
  {
    mhdrData.insert(mhdrData.end(), emptyOffset.begin(), emptyOffset.end());
  }

  offsetInFile = offsetInFile + chunkLettersAndSize + mtxf.getRealSize();
  std::vector<char> mtxfOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  if (mtxf.getGivenSize() != 0)
  {
    mhdrData.insert(mhdrData.end(), mtxfOffset.begin(), mtxfOffset.end());
  }
  else
  {
    mhdrData.insert(mhdrData.end(), emptyOffset.begin(), emptyOffset.end());
  }

  const int unused = 16;
  int fillUnused;

  for(fillUnused = 0 ; fillUnused < unused ; fillUnused++)
  {
    mhdrData.push_back(0);
  }

  mhdr = Mhdr("RDHM", mhdrFixedSize, mhdrData);
}

void AdtLk::toFile()
{
  std::string fileName = adtName.append("test");
  std::ofstream outputFile(fileName.c_str(), std::ios::out|std::ios::binary);
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

  outputFile.close();

  int currentMcnk;

  for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
  {
    mcnks[currentMcnk].toFile(outputFile, fileName);
  }

  outputFile.is_open();

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
  //os << adtLk.mcin; // TODO : causes problem with adtAlpha2Lk parsing, until alpha2Lk MCIN conversion is ok (MCIN being empty).
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