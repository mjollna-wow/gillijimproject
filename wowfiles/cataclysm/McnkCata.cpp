#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/cataclysm/McnkCata.h>
#include <utilities/Utilities.h>

McnkCata::McnkCata(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
  const int mcnkHeaderSize (128);
  const int chunkLettersAndSize (8);

  offsetInFile = chunkLettersAndSize + offsetInFile;

  mcnkHeader = Utilities::getCharVectorFromFile(adtFile, offsetInFile, mcnkHeaderSize);
  offsetInFile = mcnkHeaderSize + offsetInFile;

  const int mccvOffset (0x074);
  const int mclvOffset (0x078);
  const int mcshOffset (0x02C);
  const int mclqOffset (0x060);

  mcvt = Chunk(adtFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mcvt.getGivenSize();

  if (Utilities::getIntFromCharVector(mcnkHeader, mccvOffset) != 0)
  {
    mccv = Chunk(adtFile, offsetInFile);
    offsetInFile = chunkLettersAndSize + offsetInFile + mccv.getGivenSize();
  }

  if (Utilities::getIntFromCharVector(mcnkHeader, mclvOffset) != 0)
  {
    mclv = Chunk(adtFile, offsetInFile);
    offsetInFile = chunkLettersAndSize + offsetInFile + mclv.getGivenSize();
  }

  mcnr = Chunk(adtFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mcnr.getGivenSize();

  if (Utilities::getIntFromCharVector(mcnkHeader, mclqOffset) != 0)
  {
    mclq = Chunk(adtFile, offsetInFile);
    offsetInFile = chunkLettersAndSize + offsetInFile + mclq.getGivenSize();
  }

  if (Utilities::getIntFromCharVector(mcnkHeader, mcshOffset) != 0)
  {
    mcse = Chunk(adtFile, offsetInFile);
    offsetInFile = chunkLettersAndSize + offsetInFile + mcse.getGivenSize();
  }
}

std::ostream & operator<<(std::ostream & os, const McnkCata & mcnkCata)
{
  os << "Chunk letters : " << mcnkCata.letters << std::endl;
  os << "Chunk givenSize : " << mcnkCata.givenSize << std::endl;

  os << "------------------------------" << std::endl;

  os << mcnkCata.mcvt;
  os << mcnkCata.mccv;
  os << mcnkCata.mclv;
  os << mcnkCata.mcnr;
  os << mcnkCata.mclq;
  os << mcnkCata.mcse;

  os << "------------------------------" << std::endl;
  return os;
}