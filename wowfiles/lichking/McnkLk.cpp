#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mcal.h>
#include <wowfiles/lichking/McnkLk.h>
#include <wowfiles/lichking/McnrLk.h>
#include <utilities/Utilities.h>
#include <wowfiles/WowChunkedFormat.h>

McnkLk::McnkLk(std::ifstream & adtFile, int offsetInFile, const int headerSize) : Mcnk(adtFile, offsetInFile, mcnkTerrainHeaderSize)
{
  const int headerStartOffset (offsetInFile);

  offsetInFile = chunkLettersAndSize + offsetInFile;

  getHeaderFromFile(adtFile, offsetInFile, mcnkTerrainHeaderSize);

  //mcnkHeader = Utilities::getCharVectorFromFile(adtFile, offsetInFile, mcnkTerrainHeaderSize);

  /*const int headerFlags (Utilities::get<int>(mcnkHeader, 0));
  const int mcshFlag (0x1);

  const int mcvtOffset (0x014);
  const int mccvOffset (0x074);
  const int mcnrOffset (0x018);
  const int mclyOffset (0x01C);
  const int mcrfOffset (0x020);
  const int mcshOffset (0x02C);
  const int mcalOffset (0x024);
  const int mcalSizeOffset (0x028);
  const int mclqOffset (0x060);
  const int mcseOffset (0x058);*/

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
  mcrf = Chunk(adtFile, offsetInFile);

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

McnkLk::McnkLk(const McnkLkHeader & cMcnkHeader 
    , const Chunk & cMcvt
    , const Chunk & cMccv
    , const McnrLk & cMcnr
    , const Chunk & cMcly
    , const Chunk & cMcrf
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

  // TODO : give McnkLk.data header content somehow.

  std::vector<char> tempData;

  tempData = mcvt.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  if (!mccv.isEmpty())
  {
    tempData = mccv.getWholeChunk();
    data.insert(data.end(), tempData.begin(), tempData.end());
  }

  tempData = mcnr.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  if (!mcly.isEmpty())
  {
    tempData = mcly.getWholeChunk();
    data.insert(data.end(), tempData.begin(), tempData.end());
  }

  tempData = mcrf.getWholeChunk();
  data.insert(data.end(), tempData.begin(), tempData.end());

  if (!mcsh.isEmpty())
  {
    tempData = mcsh.getWholeChunk();
    data.insert(data.end(), tempData.begin(), tempData.end());
  }

  if (!mcal.isEmpty())
  {
    tempData = mcal.getWholeChunk();
    data.insert(data.end(), tempData.begin(), tempData.end());
  }

  if (!mclq.isEmpty())
  {
    tempData = mclq.getWholeChunk();
    data.insert(data.end(), tempData.begin(), tempData.end());
  }

  if (!mcse.isEmpty())
  {
    tempData = mcse.getWholeChunk();
    data.insert(data.end(), tempData.begin(), tempData.end());
  }
}

void McnkLk::toFile(std::ofstream & adtFile, std::string & adtFileName)
{
  adtFile.open(adtFileName.c_str(), std::ios::out|std::ios::binary|std::ios::app);

  if (adtFile.is_open())
  {
    adtFile.write((char *)&letters[0], sizeof(char) * letters.size());
    adtFile.write((char *)&givenSize, sizeof(char) * sizeof(givenSize));

    adtFile.write((char *)&mcnkHeader, sizeof(char) * sizeof(mcnkHeader)); // TODO : check this absolutely (replace by getWholeChunk() when mcnk.data == header only ?)

    adtFile.write((char *)&mcvt.getWholeChunk()[0], sizeof(char) * mcvt.getWholeChunk().size());

    if (!mccv.isEmpty())
      adtFile.write((char *)&mccv.getWholeChunk()[0], sizeof(char) * mccv.getWholeChunk().size());

    adtFile.write((char *)&mcnr.getWholeChunk()[0], sizeof(char) * mcnr.getWholeChunk().size());

    if (!mcly.isEmpty())
      adtFile.write((char *)&mcly.getWholeChunk()[0], sizeof(char) * mcly.getWholeChunk().size());

    adtFile.write((char *)&mcrf.getWholeChunk()[0], sizeof(char) * mcrf.getWholeChunk().size());

    if (!mcsh.isEmpty())
      adtFile.write((char *)&mcsh.getWholeChunk()[0], sizeof(char) * mcsh.getWholeChunk().size());

    if (!mcal.isEmpty())
      adtFile.write((char *)&mcal.getWholeChunk()[0], sizeof(char) * mcal.getWholeChunk().size());

    if (!mclq.isEmpty())
      adtFile.write((char *)&mclq.getWholeChunk()[0], sizeof(char) * mclq.getWholeChunk().size());

    if (!mcse.isEmpty())
      adtFile.write((char *)&mcse.getWholeChunk()[0], sizeof(char) * mcse.getWholeChunk().size());
  }

  adtFile.close();
}

void McnkLk::toFile()
{
  // TODO
}

int McnkLk::getWholeSize()
{
  return getWholeChunk().size();
}

void McnkLk::getHeaderFromFile(std::ifstream & adtFile, const int position, const int length)
{
  adtFile.seekg(position, std::ios::beg);
  char * dataBuffer = new char[length];

  adtFile.read(dataBuffer, length);

  mcnkHeader = *reinterpret_cast<McnkLkHeader*>(dataBuffer);

  delete[] dataBuffer;
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