#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>
#include <wowfiles/ChunkHeaders.h>
#include <wowfiles/Mcal.h>
#include <wowfiles/Mcrf.h>
#include <wowfiles/lichking/McnkLk.h>
#include <wowfiles/lichking/McnrLk.h>
#include <utilities/Utilities.h>
#include <wowfiles/WowChunkedFormat.h>

McnkLk::McnkLk(const std::vector<char> & adtFile, int offsetInFile, const int & headerSize) : Mcnk(adtFile, offsetInFile, mcnkTerrainHeaderSize)
{
  const int headerStartOffset (offsetInFile);

  offsetInFile = chunkLettersAndSize + offsetInFile;

  std::vector<char> headerContent (0);
  headerContent.assign( adtFile.begin() + offsetInFile, adtFile.begin() + offsetInFile + mcnkTerrainHeaderSize );
  mcnkHeader = *reinterpret_cast<McnkHeader*>(&headerContent[0]);

  offsetInFile = headerStartOffset + mcnkHeader.mcvtOffset;

  mcvt = Chunk(adtFile, offsetInFile);

  if (mcnkHeader.mccvOffset != 0)
  {
    offsetInFile = headerStartOffset + mcnkHeader.mccvOffset;
    mccv = Chunk(adtFile, offsetInFile);
  }

  offsetInFile = headerStartOffset + mcnkHeader.mcnrOffset;
  mcnr = McnrLk(adtFile, offsetInFile);

  offsetInFile = headerStartOffset + mcnkHeader.mclyOffset;
  mcly = Chunk(adtFile, offsetInFile);

  offsetInFile = headerStartOffset + mcnkHeader.mcrfOffset;
  mcrf = Mcrf(adtFile, offsetInFile);

  // Note : I don't check the 0x1 Mcnk header flag since it's not set on some maps, even though there is a shadow map (e.g. MonasteryInstances)
  if ((mcnkHeader.mcshOffset != 0) && (mcnkHeader.mcshOffset !=  mcnkHeader.mcalOffset)) 
  {
    offsetInFile = headerStartOffset + mcnkHeader.mcshOffset;
    mcsh = Chunk(adtFile, offsetInFile);
  }

  offsetInFile = headerStartOffset + mcnkHeader.mcalOffset;
  const int alphaSize (mcnkHeader.mcalSize - chunkLettersAndSize);
  mcal = Mcal(adtFile, offsetInFile, alphaSize);

  if (mcnkHeader.mclqOffset != 0)
  {
    offsetInFile = headerStartOffset + mcnkHeader.mclqOffset;
    mclq = Chunk(adtFile, offsetInFile);
  }

  if (mcnkHeader.mcseOffset != 0)
  {
    offsetInFile = headerStartOffset + mcnkHeader.mcseOffset;
    mcse = Chunk(adtFile, offsetInFile);
  }
}

McnkLk::McnkLk(std::string letters, int givenSize, const std::vector<char> &data) : Mcnk(letters, givenSize, data)
{
}

McnkLk::McnkLk(const McnkHeader & cMcnkHeader 
    , const Chunk & cMcvt
    , const Chunk & cMccv
    , const McnrLk & cMcnr
    , const Chunk & cMcly
    , const Mcrf & cMcrf
    , const Chunk & cMcsh
    , const Mcal & cMcal
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
  letters = "KNCM";

  givenSize = mcnkTerrainHeaderSize
    + mcvt.getRealSize()
    + chunkLettersAndSize
    + mcnr.getRealSize() 
    + chunkLettersAndSize
    + mcrf.getRealSize() 
    + chunkLettersAndSize;

  if (!mccv.isEmpty())
    givenSize = givenSize + chunkLettersAndSize + mccv.getRealSize();

  if (!mcly.isEmpty())
    givenSize = givenSize + chunkLettersAndSize + mcly.getRealSize();

  if (!mcsh.isEmpty())
    givenSize = givenSize + chunkLettersAndSize + mcsh.getRealSize();

  if (!mcal.isEmpty())
    givenSize = givenSize + chunkLettersAndSize + mcal.getRealSize();
  
  if (!mclq.isEmpty())
    givenSize = givenSize + chunkLettersAndSize + mclq.getRealSize();
  
  if (!mcse.isEmpty())
    givenSize = givenSize + chunkLettersAndSize + mcse.getRealSize();
}

std::vector<char> McnkLk::getWholeChunk() const
{
  std::vector<char> wholeChunk (0);

  std::vector<char> tempData (letters.begin(), letters.end());
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(givenSize);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  const char* temp = reinterpret_cast<const char*>(&mcnkHeader);
  std::vector<char> headerContent ( mcnkTerrainHeaderSize );
  headerContent.assign(temp, temp + mcnkTerrainHeaderSize );
  wholeChunk.insert(wholeChunk.end(), headerContent.begin(), headerContent.end());
  
  tempData = mcvt.getWholeChunk();
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  if (!mccv.isEmpty())
  {
    tempData = mccv.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }

  tempData = mcnr.getWholeChunk();
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  if (!mcly.isEmpty())
  {
    tempData = mcly.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }

  tempData = mcrf.getWholeChunk();
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  if (!mcsh.isEmpty())
  {
    tempData = mcsh.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }

  if (!mcal.isEmpty())
  {
    tempData = mcal.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }

  if (!mclq.isEmpty())
  {
    tempData = mclq.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }

  if (!mcse.isEmpty())
  {
    tempData = mcse.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }  
  
  return wholeChunk;
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