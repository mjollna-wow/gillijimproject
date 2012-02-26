#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "../Chunk.h"
#include "McnkLk.h"
#include "McnrLk.h"
#include "../../utilities/Utilities.h"

McnkLk::McnkLk(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
  const int mcnkHeaderSize = 128;
  const int chunkLettersAndSize = 8;
  const int headerStartOffset = offsetInFile;

  offsetInFile = chunkLettersAndSize + offsetInFile;

  mcnkHeader = Utilities::getCharVectorFromFile(adtFile, offsetInFile, mcnkHeaderSize);

  const int mcvtOffset = 0x014;
  const int mccvOffset = 0x074;
  const int mcnrOffset = 0x018;
  const int mclyOffset = 0x01C;
  const int mcrfOffset = 0x020;
  const int mcshOffset = 0x02C;
  const int mcalOffset = 0x024;
  const int mclqOffset = 0x060;
  const int mcseOffset = 0x058;

  offsetInFile = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcvtOffset);

  mcvt = Chunk(adtFile, offsetInFile);

  if (Utilities::getIntFromCharVector(mcnkHeader, mccvOffset) != 0)
  {
    offsetInFile = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mccvOffset);
    mccv = Chunk(adtFile, offsetInFile);
  }

  offsetInFile = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcnrOffset);
  mcnr = McnrLk(adtFile, offsetInFile);

  offsetInFile = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mclyOffset);
  mcly = Chunk(adtFile, offsetInFile);

  offsetInFile = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcrfOffset);
  mcrf = Chunk(adtFile, offsetInFile);

  if (Utilities::getIntFromCharVector(mcnkHeader, mcshOffset) != 0)
  {
    offsetInFile = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcshOffset);
    mcsh = Chunk(adtFile, offsetInFile);
  }

  offsetInFile = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcalOffset);
  mcal = Chunk(adtFile, offsetInFile);

  if (Utilities::getIntFromCharVector(mcnkHeader, mclqOffset) != 0)
  {
    offsetInFile = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mclqOffset);
    mclq = Chunk(adtFile, offsetInFile);
  }

  if (Utilities::getIntFromCharVector(mcnkHeader, mcseOffset) != 0)
  {
    offsetInFile = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcseOffset);
    mcse = Chunk(adtFile, offsetInFile);
  }
}

McnkLk::McnkLk(const std::vector<char> & fullAdtData, int fullDataOffset, int sizeAdjustments) : Chunk(fullAdtData, fullDataOffset, sizeAdjustments)
{
  const int mcnkHeaderSize = 128;
  const int chunkLettersAndSize = 8;
  const int headerStartOffset = fullDataOffset;

  fullDataOffset = chunkLettersAndSize + fullDataOffset;

  mcnkHeader = Utilities::getCharSubVector(fullAdtData, fullDataOffset, mcnkHeaderSize);

  const int mcvtOffset = 0x014;
  const int mccvOffset = 0x074;
  const int mcnrOffset = 0x018;
  const int mclyOffset = 0x01C;
  const int mcrfOffset = 0x020;
  const int mcshOffset = 0x02C;
  const int mcalOffset = 0x024;
  const int mclqOffset = 0x060;
  const int mcseOffset = 0x058;

  fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcvtOffset);

  mcvt = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

  if (Utilities::getIntFromCharVector(mcnkHeader, mccvOffset) != 0)
  {
    fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mccvOffset);
    mccv = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);
  }

  sizeAdjustments = sizeAdjustments + 13;
  fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcnrOffset);
  mcnr = McnrLk(fullAdtData, fullDataOffset, sizeAdjustments);

  sizeAdjustments = 0;
  fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mclyOffset);
  mcly = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

  fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcrfOffset);
  mcrf = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

  if (Utilities::getIntFromCharVector(mcnkHeader, mcshOffset) != 0)
  {
    fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcshOffset);
    mcsh = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);
  }

  fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcalOffset);
  mcal = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);

  if (Utilities::getIntFromCharVector(mcnkHeader, mclqOffset) != 0)
  {
    fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mclqOffset);
    mclq = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);
  }

  if (Utilities::getIntFromCharVector(mcnkHeader, mcseOffset) != 0)
  {
    fullDataOffset = headerStartOffset + Utilities::getIntFromCharVector(mcnkHeader, mcseOffset);
    mcse = Chunk(fullAdtData, fullDataOffset, sizeAdjustments);
  }
}

McnkLk::McnkLk(const std::vector<char> & cMcnkHeader 
    , const Chunk & cMcvt
    , const Chunk & cMccv
    , const McnrLk & cMcnr
    , const Chunk & cMcly
    , const Chunk & cMcrf
    , const Chunk & cMcsh
    , const Chunk & cMcal
    , const Chunk & cMclq
    , const Chunk & cMcse
    ) : mcnkHeader(cMcnkHeader)
  , mcvt(cMcvt)
  , mccv(cMccv)
  , mcnr(cMcnr)
  , mcly(cMcly)
  , mcrf(cMcrf)
  , mcsh(cMcsh)
  , mcal(cMcal)
  , mclq(cMclq)
  , mcse(cMcse)
{
  const int mcnkHeaderSize = 128;

  letters = "KNCM";
  givenSize = mcnkHeaderSize 
    + mcvt.getRealSize() 
    + mccv.getRealSize() 
    + mcnr.getGivenSize() 
    + mcly.getRealSize() 
    + mcrf.getRealSize() 
    + mcsh.getRealSize() 
    + mcal.getRealSize() 
    + mclq.getRealSize() 
    + mcse.getRealSize();

  data = mcvt.getWholeChunk();

  std::vector<char> tempData;

  tempData = mccv.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  tempData = mcnr.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  tempData = mcly.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  tempData = mcrf.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  tempData = mcsh.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  tempData = mcal.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  tempData = mclq.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  tempData = mcse.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());
}

std::ostream & operator<<(std::ostream & os, const McnkLk & mcnkLk)
{
  os << "Chunk letters : " << mcnkLk.letters << std::endl;
  os << "Chunk givenSize : " << mcnkLk.givenSize << std::endl;

  os << "------------------------------" << std::endl;

  os << mcnkLk.mcvt;
  os << mcnkLk.mccv;
  os << mcnkLk.mcnr;
  os << mcnkLk.mcly;
  os << mcnkLk.mcrf;
  os << mcnkLk.mcsh;
  os << mcnkLk.mcal;
  os << mcnkLk.mclq;
  os << mcnkLk.mcse;

  os << "------------------------------" << std::endl;
  return os;
}