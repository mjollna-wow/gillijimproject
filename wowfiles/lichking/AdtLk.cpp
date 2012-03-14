#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include "AdtLk.h"
#include "../Chunk.h"
#include "../Mh2o.h"
#include "../Mcin.h"
#include "McnkLk.h"
#include "../../utilities/Utilities.h"

AdtLk::AdtLk(const std::string & adtFileName) : adtName(adtFileName)
{
  std::ifstream adtFile;
  adtFile.open(adtFileName.c_str(), std::ios::binary);

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
  offsetInFile = chunkLettersAndSize + mver.getRealSize();

  const int MhdrStartOffset = offsetInFile + chunkLettersAndSize;

  mhdr = Chunk(adtFile, offsetInFile);

  offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mcinOffset);

  mcin = Mcin(adtFile, offsetInFile); 

  int mh2oSizeInFile = 0;

  if (mhdr.getOffset(mh2oOffset) != 0)
  {
    const int lettersSize = 4;
    offsetInFile = MhdrStartOffset + Utilities::getIntFromFile(adtFile, MhdrStartOffset + mh2oOffset);
    mh2oSizeInFile = Utilities::getIntFromFile(adtFile, offsetInFile + lettersSize);
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

  const int GRETSize = 1413829191;

  if (mh2oSizeInFile == GRETSize)
  {
    updateMhdrAndMcin();
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
  const int relativeMhdrStart = 0x14;

  std::vector<char> mhdrData(0);

  std::vector<char> flags = Utilities::getCharVectorFromInt(mhdrFlags);
  mhdrData.insert(mhdrData.end(), flags.begin(), flags.end());

  int offsetInFile;

  offsetInFile = chunkLettersAndSize + mver.getRealSize() + chunkLettersAndSize + mhdrFixedSize;
  std::vector<char> mcinOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);
  mhdrData.insert(mhdrData.end(), mcinOffset.begin(), mcinOffset.end());

  offsetInFile = offsetInFile + chunkLettersAndSize + mcinFixedSize;
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

  std::vector<char> mh2oOffset = Utilities::getCharVectorFromInt(offsetInFile - relativeMhdrStart);

  offsetInFile = offsetInFile + chunkLettersAndSize + mh2o.getRealSize();

  std::vector<McnkLk>::const_iterator mcnksIter;
  int currentMcnk;

  std::vector<char> mcinData(0);
  const int unusedMcinBytes = 8;
  int throughMcinUnusedBytes;

  for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
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

  mhdr = Chunk("RDHM", mhdrFixedSize, mhdrData);
}

void AdtLk::toFile()
{
  std::string fileName = adtName;
  fileName.append("_new");
  std::ofstream outputFile(fileName.c_str(), std::ios::out|std::ios::binary);

  if (outputFile.is_open())
  {
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
  }

  outputFile.close();

  int currentMcnk;

  for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
  {
    mcnks[currentMcnk].toFile(outputFile, fileName);
  }

  outputFile.open(fileName.c_str(), std::ios::out|std::ios::binary|std::ios::app);

  if (outputFile.is_open())
  {
    if (!mfbo.isEmpty())
      outputFile.write((char *)&mfbo.getWholeChunk()[0], sizeof(char) * mfbo.getWholeChunk().size());
    if (!mtxf.isEmpty())
      outputFile.write((char *)&mtxf.getWholeChunk()[0], sizeof(char) * mtxf.getWholeChunk().size());
  }

  outputFile.close();
}

void AdtLk::mh2oToFile() // TODO : Make this better.
{
  std::string fileName = adtName; 
  fileName = fileName.substr(0, fileName.size() - 3);
  fileName = fileName.append("mh2o");

  mh2o.toFile(fileName);
}

AdtLk AdtLk::importMh2o(std::string mh2oName)
{
  std::ifstream mh2oFile;
  mh2oFile.open(mh2oName.c_str(), std::ios::binary);
  
  Mh2o mh2oFromFile;

  if (mh2oFile.is_open())
  {
    mh2oFromFile = Mh2o(mh2oFile, 0);
  }
  else 
  {
    mh2oFromFile = Mh2o();
  }
  
  mh2oFile.close();
  
  AdtLk adtWithMh2o = AdtLk( adtName
  , mver
  , getMhdrFlags()
  , mh2oFromFile
  , mtex
  , mmdx
  , mmid
  , mwmo
  , mwid
  , mddf
  , modf
  , mcnks
  , mfbo
  , mtxf
  );
  
  return adtWithMh2o;
}

int AdtLk::getMhdrFlags()
{
  return mhdr.getOffset(0);
}

int AdtLk::getMcnksWholeSize()
{
	int wholeSize = 0;
	
	int currentMcnk;
	for (currentMcnk = 0 ; currentMcnk < mcnks.size() ; currentMcnk++)
	{
		wholeSize = wholeSize + mcnks[currentMcnk].getWholeSize();
	}
		
	return wholeSize;
}

void AdtLk::updateMhdrAndMcin()
{
  // TODO !
}

std::ostream & operator<<(std::ostream & os, const AdtLk & adtLk)
{
  os << adtLk.adtName << std::endl;
  os << "------------------------------" << std::endl;
  os << adtLk.mver;
  os << adtLk.mhdr;
  os << adtLk.mcin;
  os << adtLk.mtex;
  os << adtLk.mmdx;
  os << adtLk.mmid;
  os << adtLk.mwmo;
  os << adtLk.mwid;
  os << adtLk.mddf;
  os << adtLk.modf;
  os << adtLk.mh2o;

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
